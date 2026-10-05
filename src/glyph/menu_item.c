#include <glyph/menu_item.h>

void menu_item_click ( menu_item *p_menu_item );

menu_item *menu_item_construct ( const char *text )
{
    menu_item *p_menu_item = default_allocator(NULL, sizeof(menu_item));

    mono_glyph_construct((mono_glyph *)p_menu_item, (glyph *)row_from_string(text, false, false, 30.0f));

    p_menu_item->_item._composition._glyph.pfn_click = (fn_glyph_click *) menu_item_click;

    return p_menu_item;
}

void menu_item_click ( menu_item *p_menu_item )
{
    if ( p_menu_item->_item._composition._glyph.p_command )
        p_menu_item->_item._composition._glyph.p_command->pfn_execute(p_menu_item->_item._composition._glyph.p_command);
}
