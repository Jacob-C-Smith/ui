#include <glyph/composition.h>

int composition_construct ( composition *p_composition )
{
    glyph_construct((glyph *)p_composition);

    p_composition->_glyph.pfn_window_set      = (fn_glyph_window_set *)      composition_window_set;
    p_composition->_glyph.pfn_insert          = (fn_glyph_insert *)          composition_insert;
    p_composition->_glyph.pfn_child           = (fn_glyph_child *)           composition_child;
    p_composition->_glyph.pfn_draw            = (fn_glyph_draw *)            composition_draw;
    p_composition->_glyph.pfn_bounds_get      = (fn_glyph_bounds_get *)      composition_bounds_get;
    p_composition->_glyph.pfn_composition_get = (fn_glyph_composition_get *) composition_composition_get;
    p_composition->_glyph.pfn_compose         = (fn_glyph_compose *)         composition_compose;
    p_composition->_glyph.pfn_position_get    = (fn_glyph_position_get *)    composition_position_get;
    p_composition->_glyph.pfn_position_set    = (fn_glyph_position_set *)    composition_position_set;
    p_composition->_glyph.pfn_adjust          = (fn_glyph_adjust *)          composition_adjust; 
    p_composition->_glyph.pfn_adjust_child    = (fn_glyph_adjust_child *)    composition_adjust_child;
    p_composition->_glyph.pfn_cursor          = (fn_glyph_cursor *)          composition_cursor;
    p_composition->_glyph.pfn_size            = (fn_glyph_size *)            composition_size;
    p_composition->_glyph.pfn_iterator        = (fn_glyph_iterator *)        composition_iterator;
    
    array_construct(&p_composition->p_array, 32);
    p_composition->_size = (rect){ 0 };
    p_composition->_position = (point){ 0 };
    p_composition->p_compositor = (compositor *) simple_compositor_construct();
    p_composition->p_compositor->pfn_compositor_composition_set(p_composition->p_compositor, p_composition);

    return 1;
}

void composition_window_set (composition *p_composition, window *p_window)
{
    glyph_window_set((glyph *)p_composition, p_window);
    composition_compose(p_composition);
}

void composition_insert (composition *p_composition, glyph *p_child, int i)
{
    (void) i;
    p_child->pfn_parent_set(p_child, (glyph *)p_composition);
    array_add(p_composition->p_array, p_child);
    p_composition->p_compositor->pfn_compositor_compose(p_composition->p_compositor);
}

glyph *composition_child (composition *p_composition, int i)
{
    glyph *p_glyph = NULL;
    array_index(p_composition->p_array, i, (void **)&p_glyph);
    return p_glyph;
}

void composition_draw (composition *p_composition, window *p_window)
{
    for (iterator it = composition_iterator(p_composition); !it.done(&it); it.next(&it))
    {
        glyph *p_glyph = it.item(&it);
        p_glyph->pfn_draw(p_glyph, p_window);
    }
}

rect composition_bounds_get (composition *p_composition)
{
    if ( 0 == array_size(p_composition->p_array) ) 
        return glyph_bounds_get((glyph *)p_composition);

    float minX = 1000000, minY = 1000000, maxX = -1000000, maxY = -1000000;

    for (iterator it = composition_iterator(p_composition); !it.done(&it); it.next(&it))
    {
        glyph *p_glyph = it.item(&it);
        rect b = p_glyph->pfn_bounds_get(p_glyph);

        minX = (minX < b.origin.x) ? minX : b.origin.x;
        minY = (minY < b.origin.y) ? minY : b.origin.y;
        maxX = (maxX > b.origin.x + b.extent.x) ? maxX : b.origin.x + b.extent.x;
        maxY = (maxY > b.origin.y + b.extent.y) ? maxY : b.origin.y + b.extent.y;
    }

    return (rect){ { minX, minY }, { maxX - minX, maxY - minY } };
}

composition *composition_composition_get ( composition *p_composition )
{
    return p_composition;
}

void composition_compose (composition *p_composition)
{
    p_composition->p_compositor->pfn_compositor_compose(p_composition->p_compositor);
}

point composition_position_get (composition *p_composition)
{
    return p_composition->_position;
}

void composition_position_set (composition *p_composition, point _point)
{
    p_composition->_position = _point;
}

point composition_adjust_child ( composition *p_composition, glyph *p_child, point cursor )
{
    (void)p_composition;
    return (point)
    {
        cursor.x + p_child->_bounds.extent.x,
        cursor.y
    };
}

void composition_adjust ( composition *p_composition, point cursor )
{
    rect b = composition_bounds_get(p_composition);
    float w = cursor.x - p_composition->_position.x;
    float h = cursor.y - p_composition->_position.y;
    p_composition->_size = (rect)
    {
        .origin = { 0, 0 },
        .extent = { w > b.extent.x ? w : b.extent.x, h > b.extent.y ? h : b.extent.y }
    };
}

point composition_cursor (composition *p_composition)
{
    return p_composition->_position;
}

void composition_size (composition *p_composition, window *p_window)
{
    (void)p_window;
    glyph_bounds_set(
        (glyph *)p_composition, 
        (rect)
        {
            .origin = 
            { 
                p_composition->_position.x, 
                p_composition->_position.y 
            },
            .extent = 
            { 
                p_composition->_size.extent.x, 
                p_composition->_size.extent.y 
            }
        }
    );
}

iterator composition_iterator (composition *p_composition)
{
    return array_iterator(p_composition->p_array);
}