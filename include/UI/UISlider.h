 #pragma once

#include <JSON/JSON.h>

#include <UI/UItypedef.h>
#include <UI/UI.h>

struct UISlider_s
{
    // TODO
    i32   x,
          y,
          width,
          height;

    float min,
          max,
          step,
          real_step,
          value;

    bool  grab;

    // Callbacks
    size_t on_click_count,
           on_hover_count,
           on_change_count;
    
    void **on_click,
         **on_hover,
         **on_change;
};


UISlider_t *create_slider              ( void );

UISlider_t *load_slider                ( const char   path[] );
UISlider_t *load_slider_as_json_tokens ( JSONToken_t *tokens, size_t        token_count );

int         draw_slider                ( UIWindow_t *window , UISlider_t   *slider );

int         hover_slider               ( UISlider_t *slider , mouse_state_t mouse_state );
int         click_slider               ( UISlider_t *slider , mouse_state_t mouse_state );
int         release_slider             ( UISlider_t *slider , mouse_state_t mouse_state );

void        destroy_slider             ( UISlider_t *slider );