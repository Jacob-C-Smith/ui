#include <glyph/red_menu_item.h>

void red_menu_item_draw ( red_menu_item *p_red_menu_item, window *p_window )
{
    composition_draw((composition *)p_red_menu_item, p_window);
}
