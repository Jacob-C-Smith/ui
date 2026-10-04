#pragma once

#include <ui/ui.h>
#include <glyph/glyph.h>
#include <compositor/simple_compositor.h>

#include <data/array.h>

int composition_construct ( composition *p_composition );

void composition_window_set ( composition *p_composition, window *p_window );
void composition_insert ( composition *p_composition, glyph *p_child, int i );
glyph *composition_child ( composition *p_composition, int i );
void composition_draw ( composition *p_composition, window *p_window );
rect composition_bounds_get ( composition *p_composition );
composition *composition_composition_get ( composition *p_composition );
void composition_compose ( composition *p_composition );
point composition_position_get ( composition *p_composition );
void composition_position_set ( composition *p_composition, point _point );
void composition_adjust (  composition *p_composition, point cursor );
point composition_adjust_child (  composition *p_composition, glyph *p_child, point cursor );
point composition_cursor ( composition *p_composition );
void composition_size ( composition *p_composition, window *p_window );
iterator composition_iterator ( composition *p_composition );
glyph *composition_find ( composition *p_composition, point p );
bool composition_intersects ( composition *p_composition, point p );