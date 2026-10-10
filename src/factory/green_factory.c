#include <factory/green_factory.h>
#include <glyph/button.h>
#include <glyph/label.h>
#include <glyph/checkbox.h>
#include <glyph/checkbox_group.h>
#include <glyph/radio_button.h>
#include <glyph/radio_button_group.h>
#include <glyph/green_menu.h>
#include <glyph/green_menu_item.h>
#include <glyph/green_checkbox.h>
#include <glyph/green_checkbox_group.h>
#include <glyph/green_radio_button.h>
#include <glyph/green_radio_button_group.h>
#include <glyph/green_button.h>
#include <glyph/green_label.h>

static green_gui_factory _green_gui_factory = { 0 };

button             *green_button_construct             ( green_gui_factory *p_green_factory, const char *text );
label              *green_label_construct              ( green_gui_factory *p_green_factory, const char *text );
checkbox_group     *green_checkbox_group_construct     ( green_gui_factory *p_green_factory );
checkbox           *green_checkbox_construct           ( green_gui_factory *p_green_factory, const char *text );
menu               *green_menu_construct_factory       ( green_gui_factory *p_green_factory );
menu_item          *green_menu_item_construct_factory  ( green_gui_factory *p_green_factory, const char *text );
radio_button_group *green_radio_button_group_construct ( green_gui_factory *p_green_factory );
radio_button       *green_radio_button_construct       ( green_gui_factory *p_green_factory, radio_button_group *p_group, const char *text );

int green_gui_factory_construct ( )
{

    _green_gui_factory = (green_gui_factory)
    {
        .p_unique_instance                = &_green_gui_factory,
        .pfn_button_construct             = (fn_gui_factory_button_construct *)             green_button_construct,
        .pfn_label_construct              = (fn_gui_factory_label_construct *)              green_label_construct,
        .pfn_menu_construct               = (fn_gui_factory_menu_construct *)               green_menu_construct_factory,
        .pfn_menu_item_construct          = (fn_gui_factory_menu_item_construct *)          green_menu_item_construct_factory,
        .pfn_checkbox_group_construct     = (fn_gui_factory_checkbox_group_construct *)     green_checkbox_group_construct,
        .pfn_checkbox_construct           = (fn_gui_factory_checkbox_construct *)           green_checkbox_construct,
        .pfn_radio_button_group_construct = (fn_gui_factory_radio_button_group_construct *) green_radio_button_group_construct,
        .pfn_radio_button_construct       = (fn_gui_factory_radio_button_construct *)       green_radio_button_construct,
    };

    return 1;
}

gui_factory *green_gui_factory_instance ( void )
{
    if ( NULL == _green_gui_factory.p_unique_instance )
        green_gui_factory_construct();

    return (gui_factory *)&_green_gui_factory;
}

button *green_button_construct ( green_gui_factory *p_green_factory, const char *text )
{
    (void)p_green_factory;
    button *p_button = button_construct(text);
    p_button->_mono_glyph._composition._glyph.pfn_draw = (fn_glyph_draw *)green_button_draw;
    return p_button;
}

label *green_label_construct ( green_gui_factory *p_green_factory, const char *text )
{
    (void)p_green_factory;
    label *p_label = label_construct(text);
    p_label->_mono_glyph._composition._glyph.pfn_draw = (fn_glyph_draw *)green_label_draw;
    return p_label;
}

menu *green_menu_construct_factory ( green_gui_factory *p_green_factory )
{
    (void)p_green_factory;
    menu *p_menu = menu_construct();
    p_menu->_column._composition._glyph.pfn_draw = (fn_glyph_draw *)green_menu_draw;
    return p_menu;
}

menu_item *green_menu_item_construct_factory ( green_gui_factory *p_green_factory, const char *text )
{
    (void)p_green_factory;
    menu_item *p_menu_item = menu_item_construct(text);
    p_menu_item->_item._composition._glyph.pfn_draw = (fn_glyph_draw *)green_menu_item_draw;
    return p_menu_item;
}

checkbox_group *green_checkbox_group_construct ( green_gui_factory *p_green_factory )
{
    (void)p_green_factory;
    checkbox_group *p_group = checkbox_group_construct();
    p_group->_composition._glyph.pfn_draw = (fn_glyph_draw *)green_checkbox_group_draw;
    return p_group;
}

checkbox *green_checkbox_construct ( green_gui_factory *p_green_factory, const char *text )
{
    (void)p_green_factory;
    checkbox *p_checkbox = checkbox_construct(text);
    p_checkbox->_row._composition._glyph.pfn_draw = (fn_glyph_draw *)green_checkbox_draw;
    return p_checkbox;
}

radio_button_group *green_radio_button_group_construct ( green_gui_factory *p_green_factory )
{
    (void)p_green_factory;
    radio_button_group *p_group = radio_button_group_construct();
    p_group->_composition._glyph.pfn_draw = (fn_glyph_draw *)green_radio_button_group_draw;
    return p_group;
}

radio_button *green_radio_button_construct ( green_gui_factory *p_green_factory, radio_button_group *p_group, const char *text )
{
    (void)p_green_factory;
    radio_button *p_radio_button = radio_button_construct(p_group, text);
    p_radio_button->_row._composition._glyph.pfn_draw = (fn_glyph_draw *)green_radio_button_draw;
    return p_radio_button;
}