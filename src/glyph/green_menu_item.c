#include <glyph/green_menu_item.h>

void green_menu_item_draw ( green_menu_item *p_green_menu_item, window *p_window )
{
    composition_draw((composition *)p_green_menu_item, p_window);
}
