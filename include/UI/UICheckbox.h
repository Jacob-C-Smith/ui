#pragma once

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include <JSON/JSON.h>

#include <UI/UItypedef.h>
#include <UI/UI.h>

struct UICheckbox_s
{
    // ID
    char* label,
          group;

    // Renderer
    u32   x,
          y,
          width,
          height;
    bool  hidden;

    // Value
    bool  checked;



    // Callbacks
    void** on_click;
    size_t on_click_count;
};

// Allocators
UICheckbox_t *create_checkbox              ( void );

// Constructors
UICheckbox_t *load_checkbox_as_json_tokens ( JSONToken_t  *tokens    , size_t       token_count );

// Callbacks
int           hover_checkbox               ( UICheckbox_t *checkbox  , mouse_state_t mouse_state );
int           click_checkbox               ( UICheckbox_t *checkbox  , mouse_state_t mouse_state );
int           release_checkbox             ( UICheckbox_t *checkbox  , mouse_state_t mouse_state );

// Drawing
int           draw_checkbox                ( UIWindow_t   *window    , UICheckbox_t *checkbox );

// Deallocators
int           destroy_checkbox             ( UICheckbox_t *checkbox );