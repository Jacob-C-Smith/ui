#include <glyph/margin.h>

void margin_position_set (margin *p_margin, point _point);
rect margin_bounds_get (margin *p_margin);

margin *margin_construct ( glyph *p_glyph, int size )
{
    margin *p_margin = default_allocator(NULL, sizeof(margin));
    
    mono_glyph_construct((mono_glyph *)p_margin, p_glyph);

    p_margin->_mono_glyph._composition._glyph.pfn_position_set = (fn_glyph_position_set *) margin_position_set;
    p_margin->_mono_glyph._composition._glyph.pfn_bounds_get   = (fn_glyph_bounds_get *)   margin_bounds_get;    

    p_margin->_s = size;
    p_margin->_mono_glyph._composition._glyph.pfn_compose((glyph *)p_margin);

    return p_margin;
}

void margin_position_set (margin *p_margin, point _point)
{
    mono_glyph_position_set(
        (mono_glyph *) p_margin, 
        (point)
        {
            _point.x + p_margin->_s,
            _point.y + p_margin->_s
        }
    );
}

rect margin_bounds_get (margin *p_margin)
{
    rect cb = composition_bounds_get((composition *)p_margin);

    return (rect) 
    {
        .origin = 
        {
            cb.origin.x - p_margin->_s,
            cb.origin.y - p_margin->_s,
        },
        .extent = 
        {
            cb.extent.x + 2 * p_margin->_s,
            cb.extent.y + 2 * p_margin->_s,    
        }    
    };
}
