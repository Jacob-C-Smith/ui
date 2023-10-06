#pragma once

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include <dict/dict.h>
#include <json/json.h>

#include <UI/UItypedef.h>
#include <UI/UI.h>

struct UICheckbox_s
{
    
    size_t    longest_label,
              label_count;
    char    **labels;
    bool     *checks;

    // Renderer
    u32       x,
              y,
              width,
              height,
              hover_index;

    bool      hidden;

    // Callbacks
    size_t on_click_count,   on_click_max,
           on_hover_count,   on_hover_max,
           on_release_count, on_release_max;
    
    void     **on_click,
             **on_hover,
             **on_release;
};

// Allocators
 /** !
  *  Allocate a UI Checkbox
  *
  *  @param pp_checkbox : Pointer to pointer to checkbox
  *
  *  @sa destroy_checkbox
  *
  *  @return 0 on success, -1 on error.
  */
DLLEXPORT int           create_checkbox                ( UICheckbox_t **pp_checkbox );

// Constructors
DLLEXPORT int           load_checkbox_as_json_value    ( UICheckbox_t **pp_checkbox, json_value *p_value );
DLLEXPORT int           construct_checkbox             ( UICheckbox_t **pp_checkbox, char **pp_labels, bool *checked, i32 x, i32 y );

// Callbacks
DLLEXPORT int           hover_checkbox                 ( UICheckbox_t *p_checkbox  , ui_mouse_state_t mouse_state );
DLLEXPORT int           click_checkbox                 ( UICheckbox_t *p_checkbox  , ui_mouse_state_t mouse_state );
DLLEXPORT int           release_checkbox               ( UICheckbox_t *p_checkbox  , ui_mouse_state_t mouse_state );

// Add callbacks
DLLEXPORT int           add_click_callback_checkbox    ( UICheckbox_t  *p_checkbox, void          (*callback)(UICheckbox_t*, ui_mouse_state_t));
DLLEXPORT int           add_hover_callback_checkbox    ( UICheckbox_t  *p_checkbox, void          (*callback)(UICheckbox_t*, ui_mouse_state_t));
DLLEXPORT int           add_release_callback_checkbox  ( UICheckbox_t  *p_checkbox, void          (*callback)(UICheckbox_t*, ui_mouse_state_t));

// Drawing
DLLEXPORT int           draw_checkbox                  ( UIWindow_t   *p_window    , UICheckbox_t *p_checkbox );

DLLEXPORT bool          checkbox_in_bounds             ( UICheckbox_t *p_checkbox , ui_mouse_state_t mouse_state );


// Deallocators
DLLEXPORT int           destroy_checkbox               ( UICheckbox_t *p_checkbox );