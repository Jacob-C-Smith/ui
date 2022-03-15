#pragma once

#include <JSON/JSON.h>

#include <UI/UItypedef.h>
#include <UI/UI.h>

struct UITextInput_s
{
    // Renderer
    char     *placeholder;
    char     *text;
    long int  width;
    long int  height;
    long int  x;
    long int  y;
    bool      hidden;

    // Callbacks
    size_t on_click_count , on_click_max,
           on_hover_count , on_hover_max,
           on_change_count, on_change_max;
    
    void **on_click,
         **on_hover,
         **on_change;
};


UITextInput_t* create_text_input              ( void );

UITextInput_t* load_text_input                ( const char     path[] );
UITextInput_t* load_text_input_as_json_tokens ( JSONToken_t   *tokens    , size_t         token_count );

int            draw_text_input                ( UIWindow_t    *window    , UITextInput_t *text_input );

int            click_text_input               ( UITextInput_t *text_input, mouse_state_t  mouse_state );

void           destroy_text_input             ( UITextInput_t *text_input );