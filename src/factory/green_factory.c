#include <factory/green_factory.h>
#include <glyph/button.h>
#include <glyph/label.h>

static green_gui_factory _green_gui_factory = { 0 };

button *green_button_construct ( green_gui_factory *p_green_factory );
label  *green_label_construct ( green_gui_factory *p_green_factory );

int green_gui_factory_construct ( )
{
    _green_gui_factory.p_unique_instance = &_green_gui_factory;
    _green_gui_factory.pfn_button_construct = (fn_gui_factory_button_construct *) green_button_construct;
    _green_gui_factory.pfn_label_construct = (fn_gui_factory_label_construct *) green_label_construct;
    return 1;
}

gui_factory *green_gui_factory_instance ( void )
{
    if ( NULL == _green_gui_factory.p_unique_instance )
    {
        green_gui_factory_construct();
    }

    return (gui_factory *)&_green_gui_factory;
}

button *green_button_construct ( green_gui_factory *p_green_factory )
{
    button *p_button = button_construct();
    p_button->_mono_glyph._composition._glyph.pfn_draw = (fn_glyph_draw *)green_button_draw;
    return p_button;
}

label *green_label_construct ( green_gui_factory *p_green_factory )
{
    label *p_label = label_construct();
    p_label->_mono_glyph._composition._glyph.pfn_draw = (fn_glyph_draw *)green_label_draw;
    return p_label;
}