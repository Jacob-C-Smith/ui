#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <json/json.h>

#include <UI/UI.h>
#include <UI/UItypedef.h>

struct UILabel_s
{
    char    *text;
    i32      x,
             y,
             width,
             height,
             size;
    bool     hidden;
    
    // Callbacks
    size_t   on_click_count,   on_click_max,
             on_hover_count,   on_hover_max,
             on_release_count, on_release_max;
    
    void   **on_click,
           **on_hover,
           **on_release;
    
};

// Allocators
DLLEXPORT int  create_label              ( UILabel_t   **pp_label );

// Constructors
DLLEXPORT int  load_label_as_json_value   ( UILabel_t  **pp_label, JSONValue_t     *p_value );

// Drawer
DLLEXPORT int  draw_label                 ( UIWindow_t  *p_window, UILabel_t       *p_label );

// Callbacks
DLLEXPORT int  click_label                ( UILabel_t   *p_label, ui_mouse_state_t  mouse_state );
DLLEXPORT int  hover_label                ( UILabel_t   *p_label, ui_mouse_state_t  mouse_state );
DLLEXPORT int  release_label              ( UILabel_t   *p_label, ui_mouse_state_t  mouse_state );

// Add callbacks
DLLEXPORT int  add_click_callback_label   ( UILabel_t   *p_label, void           ( *callback ) ( UILabel_t*, ui_mouse_state_t) );
DLLEXPORT int  add_hover_callback_label   ( UILabel_t   *p_label, void           ( *callback ) ( UILabel_t*, ui_mouse_state_t) );
DLLEXPORT int  add_release_callback_label ( UILabel_t   *p_label, void           ( *callback ) ( UILabel_t*, ui_mouse_state_t) );

// Bounds
DLLEXPORT bool label_in_bounds            ( UILabel_t   *p_label, ui_mouse_state_t  mouse_state );

// Printers
DLLEXPORT int  print_label_to_file        ( UILabel_t   *p_label, FILE *f, char *name );

// Deallocators
DLLEXPORT int destroy_label              ( UILabel_t   **pp_label );