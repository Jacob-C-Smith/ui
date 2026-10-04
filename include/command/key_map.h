#pragma once

#include <ui/ui.h>

key_map *key_map_construct ( void );
command *key_map_get ( key_map *p_key_map, char c );
void key_map_put ( key_map *p_key_map, char c, command *p_command );
