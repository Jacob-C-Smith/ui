#pragma once

#include <JSON/JSON.h>

#include <UI/UItypedef.h>

struct UITextInput_s
{
    // ID
    char* ID;

    // Renderer
    char* placeholder;
    char* text;
    long int width;
    long int height;
    long int x;
    long int y;
    bool     hidden;

    // Callbacks
    void* onChange;
    void* onInput;

    // Next
    void* next;
};
