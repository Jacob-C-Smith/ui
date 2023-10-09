#pragma once
#include <stdio.h>

#include <dict/dict.h>

#include <json/json.h>

#include <UI/UItypedef.h>
#include <UI/UIElement.h>

// UI Button. 
struct UIButton_s
{

    // Button label
	  char  *label;

      // Button location
	  u32    x, 
		       y, 
		       w,
		       h;
    
    // Is the button being pressed?
    bool     depressed;

    // Callback information
    size_t   on_click_count,   on_click_max,
             on_hover_count,   on_hover_max,
             on_release_count, on_release_max;
    
    // Callback function pointers
    void   **on_click,
           **on_hover,
           **on_release;
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
DLLEXPORT int create_button ( ui_button **pp_button );

// Constructors
/** !
  *  Load a UI Button from a dict 
  *
  *  @param pp_button    : Pointer to pointer to button
  *  @param p_dictionary : Pointer to dict 
  * 
  *  @sa load_element_as_json 
  *  
  *  @return 1 on success, 0 on error.  
  */
DLLEXPORT int load_button_as_json_value ( ui_button **pp_button, json_value *p_value );

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
DLLEXPORT int hover_button ( ui_button *p_button , ui_mouse_state_t mouse_state );

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
DLLEXPORT int click_button ( ui_button *p_button , ui_mouse_state_t mouse_state );

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
DLLEXPORT int release_button ( ui_button *p_button , ui_mouse_state_t mouse_state );

// Add callbacks

/** !
  *  Add a click callback.
  *
  *  @param p_button : Pointer to button
  *  @param callback : function pointer. Should be of type int callback ( ui_button* , ui_mouse_state_t )
  *
  *  @sa add_hover_callback_button
  *  @sa add_release_callback_button
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int add_click_callback_button ( ui_button *p_button , void (*callback) ( ui_button*, ui_mouse_state_t ) );

/** !
  *  Add a hover callback.
  *
  *  @param p_button : Pointer to button
  *  @param callback : function pointer. Should be of type int callback ( ui_button* , ui_mouse_state_t )
  *
  *  @sa add_click_callback_button
  *  @sa add_release_callback_button
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int add_hover_callback_button ( ui_button *p_button , void (*callback) ( ui_button*, ui_mouse_state_t ) );

/** !
  *  Add a release callback.
  *
  *  @param p_button : Pointer to button
  *  @param callback : function pointer. Should be of type int callback ( ui_button* , ui_mouse_state_t )
  *
  *  @sa add_click_callback_button
  *  @sa add_hover_callback_button
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int add_release_callback_button ( ui_button *p_button , void (*callback) ( ui_button*, ui_mouse_state_t ) );

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
DLLEXPORT bool button_in_bounds ( ui_button *p_button, ui_mouse_state_t mouse_state );

// Deallocators
/** !
  *  Deallocates a button and its contents
  * 
  *  @param p_button    : Pointer to button
  *
  *  @return 
  */
DLLEXPORT int destroy_button ( ui_button *p_button );