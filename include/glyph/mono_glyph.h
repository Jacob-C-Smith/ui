#pragma once

#include <ui/ui.h>

#include <glyph/composition.h>

int mono_glyph_construct ( mono_glyph *p_mono_glyph, glyph *p_glyph );

void mono_glyph_position_set ( mono_glyph *p_mono_glyph, point _point );
void mono_glyph_compose ( mono_glyph *p_mono_glyph );
void mono_glyph_size ( mono_glyph *p_mono_glyph, window *p_window );
void mono_glyph_adjust (  mono_glyph *p_mono_glyph, point cursor );
point mono_glyph_adjust_child (  mono_glyph *p_mono_glyph, glyph *p_child, point cursor );
void mono_glyph_insert ( mono_glyph *p_mono_glyph, glyph *p_child, int i );
glyph *mono_glyph_child ( mono_glyph *p_mono_glyph, int i );
composition *mono_glyph_composition_get (  mono_glyph *p_mono_glyph );
