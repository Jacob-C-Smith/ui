#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <JSON/JSON.h>

#include <UI/UItypedef.h>
#include <UI/UI.h>
#include <UI/UIWindow.h>

struct UIDropdown_s
{

    // Renderer
    bool       collapsed,
               hidden;
    char     **options;
    u8         text_align;
    i32        index,
               hover_index,
               width,
               height,
               x,
               y;
    size_t     options_len,
               longest_option;
    

    // Callbacks
    size_t     on_click_count,  on_click_max,
               on_hover_count,  on_hover_max,
               on_release_count, on_release_max;
    
    void      **on_click,
              **on_hover,
              **on_release;
};

// Allocators

 /* !
  *  Allocate a UI Dropdown
  *
  *  @param pp_dropdown : Pointer to pointer to dropdown struct
  * 
  *  @sa destroy_button
  *
  *  @return 0 on success, -1 on error.
  */
DLLEXPORT int create_dropdown               ( UIDropdown_t **pp_dropdown );

// Constructors
DLLEXPORT int load_dropdown_as_dict         ( UIDropdown_t **pp_dropdown, dict                  *dictionary );
DLLEXPORT int construct_dropdown            ( UIDropdown_t **pp_dropdown, char                 **options, i32 x, i32 y, i32 index );

// Drawing
DLLEXPORT int draw_dropdown                 ( UIWindow_t    *p_window    , UIDropdown_t         *p_dropdown );

// Callbacks
DLLEXPORT int click_dropdown                ( UIDropdown_t  *p_dropdown  , ui_mouse_state_t      mouse_state );
DLLEXPORT int hover_dropdown                ( UIDropdown_t  *p_dropdown  , ui_mouse_state_t      mouse_state );
DLLEXPORT int release_dropdown              ( UIDropdown_t  *p_dropdown  , ui_mouse_state_t      mouse_state );

// Add callbacks
DLLEXPORT int add_click_callback_dropdown   ( UIDropdown_t  *p_dropdown  , void               ( *callback ) ( UIDropdown_t *, ui_mouse_state_t ) );
DLLEXPORT int add_hover_callback_dropdown   ( UIDropdown_t  *p_dropdown  , void               ( *callback ) ( UIDropdown_t *, ui_mouse_state_t ) );
DLLEXPORT int add_release_callback_dropdown ( UIDropdown_t  *p_dropdown  , void               ( *callback ) ( UIDropdown_t *, ui_mouse_state_t ) );

DLLEXPORT bool dropdown_in_bounds           ( UIDropdown_t  *p_dropdown  , ui_mouse_state_t      mouse_state);

// Destructors
DLLEXPORT int destroy_dropdown              ( UIDropdown_t *p_dropdown );