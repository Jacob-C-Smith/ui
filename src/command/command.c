#include <command/command.h>

command *command_clone ( command *p_command );

int command_construct ( command *p_command )
{
    p_command->pfn_clone = (fn_command_clone *)command_clone;
    p_command->reversable = true;

    return 1;
}

command *command_clone ( command *p_command )
{
    (void) p_command;
    
    printf("Unsupported operation: %s()\n", __FUNCTION__);

    return NULL;
}