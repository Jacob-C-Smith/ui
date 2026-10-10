#include <command/radio_button_set_command.h>

radio_button_set_command *radio_button_set_command_clone ( radio_button_set_command *p_command );
void radio_button_set_command_execute ( radio_button_set_command *p_command );

radio_button_set_command *radio_button_set_command_construct ( radio_button *p_radio_button, int selection )
{
    radio_button_set_command *p_command = default_allocator(NULL, sizeof(radio_button_set_command));
    
    command_construct((command *)p_command);

    p_command->_command.pfn_execute = (fn_command_execute *)radio_button_set_command_execute;
    p_command->_command.pfn_unexecute = NULL;
    p_command->_command.pfn_clone = (fn_command_clone *)radio_button_set_command_clone;
    p_command->_command.reversable = false;
    
    p_command->p_radio_button = p_radio_button;
    p_command->set = selection;

    return p_command;
}

radio_button_set_command *radio_button_set_command_clone ( radio_button_set_command *p_command )
{
    return radio_button_set_command_construct(p_command->p_radio_button, p_command->set);
}

void radio_button_set_command_execute ( radio_button_set_command *p_command )
{
    radio_button *p_radio_button = p_command->p_radio_button;
    glyph *p_glyph = (glyph *)p_radio_button;
    
    for (int i = 0; i < p_radio_button->count; i++)
    {
        glyph *p_row = p_glyph->pfn_child(p_glyph, i);
        circle *p_circle = (circle *)p_row->pfn_child(p_row, 0);
        if ( p_circle )
            p_circle->fill = (i == p_command->set);
    }
    
    if ( p_glyph->p_command )
    {
        radio_button_command *p_rb_cmd = (radio_button_command *)p_glyph->p_command;
        p_rb_cmd->choice = p_command->set;
        p_rb_cmd->_command.pfn_execute((command *)p_rb_cmd);
    }
}
