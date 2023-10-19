#pragma once

#include <json/json.h>

#include <ui/typedef.h>
#include <ui/ui.h>

#include <SDL.h>

struct UITextInput_s
{
    // Renderer
    char     *placeholder;
    char     *text;
    i32       width,
              height,
              x,
              y;
    size_t    max_chars;
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
DLLEXPORT int create_text_input ( ui_textinput **pp_text_input );

// Constructors
DLLEXPORT int load_text_input_as_json_value ( ui_textinput **pp_text_input, json_value *p_value );
DLLEXPORT int construct_text_input          ( ui_textinput **pp_text_input, char       *placeholder, char *text , i32 x, i32 y, size_t buffer_len );

// Callbacks
DLLEXPORT int hover_text_input   ( ui_textinput* text_input, ui_mouse_state mouse_state );
DLLEXPORT int click_text_input   ( ui_textinput* text_input, ui_mouse_state mouse_state );
DLLEXPORT int release_text_input ( ui_textinput* text_input, ui_mouse_state mouse_state );

// Add callbacks
DLLEXPORT int add_click_callback_text_input   ( ui_textinput *text_input, void (*callback)(ui_textinput*, ui_mouse_state) );
DLLEXPORT int add_hover_callback_text_input   ( ui_textinput *text_input, void (*callback)(ui_textinput*, ui_mouse_state) );
DLLEXPORT int add_release_callback_text_input ( ui_textinput *text_input, void (*callback)(ui_textinput*, ui_mouse_state) );

// Mutators
DLLEXPORT int set_text_input_text ( ui_textinput *p_text_input, char *text );

// Draw
DLLEXPORT int draw_text_input ( ui_window *window, ui_textinput *text_input );

// Bounds
DLLEXPORT bool text_input_in_bounds ( ui_textinput *text_input, ui_mouse_state mouse_state );

// Destructors
DLLEXPORT int destroy_text_input ( ui_textinput *text_input );