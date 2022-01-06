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
    // ID
    char* ID;

    // Renderer
    char* text;
    long int x;
    long int y;
    u32      textColor;
    u8       textAlign;
    bool     hidden;

    // Callbacks
    void* onClick;

    // Next
    void* next;
};
struct UILabel_s;
typedef struct UILabel_s UILabel_t;

UILabel_t *createLabel     ( );

UILabel_t *loadLabel       ( const char  path[] );
UILabel_t *loadLabelAsJSON ( char       *token );

int        drawLabel       ( UIWindow_t *window, UILabel_t  *label );

void       destroyLabel    ( UILabel_t  *label );