#pragma once

#include <JSON/JSON.h>

#include <UI/UItypedef.h>

struct UIRadioButton_s
{
    // ID
    char* ID;
    char* groupID;

    // Renderer
    long int x;
    long int y;
    bool     hidden;
    bool     checked;

    // Callbacks
    void* onChange;
    // Next
    void* next;
};
struct UIRadioButton_s;
typedef struct UIRadioButton_s UIRadioButton_t;
