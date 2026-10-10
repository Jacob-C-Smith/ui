#include <glyph/radio_button.h>

void radio_button_click ( circle *p_circle );

radio_button *radio_button_construct( radio_button_group *p_group, const char *text )
{
    radio_button *p_radio_button = default_allocator(NULL, sizeof(radio_button));

    glyph *p_circle = (glyph *)circle_construct((rect){{0}, {30, 30}});
    p_circle->pfn_command_set(p_circle, (command *)radio_button_set_command_construct(p_group, p_radio_button));
    p_circle->pfn_click = (fn_glyph_click *) radio_button_click;

    mono_glyph_construct
    (
        (mono_glyph *)p_radio_button, 
        (glyph *)row_from_arguments
        (
            2, 
            p_circle, 
            row_from_string(text, false, false, 30.0f)
        )
    );

    if ( p_group ) 
        array_add(p_group->p_buttons, p_radio_button);

    return p_radio_button;
}

void radio_button_click ( circle *p_circle )
{
    if ( p_circle->_glyph.p_command ) p_circle->_glyph.p_command->pfn_execute(p_circle->_glyph.p_command);
}
