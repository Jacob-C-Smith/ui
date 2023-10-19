/** !
 * Header file for UI button
 * 
 * @file ui/button.h
 * 
 * @author Jacob Smith
 */

// Header guard
#pragma once

// Standard library
#include <stdio.h>

// dict submodule
#include <dict/dict.h>

// json submodule
#include <json/json.h>

// UI
#include <ui/typedef.h>
#include <ui/element.h>

/** !
 * @brief UI button
 */
struct UIButton_s
{

    // Label
    char *label;
    
    // Is the button being pressed?
    bool depressed;

    // Location
    struct
    {
        u32 x, y, w, h;
    } location;

    // Callback
    struct 
    {
        struct 
        {
            size_t   count, max;
            void   **callbacks;
        } click;

        struct 
        {
            size_t   count, max;
            void   **callbacks;
        } hover;

        struct 
        {
            size_t   count, max;
            void   **callbacks;
        } release;
    } callback;
};

// Allocators

/** !
 *  Allocate a UI Button
 *
 *  @param pp_button : Pointer to pointer to button
 *  
 *  @sa destroy_button
 *  
 *  @return 1 on success, 0 on error.  
 */
DLLEXPORT int create_button ( ui_button **const pp_button );

// Constructors
/** !
 *  Load a UI Button from a json value
 *
 *  @param pp_button : Pointer to pointer to button
 *  @param p_value   : the json value
 * 
 *  @sa load_element_as_json 
 *  
 *  @return 1 on success, 0 on error.  
 */
DLLEXPORT int load_button_as_json_value ( ui_button **const pp_button, const json_value *const p_value );

// Callbacks

/** !
 *  Fire each hover callbacks. 
 *
 *  @param p_button    : Pointer to button
 *  @param mouse_state : Mouse state 
 * 
 *  @sa click_button
 *  @sa release_button
 *
 *  @return 1 on success, 0 on error.
 */
DLLEXPORT int hover_button ( ui_button *const p_button , ui_mouse_state mouse_state );

/** !
 *  Fire each click callbacks. 
 *
 *  @param p_button    : Pointer to button
 *  @param mouse_state : Mouse state 
 * 
 *  @sa hover_button
 *  @sa release_button
 *
 *  @return 1 on success, 0 on error.
 */
DLLEXPORT int click_button ( ui_button *const p_button , ui_mouse_state mouse_state );

/** !
 *  Fire each release callbacks. 
 *
 *  @param p_button    : Pointer to button
 *  @param mouse_state : Mouse state 
 *
 *  @sa click_button
 *  @sa hover_button
 *
 *  @return 1 on success, 0 on error.
 */
DLLEXPORT int release_button ( ui_button *const p_button , ui_mouse_state mouse_state );

// Add callbacks

/** !
 *  Add a click callback.
 *
 *  @param p_button : Pointer to button
 *  @param callback : function pointer. Should be of type int callback ( ui_button* , ui_mouse_state )
 *
 *  @sa add_hover_callback_button
 *  @sa add_release_callback_button
 *
 *  @return 1 on success, 0 on error.
 */
DLLEXPORT int add_click_callback_button ( ui_button *p_button , void (*callback) ( ui_button*, ui_mouse_state ) );

/** !
 *  Add a hover callback.
 *
 *  @param p_button : Pointer to button
 *  @param callback : function pointer. Should be of type int callback ( ui_button* , ui_mouse_state )
 *
 *  @sa add_click_callback_button
 *  @sa add_release_callback_button
 *
 *  @return 1 on success, 0 on error.
 */
DLLEXPORT int add_hover_callback_button ( ui_button *p_button , void (*callback) ( ui_button*, ui_mouse_state ) );

/** !
 *  Add a release callback.
 *
 *  @param p_button : Pointer to button
 *  @param callback : function pointer. Should be of type int callback ( ui_button* , ui_mouse_state )
 *
 *  @sa add_click_callback_button
 *  @sa add_hover_callback_button
 *
 *  @return 1 on success, 0 on error.
 */
DLLEXPORT int add_release_callback_button ( ui_button *p_button , void (*callback) ( ui_button*, ui_mouse_state ) );

// Drawing
/** !
 *  Draw a UI button.
 *
 *  @param window   : Pointer to UI window
 *  @param p_button : Pointer to button 
 *
 *  @sa draw_element
 *
 *  @return 1 on success, 0 on error.
 */
DLLEXPORT int draw_button ( ui_window *p_window, ui_button *p_button );

// Collision
/** !
 *  Checks for pointer button overlap
 * 
 *  @param p_button    : Pointer to button
 *  @param mouse_state : Mouse state
 *
 *  @return true if cursor is on the button, and false otherwise
 */
DLLEXPORT bool button_in_bounds ( ui_button *p_button, ui_mouse_state mouse_state );

// Deallocators
/** !
 *  Deallocates a button and its contents
 * 
 *  @param p_button : Pointer to button
 *
 *  @return 1 on success, 0 on error
 */
DLLEXPORT int destroy_button ( ui_button *p_button );