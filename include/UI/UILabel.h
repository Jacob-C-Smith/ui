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
    size_t     on_click_count,
               on_hover_count,
               on_change_count;
    
    void     **on_click,
             **on_hover,
             **on_change;
};

UILabel_t *create_label              ( void );

UILabel_t *load_label                ( const char  path[] );
UILabel_t *load_label_as_json_tokens ( JSONToken_t *tokens, size_t token_count );

int        draw_label                ( UIWindow_t *window, UILabel_t  *label );

int        click_label               ( UILabel_t  *label , mouse_state_t mouse_state );

void       destroy_label             ( UILabel_t  *label );