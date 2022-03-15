#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include <JSON/JSON.h>

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
UIImage_t *create_image              ( void );

// Constructors
UIImage_t *load_image                ( const char   path[] );
UIImage_t *load_image_as_json_tokens ( JSONToken_t* tokens, size_t token_count);

// Drawers
int        draw_image                ( UIImage_t   *image );

// Deallocators
int        destroy_image             ( UIImage_t   *image );