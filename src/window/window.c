#include <window/window.h>

int  window_draw         ( window *p_window );
int  window_redraw       ( window *p_window );
int  window_raise        ( window *p_window );
int  window_lower        ( window *p_window );
int  window_iconify      ( window *p_window );
int  window_deiconify    ( window *p_window );
int  window_set_contents ( window *p_window, glyph *p_glyph );
void window_draw_char    ( window *p_window, char c, bool bold, bool italic, float size, int x, int y );
void window_draw_rect    ( window *p_window, int x, int y, int w, int h );
void window_fill_rect    ( window *p_window, int x, int y, int w, int h );
void window_clear_rect   ( window *p_window, int x, int y, int w, int h );
void window_draw_button  ( window *p_window, int x, int y, int w, int h, const char *p_button );
void window_draw_label   ( window *p_window, int x, int y, int w, int h, const char *p_label );
int  window_char_width   ( window *p_window, char c, bool bold, bool italic, float size );
int  window_char_height  ( window *p_window, char c, bool bold, bool italic, float size );

int window_construct ( window *p_window, const char *p_title )
{
    window_factory *p_window_factory = window_factory_instance();

    *p_window = (window)
    {
        .pfn_draw         = window_draw,       
        .pfn_redraw       = window_redraw,         
        .pfn_raise        = window_raise,        
        .pfn_lower        = window_lower,        
        .pfn_iconify      = window_iconify,          
        .pfn_deiconify    = window_deiconify,            
        .pfn_set_contents = window_set_contents,               
        .pfn_draw_char    = window_draw_char,            
        .pfn_draw_rect    = window_draw_rect,            
        .pfn_fill_rect    = window_fill_rect, 
        .pfn_clear_rect   = window_clear_rect,           
        .pfn_draw_button  = window_draw_button,              
        .pfn_draw_label   = window_draw_label,             
        .pfn_char_width   = window_char_width,             
        .pfn_char_height  = window_char_height,              
        .p_title          = p_title,      
        .p_impl           = p_window_factory->pfn_window_imp_construct(p_window_factory, p_title, p_window), 
        .p_contents       = NULL,         
    };

    return 1;
}

int window_draw ( window *p_window ) 
{ 
    if ( p_window->p_contents )
        p_window->p_contents->pfn_draw(p_window->p_contents, p_window);

    return 1;
}
int window_redraw    ( window *p_window ) { return p_window->p_impl->pfn_redraw(p_window->p_impl); }
int window_raise     ( window *p_window ) { return p_window->p_impl->pfn_raise(p_window->p_impl); }
int window_lower     ( window *p_window ) { return p_window->p_impl->pfn_lower(p_window->p_impl); }
int window_iconify   ( window *p_window ) { return p_window->p_impl->pfn_iconify(p_window->p_impl); }
int window_deiconify ( window *p_window ) { return p_window->p_impl->pfn_deiconify(p_window->p_impl); }

int window_set_contents ( window *p_window, glyph *p_glyph ) 
{ 
    p_window->p_contents = p_glyph;
    p_window->p_contents->pfn_window_set(p_glyph, p_window);
    p_window->p_impl->pfn_set_contents(p_window->p_impl);
    return 1;
}

void window_draw_char   ( window *p_window, char c, bool bold, bool italic, float size, int x, int y ) { return p_window->p_impl->pfn_draw_char(p_window->p_impl, c, bold, italic, size, x, y); }
void window_draw_rect   ( window *p_window, int x, int y, int w, int h )                       { return p_window->p_impl->pfn_draw_rect(p_window->p_impl, x, y, w, h); }
void window_fill_rect   ( window *p_window, int x, int y, int w, int h )                       { return p_window->p_impl->pfn_fill_rect(p_window->p_impl, x, y, w, h); }
void window_clear_rect  ( window *p_window, int x, int y, int w, int h )                       { return p_window->p_impl->pfn_clear_rect(p_window->p_impl, x, y, w, h); }
void window_draw_button ( window *p_window, int x, int y, int w, int h, const char *p_button ) { return p_window->p_impl->pfn_draw_button(p_window->p_impl, x, y, w, h, p_button); }
void window_draw_label  ( window *p_window, int x, int y, int w, int h, const char *p_label )  { return p_window->p_impl->pfn_draw_label(p_window->p_impl, x, y, w, h, p_label); }
int window_char_width   ( window *p_window, char c, bool bold, bool italic, float size )       { return p_window->p_impl->pfn_char_width(p_window->p_impl, c, bold, italic, size); }
int window_char_height  ( window *p_window, char c, bool bold, bool italic, float size )       { return p_window->p_impl->pfn_char_height(p_window->p_impl, c, bold, italic, size); }
