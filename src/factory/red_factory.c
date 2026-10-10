#include <factory/red_factory.h>
#include <glyph/button.h>
#include <glyph/label.h>
#include <glyph/red_menu.h>
#include <glyph/red_menu_item.h>
#include <glyph/red_checkbox.h>
#include <glyph/red_radio_button.h>
#include <glyph/checkbox.h>
#include <glyph/radio_button.h>

static red_gui_factory _red_gui_factory = { 0 };

button *red_button_construct ( red_gui_factory *p_red_factory, const char *text );
label  *red_label_construct ( red_gui_factory *p_red_factory, const char *text );
checkbox *red_checkbox_construct ( red_gui_factory *p_red_factory, int choices, const char *options[] );
menu *red_menu_construct_factory ( red_gui_factory *p_red_factory );
menu_item *red_menu_item_construct_factory ( red_gui_factory *p_red_factory, const char *text );
radio_button  *red_radio_button_construct      ( red_gui_factory *p_red_factory, int count, const char *options[] );

int red_gui_factory_construct ( )
{
    _red_gui_factory.p_unique_instance = &_red_gui_factory;
    _red_gui_factory.pfn_button_construct = (fn_gui_factory_button_construct *) red_button_construct;
    _red_gui_factory.pfn_label_construct = (fn_gui_factory_label_construct *) red_label_construct;
    _red_gui_factory.pfn_menu_construct = (fn_gui_factory_menu_construct *) red_menu_construct_factory;
    _red_gui_factory.pfn_menu_item_construct = (fn_gui_factory_menu_item_construct *) red_menu_item_construct_factory;
    _red_gui_factory.pfn_checkbox_construct = (fn_gui_factory_checkbox_construct *) red_checkbox_construct;
    _red_gui_factory.pfn_radio_button_construct = (fn_gui_factory_radio_button_construct *) red_radio_button_construct;
    return 1;
}

gui_factory *red_gui_factory_instance ( void )
{
    if ( NULL == _red_gui_factory.p_unique_instance )
    {
        red_gui_factory_construct();
    }

    return (gui_factory *)&_red_gui_factory;
}

button *red_button_construct ( red_gui_factory *p_red_factory, const char *text )
{
    (void)p_red_factory;
    button *p_button = button_construct(text);
    p_button->_mono_glyph._composition._glyph.pfn_draw = (fn_glyph_draw *)red_button_draw;
    return p_button;
}

label *red_label_construct ( red_gui_factory *p_red_factory, const char *text )
{
    (void)p_red_factory;
    label *p_label = label_construct(text);
    p_label->_mono_glyph._composition._glyph.pfn_draw = (fn_glyph_draw *)red_label_draw;
    return p_label;
}

menu *red_menu_construct_factory ( red_gui_factory *p_red_factory )
{
    (void)p_red_factory;
    menu *p_menu = menu_construct();
    p_menu->_column._composition._glyph.pfn_draw = (fn_glyph_draw *)red_menu_draw;
    return p_menu;
}

menu_item *red_menu_item_construct_factory ( red_gui_factory *p_red_factory, const char *text )
{
    (void)p_red_factory;
    menu_item *p_menu_item = menu_item_construct(text);
    p_menu_item->_item._composition._glyph.pfn_draw = (fn_glyph_draw *)red_menu_item_draw;
    return p_menu_item;
}
checkbox *red_checkbox_construct ( red_gui_factory *p_red_factory, int choices, const char *options[] )
{
    (void)p_red_factory;
    checkbox *p_checkbox = checkbox_construct(choices, options);
    p_checkbox->_mono_glyph._composition._glyph.pfn_draw = (fn_glyph_draw *)red_checkbox_draw;
    return p_checkbox;
}

radio_button *red_radio_button_construct ( red_gui_factory *p_red_factory, int count, const char *options[] )
{
    (void)p_red_factory;
    radio_button *p_radio_button = radio_button_construct(count, options);
    p_radio_button->_mono_glyph._composition._glyph.pfn_draw = (fn_glyph_draw *)red_radio_button_draw;
    return p_radio_button;
}