#include <compositor/simple_compositor.h>

void simple_compositor_compose ( compositor *p_compositor );

simple_compositor *simple_compositor_construct ( void )
{
    simple_compositor *p_simple_compositor = default_allocator(NULL, sizeof(simple_compositor));

    *p_simple_compositor = (simple_compositor)
    {
        ._compositor = 
        {
            .pfn_compositor_composition_set = compositor_composition_set,
            .pfn_compositor_compose = simple_compositor_compose,
        }
    };

    return p_simple_compositor;
}

void simple_compositor_compose ( compositor *p_compositor )
{
    if ( NULL == p_compositor || NULL == p_compositor->p_composition )
    {
        return;
    }

    glyph *p_comp = (glyph *)p_compositor->p_composition;
    window *p_window = p_comp->pfn_window_get(p_comp);
    point c = p_comp->pfn_cursor(p_comp);

    for (iterator it = p_comp->pfn_iterator(p_comp); !it.done(&it); it.next(&it))
    {
        glyph *p_child = it.item(&it);

        p_child->pfn_position_set(p_child, c);
        p_child->pfn_compose(p_child);
        p_child->pfn_size(p_child, p_window);

        c = p_comp->pfn_adjust_child(p_comp, p_child, c);
    }

    p_comp->pfn_adjust(p_comp, c);
    p_comp->pfn_size(p_comp, p_window);
}
