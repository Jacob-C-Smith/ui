#include <glyph/radio_button.h>

void radio_button_click ( circle *p_circle );

radio_button *radio_button_construct( int count, const char *options[] )
{
    radio_button *p_radio_button = default_allocator(NULL, sizeof(radio_button));
    radio_button_command *p_command = radio_button_command_construct(-1);
    column *p_column = column_construct();

    p_radio_button->count = count;

    for (int i = 0; i < count; i++)
    {
        glyph *p_circle = (glyph *)circle_construct((rect){{0}, {25, 25}});

        p_circle->pfn_command_set(p_circle, (command *)radio_button_set_command_construct(p_radio_button, i));
        p_circle->pfn_click = (fn_glyph_click *) radio_button_click;

        glyph *p_option = (glyph *)row_from_arguments
        (
            2, 
            p_circle, 
            row_from_string(options[i],false,false,30.0f)
        );
        
        p_column->_composition._glyph.pfn_insert
        (
            p_column,
            p_option,
            i 
        );
    }

    mono_glyph_construct((mono_glyph *)p_radio_button, (glyph *)p_column);

    p_radio_button->_mono_glyph._composition._glyph.p_command = (command *)p_command;

    return p_radio_button;
}

void radio_button_click ( circle *p_circle )
{
    if ( p_circle->_glyph.p_command ) p_circle->_glyph.p_command->pfn_execute(p_circle->_glyph.p_command);
}