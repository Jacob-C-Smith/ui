#include <glyph/mono_glyph.h>

int mono_glyph_construct ( mono_glyph *p_mono_glyph, glyph *p_glyph )
{
    composition_construct((composition *)p_mono_glyph);

    p_mono_glyph->_composition._glyph.pfn_position_set    = (fn_glyph_position_set *)    mono_glyph_position_set;
    p_mono_glyph->_composition._glyph.pfn_compose         = (fn_glyph_compose *)         mono_glyph_compose;
    p_mono_glyph->_composition._glyph.pfn_size            = (fn_glyph_size *)            mono_glyph_size;
    p_mono_glyph->_composition._glyph.pfn_adjust          = (fn_glyph_adjust *)          mono_glyph_adjust; 
    p_mono_glyph->_composition._glyph.pfn_adjust_child    = (fn_glyph_adjust_child *)    mono_glyph_adjust_child;
    p_mono_glyph->_composition._glyph.pfn_insert          = (fn_glyph_insert *)          mono_glyph_insert;
    p_mono_glyph->_composition._glyph.pfn_child           = (fn_glyph_child *)           mono_glyph_child;
    p_mono_glyph->_composition._glyph.pfn_composition_get = (fn_glyph_composition_get *) mono_glyph_composition_get;

    composition_insert((composition *) p_mono_glyph, p_glyph, 0);
    p_mono_glyph->_composition._position = (point) { 0 };

    return 1;
}

void mono_glyph_position_set (mono_glyph *p_mono_glyph, point _point)
{
    glyph *p_unwrap = composition_child((composition *) p_mono_glyph, 0);
    p_unwrap->pfn_position_set(p_unwrap, _point);
    composition_position_set((composition *) p_mono_glyph, _point);
}

void mono_glyph_compose (mono_glyph *p_mono_glyph)
{
    composition_compose((composition *)p_mono_glyph);
}

void mono_glyph_size (mono_glyph *p_mono_glyph, window *p_window)
{
    glyph *p_unwrap = composition_child((composition *) p_mono_glyph, 0);
    p_unwrap->pfn_size(p_unwrap, p_window);
    composition_size((composition *)p_mono_glyph, p_window);
}

void mono_glyph_adjust ( mono_glyph *p_mono_glyph, point cursor )
{
    glyph *p_unwrap = composition_child((composition *) p_mono_glyph, 0);
    p_unwrap->pfn_adjust(p_unwrap, cursor);
    composition_adjust((composition *)p_mono_glyph, cursor);
}

point mono_glyph_adjust_child ( mono_glyph *p_mono_glyph, glyph *p_child, point cursor )
{
    glyph *p_unwrap = composition_child((composition *) p_mono_glyph, 0);
    return p_unwrap->pfn_adjust_child(p_unwrap, p_child, cursor);
}

void mono_glyph_insert (mono_glyph *p_mono_glyph, glyph *p_child, int i)
{
    glyph *p_unwrap = composition_child((composition *) p_mono_glyph, 0);
    p_unwrap->pfn_insert(p_unwrap, p_child, i);
}

glyph *mono_glyph_child (mono_glyph *p_mono_glyph, int i)
{
    glyph *p_unwrap = composition_child((composition *) p_mono_glyph, 0);
    return p_unwrap->pfn_child(p_unwrap, i);
}

composition *mono_glyph_composition_get ( mono_glyph *p_mono_glyph )
{
    glyph *p_unwrap = composition_child((composition *) p_mono_glyph, 0);
    return p_unwrap->pfn_composition_get(p_unwrap);
}
