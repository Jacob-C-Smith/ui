#include <command/checkbox_command.h>

checkbox_command *checkbox_command_clone ( checkbox_command *p_command );
void checkbox_command_execute ( checkbox_command *p_command );

checkbox_command *checkbox_command_construct ( int choice )
{
    checkbox_command *p_command = default_allocator(NULL, sizeof(checkbox_command));
    
    command_construct((command *)p_command);

    p_command->_command.pfn_execute = (fn_command_execute *)checkbox_command_execute;
    p_command->_command.pfn_unexecute = NULL;
    p_command->_command.pfn_clone = (fn_command_clone *)checkbox_command_clone;
    p_command->_command.reversable = false;
    
    p_command->choice = choice;

    return p_command;
}

checkbox_command *checkbox_command_clone ( checkbox_command *p_command )
{
    return checkbox_command_construct(p_command->choice);
}

void checkbox_command_execute ( checkbox_command *p_command )
{
    printf("checkbox command : %d\n", p_command->choice);
}
