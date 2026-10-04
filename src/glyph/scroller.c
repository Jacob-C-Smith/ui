#include <glyph/scroller.h>

void scroller_position_set (scroller *p_scroller, point _point);
void scroller_draw (scroller *p_scroller, window *p_window);
rect scroller_bounds_get (scroller *p_scroller);
int draw_scroller( scroller *p_scroller, window *p_window );

scroller *scroller_construct ( glyph *p_glyph, int width )
{
    scroller *p_scroller = default_allocator(NULL, sizeof(scroller));
    
    mono_glyph_construct((mono_glyph *)p_scroller, p_glyph);

    p_scroller->_mono_glyph._composition._glyph.pfn_draw         = (fn_glyph_draw *)         scroller_draw;
    p_scroller->_mono_glyph._composition._glyph.pfn_bounds_get   = (fn_glyph_bounds_get *)   scroller_bounds_get;    

    p_scroller->_w = width;
    p_scroller->_mono_glyph._composition._glyph.pfn_compose((glyph *)p_scroller);

    return p_scroller;
}

void scroller_draw (scroller *p_scroller, window *p_window)
{
    composition_draw((composition *)p_scroller, p_window);

    draw_scroller(p_scroller, p_window);
}

rect scroller_bounds_get (scroller *p_scroller)
{
    rect cb = composition_bounds_get((composition *)p_scroller);

    return (rect) 
    {
        .origin = 
        {
            cb.origin.x,
            cb.origin.y,
        },
        .extent = 
        {
            cb.extent.x + p_scroller->_w,
            cb.extent.y,
        }    
    };
}

int draw_scroller ( scroller *p_scroller, window *p_window )
{
    rect b = p_scroller->_mono_glyph._composition._glyph.pfn_bounds_get((glyph *)p_scroller);

    p_window->pfn_draw_rect(
        p_window,
        b.origin.x + b.extent.x - p_scroller->_w,
        b.origin.y,
        p_scroller->_w,
        b.extent.y
    );

    p_window->pfn_fill_rect(
        p_window,
        b.origin.x + b.extent.x - p_scroller->_w + (p_scroller->_w >> 2),
        b.origin.y + (p_scroller->_w >> 2),
        p_scroller->_w - (p_scroller->_w >> 1),
        b.extent.y - (p_scroller->_w >> 1)
    );

    return 1;
}