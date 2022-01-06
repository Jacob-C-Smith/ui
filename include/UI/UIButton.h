#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <JSON/JSON.h>

#include <UI/UItypedef.h>
#include <UI/UIWindow.h>
#include <UI/UI.h>

struct UIButton_s
{
    // ID
    char   *ID;

    // Renderer
    char   *text;
    i32     width,
            height,
            x,
            y;
    int     text_color,
            back_color,
            border_color;
    u8      text_align;
    i32     border_width;
    bool    hidden,
            depressed;

    // Callbacks
    void   **on_click,
           **on_hover;
    size_t   on_click_count,
             on_hover_count;

    

    // Next
    void* next;
};


// Allocators
UIButton_t *createButton     ( );

// Constructors
UIButton_t *loadButton       ( const char *path );
UIButton_t *loadButtonAsJSON ( char       *tokens );

// Callbacks
int         hoverButton      ( UIButton_t *button, mouse_state_t mouse_state );
int         clickButton      ( UIButton_t *button, mouse_state_t mouse_state );
int         releaseButton    ( UIButton_t *button, mouse_state_t mouse_state );

// Drawing
int         drawButton       ( UIWindow_t *window, UIButton_t *button );

// 
int         destroyButton    ( UIButton_t *button );