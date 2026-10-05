#include <glyph/red_menu.h>

void red_menu_draw ( red_menu *p_red_menu, window *p_window )
{
    menu *p_menu = (menu *)p_red_menu;
    rect b;
    
    if ( p_menu->_open )
    {
        b = p_menu->_column._composition._glyph._bounds;
    }
    else
    {
        glyph *p_first = p_menu->_column._composition._glyph.pfn_child((glyph *)p_menu, 0);
        if ( p_first ) b = p_first->pfn_bounds_get(p_first);
        else b = p_menu->_column._composition._glyph._bounds;
    }

    p_window->pfn_clear_rect(
        p_window, 
        b.origin.x,
        b.origin.y, 
        b.extent.x, 
        b.extent.y
    );

    menu_draw(p_menu, p_window);
}
