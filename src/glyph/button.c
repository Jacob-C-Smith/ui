#include <glyph/button.h>

void button_command_set ( button *p_button, command *p_command );
command *button_command_get ( button *p_button );
void button_click ( button *p_button );

button *button_construct ( const char *text )
{
    button *p_button = default_allocator(NULL, sizeof(button));

    mono_glyph_construct((mono_glyph *)p_button, (glyph *)row_from_string(text, false, false, 30.0f));

    p_button->pfn_command_get = button_command_get;
    p_button->pfn_command_set = button_command_set;
    p_button->_mono_glyph._composition._glyph.pfn_click = (fn_glyph_click *) button_click;

    return p_button;
}

void button_command_set ( button *p_button, command *p_command )
{
    p_button->p_command = p_command;
}

command *button_command_get ( button *p_button )
{
    return p_button->p_command;
}

void button_click ( button *p_button )
{
    if ( p_button->p_command ) p_button->p_command->pfn_execute(p_button->p_command);
}