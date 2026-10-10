#include <glyph/blue_menu.h>

void blue_menu_draw ( blue_menu *p_blue_menu, window *p_window )
{
    menu *p_menu = (menu *)p_blue_menu;
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

    p_window->pfn_draw_label(
        p_window, 
        b.origin.x,
        b.origin.y, 
        b.extent.x, 
        b.extent.y,
        "blue"
    );
    
    menu_draw(p_menu, p_window);
}
