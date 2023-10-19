#include <json/json.h>

#include <ui/typedef.h>

struct UIChart_s
{
    // TODO
    
    // Callbacks
    size_t     on_click_count,
               on_hover_count,
               on_change_count;
    
    void     **on_click,
             **on_hover,
             **on_change;
};
