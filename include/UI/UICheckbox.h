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
    
    char  *name,
         **labels;

    size_t label_count,
           longest_label;

    // Renderer
    u32    x,
           y,
           width,
           height;

    bool   hidden;

    // Value
    bool  *checked;

    // Callbacks
    size_t on_click_count, on_click_max,
           on_hover_count, on_hover_max,
           on_change_count, on_change_max;
    
    void     **on_click,
             **on_hover,
             **on_change;
};

// Allocators
UICheckbox_t *create_checkbox              ( void );

// Constructors
UICheckbox_t *load_checkbox_as_json_tokens ( JSONToken_t  *tokens    , size_t       token_count );

// Callbacks
int           hover_checkbox               ( UICheckbox_t *checkbox  , mouse_state_t mouse_state );
int           click_checkbox               ( UICheckbox_t *checkbox  , mouse_state_t mouse_state );
int           change_checkbox              ( UICheckbox_t *checkbox  , mouse_state_t mouse_state );

// Drawing
int           draw_checkbox                ( UIWindow_t   *window    , UICheckbox_t *checkbox );

// Deallocators
int           destroy_checkbox             ( UICheckbox_t *checkbox );