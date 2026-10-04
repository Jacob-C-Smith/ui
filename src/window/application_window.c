#include <window/application_window.h>

void window_click ( application_window *p_window, int x, int y );
void window_key   ( application_window *p_window, char c );

application_window *application_window_construct ( const char *p_title )
{
    application_window *p_application_window = default_allocator(NULL, sizeof(application_window));

    window_construct((window *)p_application_window, p_title);

    p_application_window->_window.pfn_click = (fn_window_click *) window_click;
    p_application_window->_window.pfn_key   = (fn_window_key *)   window_key;

    return p_application_window;
}

void window_click ( application_window *p_window, int x, int y ) 
{
    glyph *p_target = NULL;

    if ( NULL == p_window->_window.p_contents ) return;

    p_target = p_window->_window.p_contents->pfn_find(p_window->_window.p_contents, (point){x,y});

    if ( p_target ) 
        p_target->pfn_click(p_target);
}

void window_key ( application_window *p_window, char c )
{
    command *p_command = NULL;

    if ( NULL == p_window->p_key_map ) return;

    p_command = key_map_get(p_window->p_key_map, c);

    if ( NULL == p_command ) return;

    p_command->pfn_execute(p_command);
}
