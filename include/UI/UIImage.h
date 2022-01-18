#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include <JSON/JSON.h>

#include <UI/UItypedef.h>

struct UIImage_s
{
    int          x,
                 y,
                 width,
                 height;
    SDL_Texture *texture;
};

// Allocators
UIImage_t *create_image       ( );

// Constructors
UIImage_t *load_image         ( const char   path[] );
UIImage_t *load_image_as_json ( char        *token  );

// Drawers
int        draw_image         ( UIImage_t   *image );

// Deallocators
int        destroy_image      ( UIImage_t   *image );