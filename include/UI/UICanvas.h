#pragma once

#include <JSON/JSON.h>

#include <UI/UItypedef.h>

struct UICanvas_s
{
    // TODO
    
    // Callbacks
    size_t     on_click_count , on_click_max,
               on_hover_count , on_hover_max,
               on_change_count, on_change_max;
    
    void     **on_click,
             **on_hover,
             **on_change;
};
