#pragma once

#include <JSON/JSON.h>

#include <UI/UItypedef.h>
#include <UI/UI.h>

#include <SDL2/SDL.h>

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
UITextInput_t *create_text_input              ( void );

// Constructors
UITextInput_t *load_text_input_as_json_tokens ( JSONToken_t   *tokens     , size_t         token_count );
UITextInput_t *construct_text_input           ( char          *placeholder, char          *text       , i32 x, i32 y, size_t buffer_len);

// Draw
int            draw_text_input                ( UIWindow_t    *window     , UITextInput_t *text_input );

// Callbacks
int            click_text_input               ( UITextInput_t *text_input, mouse_state_t  mouse_state );

// Destructors
void           destroy_text_input             ( UITextInput_t *text_input );