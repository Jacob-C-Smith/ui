#include <window/application_window.h>
#include <glyph/glyph.h>

void window_click ( application_window *p_window, int x, int y );
void window_key   ( application_window *p_window, char c );

application_window *application_window_construct ( const char *p_title )
{
    application_window *p_application_window = default_allocator(NULL, sizeof(application_window));

    window_construct((window *)p_application_window, p_title);

    p_application_window->_window.pfn_click = (fn_window_click *) window_click;
    p_application_window->_window.pfn_key   = (fn_window_key *)   window_key;
    p_application_window->p_focus           = NULL;

    return p_application_window;
}

void window_click ( application_window *p_window, int x, int y ) 
{
    glyph *p_target = NULL;

    if ( NULL == p_window->_window.p_contents ) return;

    p_target = p_window->_window.p_contents->pfn_find(p_window->_window.p_contents, (point){x,y});

    glyph *p_new_focus = NULL;
    for (glyph *curr = p_target; curr != NULL; curr = curr->p_parent)
        if (curr->pfn_focus != NULL && curr->pfn_focus != glyph_focus)
        {
            p_new_focus = curr;
            break;
        }

    if (p_window->p_focus != p_new_focus)
    {
        if (p_window->p_focus && p_window->p_focus->pfn_focus)
            p_window->p_focus->pfn_focus(p_window->p_focus, false);
        p_window->p_focus = p_new_focus;
        if (p_window->p_focus && p_window->p_focus->pfn_focus)
            p_window->p_focus->pfn_focus(p_window->p_focus, true);
    }

    if ( p_target ) 
        p_target->pfn_click(p_target);
}

void window_key ( application_window *p_window, char c )
{
    if ( p_window->p_focus )
    {
        p_window->p_focus->pfn_key(p_window->p_focus, c);
        return;
    }

    command *p_command = NULL;

    if ( NULL == p_window->p_key_map ) return;

    p_command = key_map_get(p_window->p_key_map, c);

    if ( NULL == p_command ) return;

    p_command->pfn_execute(p_command);
}
