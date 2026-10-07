#include <glyph/checkbox.h>

void checkbox_click ( rectangle *p_rectangle );

checkbox *checkbox_construct( int count, const char *options[] )
{
    checkbox *p_checkbox = default_allocator(NULL, sizeof(checkbox));
    checkbox_command *p_command = checkbox_command_construct(-1);
    column *p_column = column_construct();

    for (int i = 0; i < count; i++)
    {
        glyph *p_rectangle = (glyph *)rectangle_construct((rect){{0}, {25, 25}});

        p_rectangle->pfn_command_set(p_rectangle, (command *)checkbox_set_command_construct(p_checkbox, i));
        p_rectangle->pfn_click = (fn_glyph_click *) checkbox_click;

        glyph *p_option = (glyph *)row_from_arguments
        (
            2, 
            p_rectangle, 
            row_from_string(options[i],false,false,30.0f)
        );
        
        p_column->_composition._glyph.pfn_insert
        (
            p_column,
            p_option,
            i 
        );
    }

    mono_glyph_construct((mono_glyph *)p_checkbox, (glyph *)p_column);

    p_checkbox->_mono_glyph._composition._glyph.p_command = p_command;

    return p_checkbox;
}

void checkbox_click ( rectangle *p_rectangle )
{
    p_rectangle->fill = !p_rectangle->fill;
    if ( p_rectangle->_glyph.p_command ) p_rectangle->_glyph.p_command->pfn_execute(p_rectangle->_glyph.p_command);
}