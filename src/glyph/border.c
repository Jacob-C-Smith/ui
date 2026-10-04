#include <glyph/border.h>

void border_position_set (border *p_border, point _point);
void border_draw (border *p_border, window *p_window);
rect border_bounds_get (border *p_border);
int draw_border( border *p_border, window *p_window );

border *border_construct ( glyph *p_glyph, int stroke )
{
    border *p_border = default_allocator(NULL, sizeof(border));
    
    mono_glyph_construct((mono_glyph *)p_border, p_glyph);

    p_border->_mono_glyph._composition._glyph.pfn_position_set = (fn_glyph_position_set *) border_position_set;
    p_border->_mono_glyph._composition._glyph.pfn_draw         = (fn_glyph_draw *)         border_draw;
    p_border->_mono_glyph._composition._glyph.pfn_bounds_get   = (fn_glyph_bounds_get *)   border_bounds_get;    

    p_border->_s = stroke;
    p_border->_mono_glyph._composition._glyph.pfn_compose((glyph *)p_border);

    return p_border;
}

void border_position_set (border *p_border, point _point)
{
    mono_glyph_position_set(
        (mono_glyph *) p_border, 
        (point)
        {
            _point.x + p_border->_s,
            _point.y + p_border->_s
        }
    );
}

void border_draw (border *p_border, window *p_window)
{
    composition_draw((composition *)p_border, p_window);

    draw_border(p_border, p_window);
}

rect border_bounds_get (border *p_border)
{
    rect cb = composition_bounds_get((composition *)p_border);

    return (rect) 
    {
        .origin = 
        {
            cb.origin.x - p_border->_s,
            cb.origin.y - p_border->_s,
        },
        .extent = 
        {
            cb.extent.x + 2 * p_border->_s,
            cb.extent.y + 2 * p_border->_s,    
        }    
    };
}

int draw_border( border *p_border, window *p_window )
{
    rect b = p_border->_mono_glyph._composition._glyph.pfn_bounds_get((glyph *)p_border);

    for (int i = 0; i < p_border->_s; i++)
        p_window->pfn_draw_rect(
            p_window,
            b.origin.x + i,
            b.origin.y + i,
            b.extent.x - 2 * i,
            b.extent.y - 2 * i
        );

    return 1;
}