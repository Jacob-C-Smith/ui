#include <command/radio_button_set_command.h>
#include <glyph/circle.h>
#include <data/array.h>
#include <command/radio_button_command.h>

radio_button_set_command *radio_button_set_command_clone ( radio_button_set_command *p_command );
void radio_button_set_command_execute ( radio_button_set_command *p_command );

radio_button_set_command *radio_button_set_command_construct ( radio_button_group *p_group, radio_button *p_button )
{
    radio_button_set_command *p_command = default_allocator(NULL, sizeof(radio_button_set_command));
    
    command_construct((command *)p_command);

    p_command->_command.pfn_execute = (fn_command_execute *)radio_button_set_command_execute;
    p_command->_command.pfn_unexecute = NULL;
    p_command->_command.pfn_clone = (fn_command_clone *)radio_button_set_command_clone;
    p_command->_command.reversable = false;
    
    p_command->p_group = p_group;
    p_command->p_button = p_button;

    return p_command;
}

radio_button_set_command *radio_button_set_command_clone ( radio_button_set_command *p_command )
{
    return radio_button_set_command_construct(p_command->p_group, p_command->p_button);
}

void radio_button_set_command_execute ( radio_button_set_command *p_command )
{
    radio_button_group *p_group = p_command->p_group;
    radio_button *p_selected = p_command->p_button;
    int selected_idx = -1;
    
    for (int i = 0; i < array_size(p_group->p_buttons); i++)
    {
        radio_button *p_rb = NULL;
        array_index(p_group->p_buttons, i, (void **)&p_rb);
        
        glyph *p_row_glyph = (glyph *)p_rb;
        circle *p_circle = (circle *)p_row_glyph->pfn_child(p_row_glyph, 0);
        if ( p_circle )
            p_circle->fill = (p_rb == p_selected);
            
        if (p_rb == p_selected) selected_idx = i;
    }
    
    if ( p_group->p_command )
    {
        radio_button_command *p_rb_cmd = (radio_button_command *)p_group->p_command;
        p_rb_cmd->choice = selected_idx;
        p_rb_cmd->_command.pfn_execute((command *)p_rb_cmd);
    }
}
