#pragma once

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include <dict/dict.h>
#include <json/json.h>

#include <UI/typedef.h>
#include <UI/ui.h>

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
DLLEXPORT int  create_radio_button               ( ui_radiobutton **radio_button );

// Constructors
DLLEXPORT int  load_radio_button_as_json_value   ( ui_radiobutton **pp_radio_button, json_value  *p_value );
DLLEXPORT int  construct_radio_button            ( ui_radiobutton **radio_button   , char       **labels , size_t index, i32 x, i32 y );

// Callbacks
DLLEXPORT int  hover_radio_button                ( ui_radiobutton *radio_button  , ui_mouse_state mouse_state );
DLLEXPORT int  click_radio_button                ( ui_radiobutton *radio_button  , ui_mouse_state mouse_state );
DLLEXPORT int  release_radio_button              ( ui_radiobutton *radio_button  , ui_mouse_state mouse_state );

// Add callbacks
DLLEXPORT int  add_click_callback_radio_button   ( ui_radiobutton *radio_button, void (*callback)(ui_radiobutton*, ui_mouse_state) );
DLLEXPORT int  add_hover_callback_radio_button   ( ui_radiobutton *radio_button, void (*callback)(ui_radiobutton*, ui_mouse_state) );
DLLEXPORT int  add_release_callback_radio_button ( ui_radiobutton *radio_button, void (*callback)(ui_radiobutton*, ui_mouse_state) );

// Drawing
DLLEXPORT int  draw_radio_button                 ( ui_window *window, ui_radiobutton *radio_button );

// Bounds
DLLEXPORT bool radio_button_in_bounds            ( ui_radiobutton *radio_button, ui_mouse_state mouse_state );

// Deallocators
DLLEXPORT int  destroy_radio_button              ( ui_radiobutton *radio_button );