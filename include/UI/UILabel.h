#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <JSON/JSON.h>

#include <UI/UI.h>
#include <UI/UItypedef.h>

struct UILabel_s
{
    char    *text;
    i32      x,
             y,
             width,
             height;
    bool     hidden;

    // Callbacks
    size_t     on_click_count,   on_click_max,
               on_hover_count,   on_hover_max,
               on_release_count, on_release_max;
    
    void      **on_click,
              **on_hover,
              **on_release;
};

// Allocators
DLLEXPORT int  create_label              ( UILabel_t **label );

// Constructors
DLLEXPORT int  load_label                 ( UILabel_t **label, const char  path[] );
DLLEXPORT int  load_label_as_dict         ( UILabel_t **label, dict *dictionary );
DLLEXPORT int  construct_label            ( UILabel_t **label, char *text, i32 x, i32 y );

// Draw er
DLLEXPORT int  draw_label                 ( UIWindow_t *window, UILabel_t  *label );

// Callbacks
DLLEXPORT int  click_label                ( UILabel_t  *label, mouse_state_t mouse_state );
DLLEXPORT int  hover_label                ( UILabel_t  *label, mouse_state_t mouse_state);
DLLEXPORT int  release_label              ( UILabel_t  *label, mouse_state_t mouse_state);

// Add callbacks
DLLEXPORT int  add_click_callback_label   ( UILabel_t *label, void          (*callback)(UILabel_t*, mouse_state_t));
DLLEXPORT int  add_hover_callback_label   ( UILabel_t *label, void          (*callback)(UILabel_t*, mouse_state_t));
DLLEXPORT int  add_release_callback_label ( UILabel_t *label, void          (*callback)(UILabel_t*, mouse_state_t));

// Bounds
DLLEXPORT bool label_in_bounds            ( UILabel_t *label, mouse_state_t mouse_state );

// Deallocators
DLLEXPORT void destroy_label              ( UILabel_t  *label );