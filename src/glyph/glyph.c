#include <glyph/glyph.h>

int glyph_construct ( glyph *p_glyph )
{
    *p_glyph = (glyph)
    {
        .pfn_draw            = (fn_glyph_draw *)            glyph_draw,
        .pfn_window_get      = (fn_glyph_window_get *)      glyph_window_get,
        .pfn_position_set    = (fn_glyph_position_set *)    glyph_position_set,
        .pfn_position_get    = (fn_glyph_position_get *)    glyph_position_get,
        .pfn_compose         = (fn_glyph_compose *)         glyph_compose,
        .pfn_size            = (fn_glyph_size *)            glyph_size,
        .pfn_bounds_get      = (fn_glyph_bounds_get *)      glyph_bounds_get,
        .pfn_parent_get      = (fn_glyph_parent_get *)      glyph_parent_get,
        .pfn_composition_get = (fn_glyph_composition_get *) glyph_composition_get,
        .pfn_intersects      = (fn_glyph_intersects *)      glyph_intersects,
        .pfn_parent_set      = (fn_glyph_parent_set *)      glyph_parent_set,
        .pfn_window_set      = (fn_glyph_window_set *)      glyph_window_set,
        .pfn_bounds_set      = (fn_glyph_bounds_set *)      glyph_bounds_set,
        .pfn_cursor          = (fn_glyph_cursor *)          glyph_cursor,
        .pfn_adjust_child    = (fn_glyph_adjust_child *)    glyph_adjust_child,
        .pfn_adjust          = (fn_glyph_adjust *)          glyph_adjust,
        .pfn_insert          = (fn_glyph_insert *)          glyph_insert,
        .pfn_remove          = (fn_glyph_remove *)          glyph_remove,
        .pfn_child           = (fn_glyph_child *)           glyph_child,
        .pfn_iterator        = (fn_glyph_iterator *)        glyph_iterator,
    };

    return 1;
}

void         glyph_draw            ( glyph *p_glyph, window *p_window ) { (void) p_glyph; (void) p_window; printf("Error: Unsupported operation in call to function \"%s\"\n", __FUNCTION__); }
window      *glyph_window_get      ( glyph *p_glyph ) { if (p_glyph->p_window) return p_glyph->p_window; if ( p_glyph->p_parent) return p_glyph->p_parent->pfn_window_get(p_glyph->p_parent); return NULL; }
void         glyph_position_set    ( glyph *p_glyph, point _point ) { p_glyph->_bounds.origin = _point; }
point        glyph_position_get    ( glyph *p_glyph ) { return p_glyph->_bounds.origin; }
void         glyph_compose         ( glyph *p_glyph ) { (void) p_glyph; }
void         glyph_size            ( glyph *p_glyph, window *p_window ) { (void) p_glyph; (void) p_window; };
rect         glyph_bounds_get      ( glyph *p_glyph ) { return p_glyph->_bounds; }
glyph       *glyph_parent_get      ( glyph *p_glyph ) { return p_glyph->p_parent; }
composition *glyph_composition_get ( glyph *p_glyph ) { (void) p_glyph; return NULL; }
bool         glyph_intersects      ( glyph *p_glyph, point p ) { (void) p_glyph; (void) p; return false; }
void         glyph_parent_set      ( glyph *p_glyph, glyph *p_parent ) { p_glyph->p_parent = p_parent; }
void         glyph_window_set      ( glyph *p_glyph, window *p_window ) { p_glyph->p_window = p_window; }
void         glyph_bounds_set      ( glyph *p_glyph, rect bounds ) { p_glyph->_bounds = bounds; }
point        glyph_cursor          ( glyph *p_glyph ) { (void) p_glyph; return (point) { 0 }; }
point        glyph_adjust_child    ( glyph *p_glyph, glyph *p_child, point cursor ) { (void)p_glyph; (void)p_child; return cursor; }
void         glyph_adjust          ( glyph *p_glyph, point cursor ) { (void)p_glyph; (void)cursor; }
void         glyph_insert          ( glyph *p_glyph, glyph *p_child, int i ) { (void) p_glyph; (void) p_child; (void) i; }
void         glyph_remove          ( glyph *p_glyph, glyph *p_child ) { (void) p_glyph; (void) p_child;}
glyph       *glyph_child           ( glyph *p_glyph, int i ) { (void) p_glyph; (void) i; return NULL; }
iterator     glyph_iterator        ( glyph *p_glyph ) { (void) p_glyph; return (iterator){ }; }