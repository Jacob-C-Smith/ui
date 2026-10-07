#include <glyph/rectangle.h>

void rectangle_draw ( rectangle *p_rectangle, window *p_window );

rectangle *rectangle_construct ( rect r )
{
    rectangle *p_rectangle = default_allocator(NULL, sizeof(rectangle));

    glyph_construct((glyph *)p_rectangle);

    p_rectangle->_glyph.pfn_draw = (fn_glyph_draw *) rectangle_draw;
    p_rectangle->_dimensions = r;

    p_rectangle->_glyph.pfn_bounds_set((glyph *)p_rectangle, r);

    return p_rectangle;
}

void rectangle_draw ( rectangle *p_rectangle, window *p_window )
{
    p_window->pfn_draw_rect(
        p_window,
        p_rectangle->_glyph.pfn_bounds_get((glyph *)p_rectangle).origin.x + p_rectangle->_dimensions.origin.x,
        p_rectangle->_glyph.pfn_bounds_get((glyph *)p_rectangle).origin.y + p_rectangle->_dimensions.origin.y,
        p_rectangle->_dimensions.extent.x,
        p_rectangle->_dimensions.extent.y
    );

    if ( p_rectangle->fill )
        p_window->pfn_fill_rect(
            p_window,
            p_rectangle->_glyph.pfn_bounds_get((glyph *)p_rectangle).origin.x + p_rectangle->_dimensions.origin.x + p_rectangle->_dimensions.extent.x / 4,
            p_rectangle->_glyph.pfn_bounds_get((glyph *)p_rectangle).origin.y + p_rectangle->_dimensions.origin.y + p_rectangle->_dimensions.extent.y / 4,
            p_rectangle->_dimensions.extent.x / 2,
            p_rectangle->_dimensions.extent.y / 2
        );
}