#pragma once

#include <JSON/JSON.h>

#include <UI/UItypedef.h>
#include <UI/UI.h>

#include <SDL.h>

struct UITextInput_s
{
    // Renderer
    char     *placeholder;
    char     *text;
    i32       width,
              height,
              x,
              y,
              max_chars;
    bool      hidden;

    // Callbacks
    size_t on_click_count , on_click_max,
           on_hover_count , on_hover_max,
           on_change_count, on_change_max;
    
    void **on_click,
         **on_hover,
         **on_change;
};

// Allocators
DLLEXPORT int  create_text_input       ( UITextInput_t **pp_text_input );

// Constructors
DLLEXPORT int  load_text_input_as_dict ( UITextInput_t **pp_text_input, dict *dictionary );
DLLEXPORT int  construct_text_input    ( UITextInput_t **pp_text_input, char *placeholder, char *text , i32 x, i32 y, size_t buffer_len );

// Callbacks
DLLEXPORT int  hover_text_input(UITextInput_t* text_input, ui_mouse_state_t mouse_state);
DLLEXPORT int  click_text_input(UITextInput_t* text_input, ui_mouse_state_t mouse_state);
DLLEXPORT int  release_text_input(UITextInput_t* text_input, ui_mouse_state_t mouse_state);

// Add callbacks
DLLEXPORT int  add_click_callback_text_input(UITextInput_t* text_input, void          (*callback)(UITextInput_t*, ui_mouse_state_t));
DLLEXPORT int  add_hover_callback_text_input(UITextInput_t* text_input, void          (*callback)(UITextInput_t*, ui_mouse_state_t));
DLLEXPORT int  add_release_callback_text_input(UITextInput_t* text_input, void          (*callback)(UITextInput_t*, ui_mouse_state_t));

// Draw
DLLEXPORT int  draw_text_input         ( UIWindow_t    *window     , UITextInput_t *text_input );

DLLEXPORT bool text_input_in_bounds (UITextInput_t* checkbox, ui_mouse_state_t mouse_state);

// Destructors
DLLEXPORT int  destroy_text_input      ( UITextInput_t *text_input );