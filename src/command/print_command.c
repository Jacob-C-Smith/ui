#include <command/print_command.h>

print_command *print_command_clone ( print_command *p_command );
void print_command_execute ( print_command *p_command );

print_command *print_command_construct ( const char *p_text )
{
    print_command *p_command = default_allocator(NULL, sizeof(print_command));
    
    command_construct((command *)p_command);

    p_command->_command.pfn_execute = (fn_command_execute *)print_command_execute;
    p_command->_command.pfn_unexecute = NULL;
    p_command->_command.pfn_clone = (fn_command_clone *)print_command_clone;
    p_command->_command.reversable = false;
    
    p_command->text = p_text;

    return p_command;
}

print_command *print_command_clone ( print_command *p_command )
{
    return print_command_construct(p_command->text);
}

void print_command_execute ( print_command *p_command )
{
    printf("print command : %s\n", p_command->text);
}
