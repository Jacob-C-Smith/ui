#include <compositor/array_compositor.h>

void array_compositor_compose ( compositor *p_compositor );

array_compositor *array_compositor_construct ( int columns )
{
    array_compositor *p_array_compositor = default_allocator(NULL, sizeof(array_compositor));

    *p_array_compositor = (array_compositor)
    {
        ._compositor = 
        {
            .pfn_compositor_composition_set = compositor_composition_set,
            .pfn_compositor_compose = array_compositor_compose,
        },
        ._columns = columns > 0 ? columns : 1
    };

    return p_array_compositor;
}

void array_compositor_compose ( compositor *p_compositor )
{
    if ( NULL == p_compositor || NULL == p_compositor->p_composition )
    {
        return;
    }

    array_compositor *p_array = (array_compositor *)p_compositor;
    glyph *p_comp = (glyph *)p_compositor->p_composition;
    window *p_window = p_comp->pfn_window_get(p_comp);
    point start_c = p_comp->pfn_cursor(p_comp);
    int columns = p_array->_columns;
    int child_count = 0;
    int idx = 0;
    float total_width = 0;
    float total_height = 0;
    int rows = 0;
    float *col_widths = NULL;
    float *row_heights = NULL;
    point c = start_c;

    if (columns <= 0) columns = 1;

    col_widths = default_allocator(NULL, sizeof(float) * columns);
    for (int i = 0; i < columns; i++) col_widths[i] = 0;
    
    for (iterator it = p_comp->pfn_iterator(p_comp); !it.done(&it); it.next(&it)) {
        child_count++;
    }
    
    rows = (child_count + columns - 1) / columns;
    row_heights = default_allocator(NULL, sizeof(float) * (rows > 0 ? rows : 1));
    for (int i = 0; i < rows; i++) row_heights[i] = 0;

    for (iterator it = p_comp->pfn_iterator(p_comp); !it.done(&it); it.next(&it))
    {
        glyph *p_child = it.item(&it);
        float child_w = 0;
        float child_h = 0;
        int c = 0;
        int r = 0;

        p_child->pfn_compose(p_child);
        p_child->pfn_size(p_child, p_window);

        child_w = p_child->_bounds.extent.x;
        child_h = p_child->_bounds.extent.y;

        r = idx / columns;
        c = idx % columns;

        if (child_w > col_widths[c]) col_widths[c] = child_w;
        if (child_h > row_heights[r]) row_heights[r] = child_h;
        
        idx++;
    }

    idx = 0;
    for (iterator it = p_comp->pfn_iterator(p_comp); !it.done(&it); it.next(&it))
    {
        glyph *p_child = it.item(&it);
        int r = idx / columns;
        int col = idx % columns;

        p_child->pfn_position_set(p_child, c);
        c.x += col_widths[col];

        idx++;
        if (idx % columns == 0)
        {
            c.x = start_c.x;
            c.y += row_heights[r];
        }
    }

    for (int i = 0; i < columns; i++) total_width += col_widths[i];
    for (int i = 0; i < rows; i++) total_height += row_heights[i];

    p_comp->pfn_adjust(p_comp, (point){start_c.x + total_width, start_c.y + total_height});
    p_comp->pfn_size(p_comp, p_window);

    default_allocator(col_widths, 0);
    default_allocator(row_heights, 0);
}
