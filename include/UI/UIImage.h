#pragma once
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL.h>

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
DLLEXPORT int  create_image               ( UIImage_t **pp_image );

// Constructors
DLLEXPORT int load_image_as_json_value    ( UIImage_t **pp_image, JSONValue_t      *p_value);

// Callbacks
DLLEXPORT int  hover_image                ( UIImage_t  *p_image, ui_mouse_state_t   mouse_state);
DLLEXPORT int  click_image                ( UIImage_t  *p_image, ui_mouse_state_t   mouse_state);
DLLEXPORT int  release_image              ( UIImage_t  *p_image, ui_mouse_state_t   mouse_state);

// Add callbacks
DLLEXPORT int  add_click_callback_image   ( UIImage_t  *p_image, void             (*callback)(UIImage_t*, ui_mouse_state_t));
DLLEXPORT int  add_hover_callback_image   ( UIImage_t  *p_image, void             (*callback)(UIImage_t*, ui_mouse_state_t));
DLLEXPORT int  add_release_callback_image ( UIImage_t  *p_image, void             (*callback)(UIImage_t*, ui_mouse_state_t));

// Drawers
DLLEXPORT int  draw_image                 ( UIWindow_t *p_window, UIImage_t         *p_image);

DLLEXPORT bool image_in_bounds            ( UIImage_t  *p_image, ui_mouse_state_t   mouse_state);

// Deallocators
DLLEXPORT int  destroy_image              ( UIImage_t  **pp_image );