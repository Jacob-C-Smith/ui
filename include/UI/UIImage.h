#pragma once
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL.h>
#include <SDL_image.h>

#include <json/json.h>

#include <UI/UI.h>
#include <UI/UItypedef.h>

struct UIImage_s
{
    int          x,
                 y,
                 width,
                 height;
    SDL_Texture *texture;
    
    // Callbacks
    size_t     on_click_count,
               on_hover_count,
               on_change_count;
    
    void     **on_click,
             **on_hover,
             **on_change;
};

// Allocators
DLLEXPORT int create_image ( ui_image **pp_image );

// Constructors
DLLEXPORT int load_image_as_json_value ( ui_image **pp_image, json_value *p_value );

// Callbacks
DLLEXPORT int hover_image   ( ui_image *p_image, ui_mouse_state_t mouse_state );
DLLEXPORT int click_image   ( ui_image *p_image, ui_mouse_state_t mouse_state );
DLLEXPORT int release_image ( ui_image *p_image, ui_mouse_state_t mouse_state );

// Add callbacks
DLLEXPORT int add_click_callback_image   ( ui_image *p_image, void (*callback)(ui_image*, ui_mouse_state_t) );
DLLEXPORT int add_hover_callback_image   ( ui_image *p_image, void (*callback)(ui_image*, ui_mouse_state_t) );
DLLEXPORT int add_release_callback_image ( ui_image *p_image, void (*callback)(ui_image*, ui_mouse_state_t) );

// Drawers
DLLEXPORT int draw_image ( ui_window *p_window, ui_image *p_image );

// Bounds
DLLEXPORT bool image_in_bounds ( ui_image *p_image, ui_mouse_state_t mouse_state );

// Deallocators
DLLEXPORT int destroy_image ( ui_image **pp_image );