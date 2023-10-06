#pragma once

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include <dict/dict.h>
#include <json/json.h>

#include <UI/UItypedef.h>
#include <UI/UI.h>

struct UIRadioButton_s
{
    
    size_t    longest_label,
              label_count,
              index;
    char    **labels;

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
  *  Allocate a UI Radio Butto
  *
  *  @param pp_radio_button : Pointer to pointer to radio button
  *
  *  @sa destroy_radio_button
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int  create_radio_button               ( UIRadioButton_t **radio_button );

// Constructors
DLLEXPORT int  load_radio_button_as_json_value   ( UIRadioButton_t **pp_radio_button, json_value  *p_value );
DLLEXPORT int  construct_radio_button            ( UIRadioButton_t **radio_button   , char       **labels , size_t index, i32 x, i32 y );

// Callbacks
DLLEXPORT int  hover_radio_button                ( UIRadioButton_t *radio_button  , ui_mouse_state_t mouse_state );
DLLEXPORT int  click_radio_button                ( UIRadioButton_t *radio_button  , ui_mouse_state_t mouse_state );
DLLEXPORT int  release_radio_button              ( UIRadioButton_t *radio_button  , ui_mouse_state_t mouse_state );

// Add callbacks
DLLEXPORT int  add_click_callback_radio_button   ( UIRadioButton_t *radio_button, void (*callback)(UIRadioButton_t*, ui_mouse_state_t) );
DLLEXPORT int  add_hover_callback_radio_button   ( UIRadioButton_t *radio_button, void (*callback)(UIRadioButton_t*, ui_mouse_state_t) );
DLLEXPORT int  add_release_callback_radio_button ( UIRadioButton_t *radio_button, void (*callback)(UIRadioButton_t*, ui_mouse_state_t) );

// Drawing
DLLEXPORT int  draw_radio_button                 ( UIWindow_t *window, UIRadioButton_t *radio_button );

// Bounds
DLLEXPORT bool radio_button_in_bounds            ( UIRadioButton_t *radio_button, ui_mouse_state_t mouse_state );

// Deallocators
DLLEXPORT int  destroy_radio_button              ( UIRadioButton_t *radio_button );