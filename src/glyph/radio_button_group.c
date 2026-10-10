#include <glyph/radio_button_group.h>
#include <command/radio_button_command.h>
#include <data/array.h>

radio_button_group *radio_button_group_construct ( void )
{
    radio_button_group *p_group = default_allocator(NULL, sizeof(radio_button_group));
    composition_construct((composition *)p_group);
    array_construct(&p_group->p_buttons, 16);
    p_group->p_command = (command *)radio_button_command_construct(-1);
    return p_group;
}
