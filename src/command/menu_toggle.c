#include <command/menu_toggle.h>
#include <core/interfaces.h>

void menu_toggle_execute ( command *p_command )
{
    menu_toggle *p_toggle = (menu_toggle *)p_command;
    p_toggle->p_menu->_open = !p_toggle->p_menu->_open;
}

menu_toggle *menu_toggle_construct ( menu *p_menu )
{
    menu_toggle *p_toggle = default_allocator(NULL, sizeof(menu_toggle));
    p_toggle->_command.pfn_execute = menu_toggle_execute;
    p_toggle->_command.pfn_unexecute = NULL;
    p_toggle->_command.pfn_clone = NULL;
    p_toggle->_command.reversable = false;
    p_toggle->p_menu = p_menu;
    return p_toggle;
}
