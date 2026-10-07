#include <command/checkbox_set_command.h>

checkbox_set_command *checkbox_set_command_clone ( checkbox_set_command *p_command );
void checkbox_set_command_execute ( checkbox_set_command *p_command );

checkbox_set_command *checkbox_set_command_construct ( checkbox *p_checkbox, int selection )
{
    checkbox_set_command *p_command = default_allocator(NULL, sizeof(checkbox_set_command));
    
    command_construct((command *)p_command);

    p_command->_command.pfn_execute = (fn_command_execute *)checkbox_set_command_execute;
    p_command->_command.pfn_unexecute = NULL;
    p_command->_command.pfn_clone = (fn_command_clone *)checkbox_set_command_clone;
    p_command->_command.reversable = false;
    
    p_command->p_checkbox = p_checkbox;
    p_command->set = selection;

    return p_command;
}

checkbox_set_command *checkbox_set_command_clone ( checkbox_set_command *p_command )
{
    return checkbox_set_command_construct(p_command->p_checkbox, p_command->set);
}

void checkbox_set_command_execute ( checkbox_set_command *p_command )
{
    printf("checkbox set command : %d\n", p_command->set);
}
