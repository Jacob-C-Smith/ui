#include <glyph/overlay.h>
#include <stdarg.h>

point overlay_adjust_child ( overlay *p_overlay, glyph *p_child, point cursor );
void overlay_adjust ( overlay *p_overlay, point cursor );

overlay *overlay_construct ( void )
{
    overlay *p_overlay = default_allocator(NULL, sizeof(overlay));
    
    composition_construct((composition *)p_overlay);
    
    p_overlay->_composition._glyph.pfn_adjust_child = (fn_glyph_adjust_child *) overlay_adjust_child;
    p_overlay->_composition._glyph.pfn_adjust = (fn_glyph_adjust *) overlay_adjust;

    return p_overlay;
}

overlay *overlay_from_arguments ( size_t count, ... )
{
    va_list list;
    overlay *p_overlay = overlay_construct();

    va_start(list, count);

    for (size_t i = 0; i < count; i++)
        p_overlay->_composition._glyph.pfn_insert(
            (glyph *)p_overlay, 
            (glyph *)va_arg(list, void *),
            i
        );

    va_end(list);

    return p_overlay;
}

point overlay_adjust_child ( overlay *p_overlay, glyph *p_child, point cursor )
{
    (void)p_overlay;
    (void)p_child;
    return cursor;
}

void overlay_adjust ( overlay *p_overlay, point cursor )
{
    (void)cursor;
    if ( p_overlay->_composition.p_array && array_size(p_overlay->_composition.p_array) > 0 )
    {
        glyph *p_first_child = NULL;
        array_index(p_overlay->_composition.p_array, 0, (void **)&p_first_child);
        if ( p_first_child )
        {
            rect b = p_first_child->pfn_bounds_get(p_first_child);
            p_overlay->_composition._size = (rect)
            {
                .origin = { 0, 0 },
                .extent = { b.extent.x, b.extent.y }
            };
            return;
        }
    }
    
    p_overlay->_composition._size = (rect) { .origin = { 0, 0 }, .extent = { 0, 0 } };
}
