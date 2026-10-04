#pragma once

#include <ui/ui.h>

int glyph_construct ( glyph *p_glyph );

void         glyph_draw            ( glyph *p_glyph, window *p_window );
window      *glyph_window_get      ( glyph *p_glyph );
void         glyph_position_set    ( glyph *p_glyph, point _point );
point        glyph_position_get    ( glyph *p_glyph );
void         glyph_compose         ( glyph *p_glyph );
void         glyph_size            ( glyph *p_glyph, window *p_window );
rect         glyph_bounds_get      ( glyph *p_glyph );
glyph       *glyph_parent_get      ( glyph *p_glyph );
composition *glyph_composition_get ( glyph *p_glyph );
bool         glyph_intersects      ( glyph *p_glyph, point p );
void         glyph_parent_set      ( glyph *p_glyph, glyph *p_parent );
void         glyph_window_set      ( glyph *p_glyph, window *p_window );
void         glyph_bounds_set      ( glyph *p_glyph, rect bounds );
point        glyph_cursor          ( glyph *p_glyph );
point        glyph_adjust_child    ( glyph *p_glyph, glyph *p_child, point cursor );
void         glyph_adjust          ( glyph *p_glyph, point cursor );
void         glyph_insert          ( glyph *p_glyph, glyph *p_child, int i );
void         glyph_remove          ( glyph *p_glyph, glyph *p_child );
glyph       *glyph_child           ( glyph *p_glyph, int i );
iterator     glyph_iterator        ( glyph *p_glyph );
glyph       *glyph_find            ( glyph *p_glyph, point p );
void         glyph_click           ( glyph *p_glyph );
void         glyph_key             ( glyph *p_glyph, char c );