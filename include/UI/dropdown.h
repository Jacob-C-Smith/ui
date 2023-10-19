#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <json/json.h>

#include <UI/typedef.h>
#include <UI/ui.h>
#include <UI/window.h>

struct UIDropdown_s
{

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
    size_t     options_count,
               longest_option;
    

    // Callbacks
    size_t     on_click_count,  on_click_max,
               on_hover_count,  on_hover_max,
               on_release_count, on_release_max;
    
    void      **on_click,
              **on_hover,
              **on_release;
};

// Allocators

 /** !
  *  Allocate a UI Dropdown
  *
  *  @param pp_dropdown : Pointer to pointer to dropdown struct
  * 
  *  @sa destroy_button
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int create_dropdown ( ui_dropdown **pp_dropdown );

// Constructors
DLLEXPORT int load_dropdown_as_json_value ( ui_dropdown **pp_dropdown, json_value  *p_value );
DLLEXPORT int construct_dropdown          ( ui_dropdown **pp_dropdown, char       **options, i32 x, i32 y, i32 index );

// Drawing
DLLEXPORT int draw_dropdown ( ui_window *p_window, ui_dropdown *p_dropdown );

// Callbacks
DLLEXPORT int click_dropdown   ( ui_dropdown *p_dropdown, ui_mouse_state_t mouse_state );
DLLEXPORT int hover_dropdown   ( ui_dropdown *p_dropdown, ui_mouse_state_t mouse_state );
DLLEXPORT int release_dropdown ( ui_dropdown *p_dropdown, ui_mouse_state_t mouse_state );

// Add callbacks
DLLEXPORT int add_click_callback_dropdown   ( ui_dropdown *p_dropdown, void ( *callback ) ( ui_dropdown *, ui_mouse_state_t ) );
DLLEXPORT int add_hover_callback_dropdown   ( ui_dropdown *p_dropdown, void ( *callback ) ( ui_dropdown *, ui_mouse_state_t ) );
DLLEXPORT int add_release_callback_dropdown ( ui_dropdown *p_dropdown, void ( *callback ) ( ui_dropdown *, ui_mouse_state_t ) );

// Bounds
DLLEXPORT bool dropdown_in_bounds ( ui_dropdown *p_dropdown, ui_mouse_state_t mouse_state );

// Destructors
DLLEXPORT int destroy_dropdown ( ui_dropdown *p_dropdown );