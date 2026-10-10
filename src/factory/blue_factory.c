#include <factory/blue_factory.h>
#include <glyph/button.h>
#include <glyph/label.h>
#include <glyph/checkbox.h>
#include <glyph/checkbox_group.h>
#include <glyph/radio_button.h>
#include <glyph/radio_button_group.h>
#include <glyph/blue_button.h>
#include <glyph/blue_label.h>
#include <glyph/blue_menu.h>
#include <glyph/blue_menu_item.h>
#include <glyph/blue_checkbox.h>
#include <glyph/blue_checkbox_group.h>
#include <glyph/blue_radio_button.h>
#include <glyph/blue_radio_button_group.h>

static blue_gui_factory _blue_gui_factory = { 0 };

button             *blue_button_construct             ( blue_gui_factory *p_blue_factory, const char *text );
label              *blue_label_construct              ( blue_gui_factory *p_blue_factory, const char *text );
checkbox_group     *blue_checkbox_group_construct     ( blue_gui_factory *p_blue_factory );
checkbox           *blue_checkbox_construct           ( blue_gui_factory *p_blue_factory, const char *text );
radio_button_group *blue_radio_button_group_construct ( blue_gui_factory *p_blue_factory );
radio_button       *blue_radio_button_construct       ( blue_gui_factory *p_blue_factory, radio_button_group *p_group, const char *text );
menu               *blue_menu_construct_factory       ( blue_gui_factory *p_blue_factory );
menu_item          *blue_menu_item_construct_factory  ( blue_gui_factory *p_blue_factory, const char *text );

int blue_gui_factory_construct ( void )
{

    _blue_gui_factory = (blue_gui_factory)
    {
        .p_unique_instance                = &_blue_gui_factory,
        .pfn_button_construct             = (fn_gui_factory_button_construct *)             blue_button_construct,
        .pfn_label_construct              = (fn_gui_factory_label_construct *)              blue_label_construct,
        .pfn_menu_construct               = (fn_gui_factory_menu_construct *)               blue_menu_construct_factory,
        .pfn_menu_item_construct          = (fn_gui_factory_menu_item_construct *)          blue_menu_item_construct_factory,
        .pfn_checkbox_group_construct     = (fn_gui_factory_checkbox_group_construct *)     blue_checkbox_group_construct,
        .pfn_checkbox_construct           = (fn_gui_factory_checkbox_construct *)           blue_checkbox_construct,
        .pfn_radio_button_group_construct = (fn_gui_factory_radio_button_group_construct *) blue_radio_button_group_construct,
        .pfn_radio_button_construct       = (fn_gui_factory_radio_button_construct *)       blue_radio_button_construct,
    };

    return 1;
}

gui_factory *blue_gui_factory_instance ( void )
{
    if ( NULL == _blue_gui_factory.p_unique_instance )
        blue_gui_factory_construct();

    return (gui_factory *)&_blue_gui_factory;
}

button *blue_button_construct ( blue_gui_factory *p_blue_factory, const char *text )
{
    (void)p_blue_factory;
    button *p_button = button_construct(text);
    p_button->_mono_glyph._composition._glyph.pfn_draw = (fn_glyph_draw *)blue_button_draw;
    return p_button;
}

label *blue_label_construct ( blue_gui_factory *p_blue_factory, const char *text )
{
    (void)p_blue_factory;
    label *p_label = label_construct(text);
    p_label->_mono_glyph._composition._glyph.pfn_draw = (fn_glyph_draw *)blue_label_draw;
    return p_label;
}

menu *blue_menu_construct_factory ( blue_gui_factory *p_blue_factory )
{
    (void)p_blue_factory;
    menu *p_menu = menu_construct();
    p_menu->_column._composition._glyph.pfn_draw = (fn_glyph_draw *)blue_menu_draw;
    return p_menu;
}

menu_item *blue_menu_item_construct_factory ( blue_gui_factory *p_blue_factory, const char *text )
{
    (void)p_blue_factory;
    menu_item *p_menu_item = menu_item_construct(text);
    p_menu_item->_item._composition._glyph.pfn_draw = (fn_glyph_draw *)blue_menu_item_draw;
    return p_menu_item;
}

checkbox_group *blue_checkbox_group_construct ( blue_gui_factory *p_blue_factory )
{
    (void)p_blue_factory;
    checkbox_group *p_group = checkbox_group_construct();
    p_group->_composition._glyph.pfn_draw = (fn_glyph_draw *)blue_checkbox_group_draw;
    return p_group;
}

checkbox *blue_checkbox_construct ( blue_gui_factory *p_blue_factory, const char *text )
{
    (void)p_blue_factory;
    checkbox *p_checkbox = checkbox_construct(text);
    p_checkbox->_row._composition._glyph.pfn_draw = (fn_glyph_draw *)blue_checkbox_draw;
    return p_checkbox;
}

radio_button_group *blue_radio_button_group_construct ( blue_gui_factory *p_blue_factory )
{
    (void)p_blue_factory;
    radio_button_group *p_group = radio_button_group_construct();
    p_group->_composition._glyph.pfn_draw = (fn_glyph_draw *)blue_radio_button_group_draw;
    return p_group;
}

radio_button *blue_radio_button_construct ( blue_gui_factory *p_blue_factory, radio_button_group *p_group, const char *text )
{
    (void)p_blue_factory;
    radio_button *p_radio_button = radio_button_construct(p_group, text);
    p_radio_button->_row._composition._glyph.pfn_draw = (fn_glyph_draw *)blue_radio_button_draw;
    return p_radio_button;
}