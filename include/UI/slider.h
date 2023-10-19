#pragma once
#include <stdio.h>
#include <stdbool.h>

#include <dict/dict.h>

#include <json/json.h>

#include <UI/typedef.h>
#include <UI/element.h>

// UI Slider. 
struct UISlider_s
{
    // Slider location
	u32    x, 
		     y, 
		     w,
		     h,
         pre,
         post;
    bool sliding;
    float    min,
             max,
             value;

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
  *  Allocate a UI Slider
  *
  *  @param pp_slider : Pointer to pointer to slider
  *  
  *  @sa destroy_slider
  *  
  *  @return 1 on success, 0 on error.  
  */
DLLEXPORT int create_slider ( ui_slider **pp_slider );

// Constructors
 /** !
  *  Load a UI Slider from a dict 
  *
  *  @param pp_slider : Pointer to pointer to slider
  *  @param p_value   : Pointer to a json_value
  * 
  *  @sa load_element_as_json_value 
  *  
  *  @return 1 on success, 0 on error.  
  */
DLLEXPORT int load_slider_as_json_value ( ui_slider **pp_slider, json_value *p_value );

// Callbacks

/** !
  *  Fire each hover callback. 
  *
  *  @param p_slider    : Pointer to slider
  *  @param mouse_state : Mouse state 
  * 
  *  @sa click_slider
  *  @sa release_slider
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int hover_slider ( ui_slider *p_slider, ui_mouse_state mouse_state );

/** !
  *  Fire each click callback. 
  *
  *  @param p_slider    : Pointer to slider
  *  @param mouse_state : Mouse state 
  * 
  *  @sa hover_slider
  *  @sa release_slider
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int click_slider ( ui_slider *p_slider, ui_mouse_state mouse_state );

/** !
  *  Fire each release callback. 
  *
  *  @param p_slider    : Pointer to slider
  *  @param mouse_state : Mouse state 
  *
  *  @sa click_slider
  *  @sa hover_slider
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int release_slider ( ui_slider *p_slider, ui_mouse_state mouse_state );

// Add callbacks

/** !
  *  Add a click callback.
  *
  *  @param p_slider : Pointer to slider
  *  @param callback : function pointer. Should be of type int callback ( ui_slider* , ui_mouse_state )
  *
  *  @sa add_hover_callback_slider
  *  @sa add_release_callback_slider
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int add_click_callback_slider ( ui_slider *p_slider, void (*callback) ( ui_slider*, ui_mouse_state ) );

/** !
  *  Add a hover callback.
  *
  *  @param p_slider : Pointer to slider
  *  @param callback : function pointer. Should be of type int callback ( ui_slider* , ui_mouse_state )
  *
  *  @sa add_click_callback_slider
  *  @sa add_release_callback_slider
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int add_hover_callback_slider ( ui_slider *p_slider, void (*callback) ( ui_slider*, ui_mouse_state ) );

/** !
  *  Add a release callback.
  *
  *  @param p_slider : Pointer to slider
  *  @param callback : function pointer. Should be of type int (callback) ( ui_slider* , ui_mouse_state )
  *
  *  @sa add_click_callback_slider
  *  @sa add_hover_callback_slider
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int add_release_callback_slider ( ui_slider *p_slider, void (*callback) ( ui_slider*, ui_mouse_state ) );

// Drawing
/** !
  *  Draw a UI slider.
  *
  *  @param window   : Pointer to UI window
  *  @param p_slider : Pointer to slider 
  *
  *  @sa draw_element
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int draw_slider ( ui_window *window, ui_slider *p_slider );

// Bounds
/** !
  *  Checks for pointer slider overlap
  * 
  *  @param p_slider    : Pointer to slider
  *  @param mouse_state : Mouse state
  *
  *  @return true if cursor is on the slider, and false otherwise
  */
DLLEXPORT bool slider_in_bounds ( ui_slider *p_slider, ui_mouse_state mouse_state );

// Deallocators
/** !
  *  Deallocates a slider and its contents
  *  @param p_slider    : Pointer to slider
  *
  *  @return 
  */
DLLEXPORT int destroy_slider ( ui_slider *p_slider );