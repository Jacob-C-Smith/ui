/** !
 * Main header for UI library

 * @file UI/UI.h
 * 
 * @author Jacob Smith,
 */

// Includes
#pragma once

// Standard Library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// SDL
#include <SDL.h>
#undef main

// JSON parser
#include <json/json.h>
#include <dict/dict.h>

// UI 
#include <UI/UItypedef.h>
#include <UI/UIWindow.h>

// Preprocessor constants
#define UI_M1     0x01
#define UI_M2     0x02
#define UI_M3     0x04
#define UI_M4     0x08
#define UI_M5     0x10
#define UI_SWUP   0x20
#define UI_SWDOWN 0x40

#define MAX_WINDOW_COUNT 16

// Mouse event callback parameter
struct ui_mouse_state_s {

    // The position of the cursor
    s32 x,
        y;
    
    // Bitmask mouse keys and scroll wheel
    u8  button;
};

// UI Instance. Contains a list of windows and an active theme.
struct UIInstance_s {
    dict        *windows;
    bool         running;
    UIWindow_t  *active_window,
                *load_window,
               **windows_list;
    color        primary,
                 background, 
                 accent_1,
                 accent_2,
                 accent_3;
};

// Initializers
/** !
 *  Initialize UI. If path is null, a config file will be loaded from the user's home directory. 
 *  If no config file exists, a default config file will be generated.
 *
 *  @param pp_instance : Pointer to pointer to UI instance
 *  @param path        : Path to config file or null
 *
 *  @sa ui_exit
 *
 *  @return 1 on success, 0 on error.
 */
DLLEXPORT int ui_init ( UIInstance_t **pp_instance, const char *path );

// ANSI colored prints
/** !
 *  printf in ANSI blue
 *
 *  @param format : printf format text
 *  @param ...    : varadic arguments
 *
 *  @sa ui_print_warning
 *  @sa ui_print_error
 *
 *  @return 1 on success, 0 on error.
 */
DLLEXPORT int ui_print_log ( const char* const format, ... );

/** !
  *  printf in ANSI yellow
  *
  *  @param format : printf format text
  *  @param ...    : varadic arguments
  * 
  *  @sa ui_print_log
  *  @sa ui_print_error
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int ui_print_warning ( const char* const format, ... );

/** !
  *  printf in ANSI red
  *
  *  @param format : printf format text
  *  @param ...    : varadic arguments
  * 
  *  @sa ui_print_log
  *  @sa ui_print_warning
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int ui_print_error ( const char* const format, ... );

// Text drawing
/** !
  *  Graphical printf
  *
  *  @param format : printf format text
  *  @param window : The window to print to
  *  @param x      : The x offset in pixels
  *  @param y      : The y offset in pixels
  *  @param size   : 1 is 8px height, 2 is 16px, 3 is 24px, etc
  *  @param ...    : varadic arguments
  *
  *  @sa ui_draw_text
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int ui_draw_format_text ( const char* const format, UIWindow_t *p_window, int x, int y, int size, ... );

// Text drawing
/** !
  *  Graphical puts
  *
  *  @param format : printf format text
  *  @param window : The window to print to
  *  @param x      : The x offset in pixels
  *  @param y      : The y offset in pixels
  *  @param size   : 1 is 8px height, 2 is 16px, 3 is 24px, etc
  *
  *  @sa ui_draw_format_text
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int ui_draw_text ( const char* const text, UIWindow_t *p_window, int x, int y, int size );

/** !
  *  Draw a circle
  *
  *  @param radius : printf format text
  *  @param window : The window to draw to
  *  @param x      : The x offset in pixels
  *  @param y      : The y offset in pixels
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int ui_draw_circle ( int radius, UIWindow_t *p_window, int x, int y );

// Window operations
/** !
  *  Append a window to an instance
  *
  *  @param instance : Pointer to instance
  *  @param window   : The window to append
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int ui_append_window ( UIInstance_t *p_instance, UIWindow_t *p_window );

/** !
  *  Remove a window
  *
  *  @param instance : Pointer to instance
  *  @param name     : The name of the window
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT UIWindow_t *ui_remove_window ( UIInstance_t *p_instance, const char *name );

/** !
  *  Process active window input
  *
  *  @param instance : Pointer to instance
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int ui_process_input ( UIInstance_t *p_instance );

/** !
  *  Draw the active window
  *
  *  @param instance : Pointer to instance
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int ui_draw ( UIInstance_t *p_instance );

// Image drawing
/** !
  *  Get the active instance
  *
  *  @return active instance for this process ID
  */
DLLEXPORT UIInstance_t *ui_get_active_instance ( void );

// File I/O
/** !
  *  Load a file
  *
  *  @param path   : File path
  *  @param buffer : Pointer to buffer 
  *  @param binary : fopen mode is "rb" if true else "r"
  * 
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT size_t ui_load_file ( const char *path, void *buffer, bool binary );

// Exit
/** !
  *  Shutdown the UI
  *
  *  @param instance : Pointer to instance
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int ui_exit ( UIInstance_t **pp_instance );