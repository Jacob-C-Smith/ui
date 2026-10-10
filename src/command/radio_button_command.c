#include <command/radio_button_command.h>

radio_button_command *radio_button_command_clone ( radio_button_command *p_command );
void radio_button_command_execute ( radio_button_command *p_command );

radio_button_command *radio_button_command_construct ( int choice )
{
    radio_button_command *p_command = default_allocator(NULL, sizeof(radio_button_command));
    
    command_construct((command *)p_command);

    p_command->_command.pfn_execute = (fn_command_execute *)radio_button_command_execute;
    p_command->_command.pfn_unexecute = NULL;
    p_command->_command.pfn_clone = (fn_command_clone *)radio_button_command_clone;
    p_command->_command.reversable = false;
    
    p_command->choice = choice;

    return p_command;
}

radio_button_command *radio_button_command_clone ( radio_button_command *p_command )
{
    return radio_button_command_construct(p_command->choice);
}

void radio_button_command_execute ( radio_button_command *p_command )
{
    printf("radio_button command : %d\n", p_command->choice);
}
