#include <factory/blue_factory.h>
#include <glyph/button.h>
#include <glyph/label.h>

static blue_gui_factory _blue_gui_factory = { 0 };

button *blue_button_construct ( blue_gui_factory *p_blue_factory, const char *text );
label  *blue_label_construct ( blue_gui_factory *p_blue_factory, const char *text );

int blue_gui_factory_construct ( )
{
    _blue_gui_factory.p_unique_instance = &_blue_gui_factory;
    _blue_gui_factory.pfn_button_construct = (fn_gui_factory_button_construct *) blue_button_construct;
    _blue_gui_factory.pfn_label_construct = (fn_gui_factory_label_construct *) blue_label_construct;
    return 1;
}

gui_factory *blue_gui_factory_instance ( void )
{
    if ( NULL == _blue_gui_factory.p_unique_instance )
    {
        blue_gui_factory_construct();
    }

    return (gui_factory *)&_blue_gui_factory;
}

button *blue_button_construct ( blue_gui_factory *p_blue_factory, const char *text )
{
    button *p_button = button_construct(text);
    p_button->_mono_glyph._composition._glyph.pfn_draw = (fn_glyph_draw *)blue_button_draw;
    return p_button;
}

label *blue_label_construct ( blue_gui_factory *p_blue_factory, const char *text )
{
    label *p_label = label_construct(text);
    p_label->_mono_glyph._composition._glyph.pfn_draw = (fn_glyph_draw *)blue_label_draw;
    return p_label;
}