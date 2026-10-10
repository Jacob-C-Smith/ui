#include <glyph/circle.h>

void circle_draw ( circle *p_circle, window *p_window );

circle *circle_construct ( rect r )
{
    circle *p_circle = default_allocator(NULL, sizeof(circle));

    glyph_construct((glyph *)p_circle);

    p_circle->_glyph.pfn_draw = (fn_glyph_draw *) circle_draw;
    p_circle->_dimensions = r;

    p_circle->_glyph.pfn_bounds_set((glyph *)p_circle, r);

    return p_circle;
}

void circle_draw ( circle *p_circle, window *p_window )
{
    p_window->pfn_draw_circle(
        p_window,
        p_circle->_glyph.pfn_bounds_get((glyph *)p_circle).origin.x + p_circle->_dimensions.origin.x,
        p_circle->_glyph.pfn_bounds_get((glyph *)p_circle).origin.y + p_circle->_dimensions.origin.y,
        p_circle->_dimensions.extent.x,
        p_circle->_dimensions.extent.y
    );

    if ( p_circle->fill )
        p_window->pfn_fill_circle(
            p_window,
            p_circle->_glyph.pfn_bounds_get((glyph *)p_circle).origin.x + p_circle->_dimensions.origin.x + p_circle->_dimensions.extent.x / 4,
            p_circle->_glyph.pfn_bounds_get((glyph *)p_circle).origin.y + p_circle->_dimensions.origin.y + p_circle->_dimensions.extent.y / 4,
            p_circle->_dimensions.extent.x / 2,
            p_circle->_dimensions.extent.y / 2
        );
}