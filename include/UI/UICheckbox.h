#pragma once

#include <JSON/JSON.h>

#include <UI/UItypedef.h>

struct UICheckbox_s
{
    // ID
    char* ID;
    char* group_id;

    // Renderer
    long int x;
    long int y;
    bool     hidden;
    bool     checked;

    // Callbacks
    void* on_change;
    // Next
    void* next;
};
