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
    char      *name;

    // Renderer
    bool       collapsed,
               hidden;
    char     **options;
    u8         text_align;
    i32        index,
               hover_index,
               width,
               height,
               x,
               y;
    size_t     options_len;
    

    // Callbacks
    size_t     on_click_count,
               on_hover_count,
               on_change_count;
    
    void     **on_click,
             **on_hover,
             **on_change;
};

UIDropdown_t *create_dropdown              ( void );

UIDropdown_t *load_dropdown_as_json_tokens ( JSONToken_t* tokens     , size_t        token_count );

int           draw_dropdown                ( UIWindow_t   *window    , UIDropdown_t *dropdown );

int           hover_dropdown               ( UIDropdown_t *dropdown  , mouse_state_t mouse_state );
int           click_dropdown               ( UIDropdown_t *dropdown  , mouse_state_t mouse_state );

int           destroy_dropdown             ( UIDropdown_t *dropdown ); 