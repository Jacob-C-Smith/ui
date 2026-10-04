#include <glyph/padding.h>

void padding_position_set (padding *p_padding, point _point);
rect padding_bounds_get (padding *p_padding);

padding *padding_construct ( glyph *p_glyph, int size )
{
    padding *p_padding = default_allocator(NULL, sizeof(padding));
    
    mono_glyph_construct((mono_glyph *)p_padding, p_glyph);

    p_padding->_mono_glyph._composition._glyph.pfn_position_set = (fn_glyph_position_set *) padding_position_set;
    p_padding->_mono_glyph._composition._glyph.pfn_bounds_get   = (fn_glyph_bounds_get *)   padding_bounds_get;    

    p_padding->_s = size;
    p_padding->_mono_glyph._composition._glyph.pfn_compose((glyph *)p_padding);

    return p_padding;
}

void padding_position_set (padding *p_padding, point _point)
{
    mono_glyph_position_set(
        (mono_glyph *) p_padding, 
        (point)
        {
            _point.x + p_padding->_s,
            _point.y + p_padding->_s
        }
    );
}

rect padding_bounds_get (padding *p_padding)
{
    rect cb = composition_bounds_get((composition *)p_padding);

    return (rect) 
    {
        .origin = 
        {
            cb.origin.x - p_padding->_s,
            cb.origin.y - p_padding->_s,
        },
        .extent = 
        {
            cb.extent.x + 2 * p_padding->_s,
            cb.extent.y + 2 * p_padding->_s,    
        }    
    };
}
