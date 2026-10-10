#include <glyph/blue_menu_item.h>

void blue_menu_item_draw ( blue_menu_item *p_blue_menu_item, window *p_window )
{
    composition_draw((composition *)p_blue_menu_item, p_window);
}
