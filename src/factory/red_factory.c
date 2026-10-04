#include <factory/red_factory.h>
#include <glyph/button.h>
#include <glyph/label.h>

static red_gui_factory _red_gui_factory = { 0 };

button *red_button_construct ( red_gui_factory *p_red_factory );
label  *red_label_construct ( red_gui_factory *p_red_factory );

int red_gui_factory_construct ( )
{
    _red_gui_factory.p_unique_instance = &_red_gui_factory;
    _red_gui_factory.pfn_button_construct = (fn_gui_factory_button_construct *) red_button_construct;
    _red_gui_factory.pfn_label_construct = (fn_gui_factory_label_construct *) red_label_construct;
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

button *red_button_construct ( red_gui_factory *p_red_factory )
{
    button *p_button = button_construct();
    p_button->_mono_glyph._composition._glyph.pfn_draw = (fn_glyph_draw *)red_button_draw;
    return p_button;
}

label *red_label_construct ( red_gui_factory *p_red_factory )
{
    label *p_label = label_construct();
    p_label->_mono_glyph._composition._glyph.pfn_draw = (fn_glyph_draw *)red_label_draw;
    return p_label;
}