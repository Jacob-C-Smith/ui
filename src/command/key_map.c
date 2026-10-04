#include <command/key_map.h>

key_map *key_map_construct ( void )
{
    array *p_key_map = NULL;

    array_construct(&p_key_map, 256);

    for (int i = 0; i < 255; i++)
        array_add(p_key_map, NULL);
    
    return p_key_map;
}

command *key_map_get ( key_map *p_key_map, char c )
{
    command *p_command = NULL;
    
    array_index(p_key_map, (signed int) c, (void **)&p_command);

    return p_command;
}

void key_map_put ( key_map *p_key_map, char c, command *p_command )
{
    array_set(p_key_map, (signed int)c, (void *)p_command);
}
