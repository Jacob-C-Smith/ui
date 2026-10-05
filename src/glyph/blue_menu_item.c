#include <glyph/blue_menu_item.h>

void blue_menu_item_draw ( blue_menu_item *p_blue_menu_item, window *p_window )
{
    rect b = p_blue_menu_item->_menu_item._item._composition._glyph._bounds;

    p_window->pfn_clear_rect(
        p_window, 
        b.origin.x,
        b.origin.y, 
        b.extent.x, 
        b.extent.y
    );

    composition_draw((composition *)p_blue_menu_item, p_window);
}
