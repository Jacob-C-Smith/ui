#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <json/json.h>

#include <UI/ui.h>
#include <UI/typedef.h>

struct UILabel_s
{
    char    *text;
    i32      x,
             y,
             width,
             height,
             size;
    bool     hidden;
    color    c;
    
    // Callbacks
    size_t   on_click_count,   on_click_max,
             on_hover_count,   on_hover_max,
             on_release_count, on_release_max;
    
    void   **on_click,
           **on_hover,
           **on_release;
    
};

// Allocators
DLLEXPORT int  create_label              ( ui_label   **pp_label );

// Constructors
DLLEXPORT int  load_label_as_json_value   ( ui_label  **pp_label, json_value     *p_value );

// Drawer
DLLEXPORT int  draw_label                 ( ui_window  *p_window, ui_label       *p_label );

// Callbacks
DLLEXPORT int  click_label                ( ui_label   *p_label, ui_mouse_state_t  mouse_state );
DLLEXPORT int  hover_label                ( ui_label   *p_label, ui_mouse_state_t  mouse_state );
DLLEXPORT int  release_label              ( ui_label   *p_label, ui_mouse_state_t  mouse_state );

// Add callbacks
DLLEXPORT int  add_click_callback_label   ( ui_label   *p_label, void           ( *callback ) ( ui_label*, ui_mouse_state_t) );
DLLEXPORT int  add_hover_callback_label   ( ui_label   *p_label, void           ( *callback ) ( ui_label*, ui_mouse_state_t) );
DLLEXPORT int  add_release_callback_label ( ui_label   *p_label, void           ( *callback ) ( ui_label*, ui_mouse_state_t) );

// Bounds
DLLEXPORT bool label_in_bounds            ( ui_label   *p_label, ui_mouse_state_t  mouse_state );

// Printers
DLLEXPORT int  print_label_to_file        ( ui_label   *p_label, FILE *f, char *name );

// Deallocators
DLLEXPORT int destroy_label              ( ui_label   **pp_label );