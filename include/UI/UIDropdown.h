#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include <JSON/JSON.h>

#include <UI/UItypedef.h>
#include <UI/UIWindow.h>

struct UIDropdown_s
{
    // ID
    char      *ID;

    // Renderer
    bool       collapsed,
               hidden;
    char     **options;
    u8         text_align;
    long int   index,
               hover_index,
               width,
               height,
               x,
               y,
               text_color,
               border_color;
    size_t     options_len;
    

    // Callbacks
    size_t     on_click_count,
               on_hover_count,
               on_change_count;
    
    void      *on_click,
              *on_hover,
              *on_change;


    // Next       
    void      *next;
};

UIDropdown_t *createDropdown     ( void );

UIDropdown_t *loadDropdown       ( const char    path[] );
UIDropdown_t *loadDropdownAsJSON ( char         *token );

int           drawDropdown       ( UIWindow_t   *window, UIDropdown_t *dropdown );

int           hoverDropdown      ( UIDropdown_t *dropdown, mouse_state_t mouse_state );
int           clickDropdown      ( UIDropdown_t *dropdown, mouse_state_t mouse_state );

int           destroyDropdown    ( UIDropdown_t *dropdown ); 