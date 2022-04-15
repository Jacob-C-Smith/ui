#pragma once

#include <stdio.h>
#include <string.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include <JSON/JSON.h>

#include <UI/UItypedef.h>
#include <UI/UIWindow.h>

#define UI_BUTTON      0x001
#define UI_CANVAS      0x002
#define UI_CHART       0x004
#define UI_CHECKBOX    0x008
#define UI_DROPDOWN    0x010
#define UI_IMAGE       0x020
#define UI_LABEL       0x040
#define UI_RADIOBUTTON 0x080
#define UI_SLIDER      0x100
#define UI_TEXTINPUT   0x200

#undef main

#define UI_M1     0x01
#define UI_M2     0x02
#define UI_M3     0x04
#define UI_M4     0x08
#define UI_M5     0x10
#define UI_SWUP   0x20
#define UI_SWDOWN 0x40

struct mouse_state_s {
    u32 x,
        y;
    u8  button;
};


struct UIInstance_s {
    UIWindow_t   *windows;
    color         primary,
                  background, 
                  accent_1,
                  accent_2,
                  accent_3;
};

// Initializers
UIInstance_t *ui_init             ( const char       *path );

// ANSI colored prints
int           ui_print_log        ( const char* const format  , ... );
int           ui_print_warning    ( const char* const format  , ... );
int           ui_print_error      ( const char* const format  , ... );

// Text drawing
int           ui_draw_format_text ( const char* const format  , UIWindow_t *window, int x, int y, int size, ... );
int           ui_draw_text        ( const char* const text    , UIWindow_t *window, int x, int y, int size );
int           ui_draw_circle      ( int               radius  , UIWindow_t *window, int x, int y );

// Window operations
int           ui_append_window    ( UIInstance_t     *instance, UIWindow_t *window );
UIWindow_t   *ui_remove_window    ( UIInstance_t     *instance, const char *name );
int           ui_process_input    ( UIInstance_t     *instance );
int           ui_draw             ( UIInstance_t     *instance );

// Image drawing
UIInstance_t *ui_get_active_instance ( void );

// File I/O
size_t        ui_load_file        ( const char       *path    , void       *buffer, bool binary );

// Exit
int           ui_exit             ( UIInstance_t     *instance );