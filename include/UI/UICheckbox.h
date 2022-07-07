#pragma once

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include <dict/dict.h>
#include <JSON/JSON.h>

#include <UI/UItypedef.h>
#include <UI/UI.h>

struct UICheckbox_s
{
    dict   *labels;
    size_t  longest_label;

    // Renderer
    u32    x,
           y,
           width,
           height;

    bool   hidden;

    // Callbacks
    size_t on_click_count,   on_click_max,
           on_hover_count,   on_hover_max,
           on_release_count, on_release_max;
    
    void     **on_click,
             **on_hover,
             **on_release;
};

// Allocators
DLLEXPORT int           create_checkbox               ( UICheckbox_t **checkbox );

// Constructors
DLLEXPORT int           load_checkbox_as_dict  ( UICheckbox_t **checkbox, dict *dictionary );
DLLEXPORT int           construct_checkbox     (UICheckbox_t **checkbox, char **labels, bool *checked, i32 x, i32 y );

// Callbacks
DLLEXPORT int           hover_checkbox                ( UICheckbox_t *checkbox  , mouse_state_t mouse_state );
DLLEXPORT int           click_checkbox                ( UICheckbox_t *checkbox  , mouse_state_t mouse_state );
DLLEXPORT int           release_checkbox               ( UICheckbox_t *checkbox  , mouse_state_t mouse_state );

// Add callbacks
DLLEXPORT int           add_click_callback_checkbox   ( UICheckbox_t  *checkbox, void          (*callback)(UICheckbox_t*, mouse_state_t));
DLLEXPORT int           add_hover_callback_checkbox   ( UICheckbox_t  *checkbox, void          (*callback)(UICheckbox_t*, mouse_state_t));
DLLEXPORT int           add_release_callback_checkbox ( UICheckbox_t  *checkbox, void          (*callback)(UICheckbox_t*, mouse_state_t));

// Drawing
DLLEXPORT int           draw_checkbox                  ( UIWindow_t   *window    , UICheckbox_t *checkbox );

DLLEXPORT bool          checkbox_in_bounds             ( UICheckbox_t  *checkbox , mouse_state_t mouse_state);


// Deallocators
DLLEXPORT int           destroy_checkbox               ( UICheckbox_t *checkbox );