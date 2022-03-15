#pragma once

#include <JSON/JSON.h>

#include <UI/UI.h>
#include <UI/UItypedef.h>

struct UIRadioButton_s
{
    char  *name,
         **labels;

    size_t label_count,
           longest_label,
           checked_index;

    // Renderer
    i32    x,
           y,
           width,
           height;
    bool   hidden;

    // Callbacks
    size_t on_click_count, on_click_max,
           on_hover_count, on_hover_max,
           on_change_count, on_change_max;
    
    void **on_click,
         **on_hover,
         **on_change;
};
struct UIRadioButton_s;
typedef struct UIRadioButton_s UIRadioButton_t;


// Allocators
UIRadioButton_t *create_radio_button              ( void );

// Constructors
UIRadioButton_t *load_radio_button_as_json_tokens ( JSONToken_t  *tokens    , size_t       token_count );

// Callbacks
int              hover_radio_button               ( UIRadioButton_t *radio_button  , mouse_state_t mouse_state );
int              click_radio_button               ( UIRadioButton_t *radio_button  , mouse_state_t mouse_state );
int              change_radio_button              ( UIRadioButton_t *radio_button  , mouse_state_t mouse_state );

// Drawing
int              draw_radio_button                ( UIWindow_t   *window    , UIRadioButton_t *radio_button );

// Deallocators
int              destroy_radio_button             ( UIRadioButton_t *checkbox );