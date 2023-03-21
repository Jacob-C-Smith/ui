#pragma once
#include <stdio.h>

#include <dict/dict.h>

#include <JSON/JSON.h>

#include <UI/UItypedef.h>
#include <UI/UIElement.h>

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

 /* !
  *  Allocate a UI Slider
  *
  *  @param pp_slider : Pointer to pointer to slider
  *  
  *  @sa destroy_slider
  *  
  *  @return 0 on success, -1 on error.  
  */
DLLEXPORT int           create_slider               ( UISlider_t  **pp_slider );

// Constructors
 /* !
  *  Load a UI Slider from a dict 
  *
  *  @param pp_slider    : Pointer to pointer to slider
  *  @param p_dictionary : Pointer to dict 
  * 
  *  @sa load_element_as_json 
  *  
  *  @return 0 on success, -1 on error.  
  */
DLLEXPORT int           load_slider_as_dict         ( UISlider_t **pp_slider, dict *dictionary );

// Callbacks

/* !
  *  Fire each hover callbacks. 
  *
  *  @param p_slider    : Pointer to slider
  *  @param mouse_state : Mouse state 
  * 
  *  @sa click_slider
  *  @sa release_slider
  *
  *  @return 0 on success, -1 on error.
  */
DLLEXPORT int           hover_slider                ( UISlider_t     *p_slider , ui_mouse_state_t mouse_state );

/* !
  *  Fire each click callbacks. 
  *
  *  @param p_slider    : Pointer to slider
  *  @param mouse_state : Mouse state 
  * 
  *  @sa hover_slider
  *  @sa release_slider
  *
  *  @return 0 on success, -1 on error.
  */
DLLEXPORT int           click_slider                ( UISlider_t     *p_slider , ui_mouse_state_t mouse_state );

/* !
  *  Fire each release callbacks. 
  *
  *  @param p_slider    : Pointer to slider
  *  @param mouse_state : Mouse state 
  *
  *  @sa click_slider
  *  @sa hover_slider
  *
  *  @return 0 on success, -1 on error.
  */
DLLEXPORT int           release_slider              ( UISlider_t     *p_slider , ui_mouse_state_t mouse_state );

// Add callbacks

/* !
  *  Add a click callback.
  *
  *  @param p_slider : Pointer to slider
  *  @param callback : function pointer. Should be of type int callback ( UISlider_t* , ui_mouse_state_t )
  *
  *  @sa add_hover_callback_slider
  *  @sa add_release_callback_slider
  *
  *  @return 0 on success, -1 on error.
  */
DLLEXPORT int           add_click_callback_slider   ( UISlider_t     *p_slider , void (*callback) ( UISlider_t*, ui_mouse_state_t ) );

/* !
  *  Add a hover callback.
  *
  *  @param p_slider : Pointer to slider
  *  @param callback : function pointer. Should be of type int callback ( UISlider_t* , ui_mouse_state_t )
  *
  *  @sa add_click_callback_slider
  *  @sa add_release_callback_slider
  *
  *  @return 0 on success, -1 on error.
  */
DLLEXPORT int           add_hover_callback_slider   ( UISlider_t     *p_slider , void (*callback) ( UISlider_t*, ui_mouse_state_t ) );

/* !
  *  Add a release callback.
  *
  *  @param p_slider : Pointer to slider
  *  @param callback : function pointer. Should be of type int callback ( UISlider_t* , ui_mouse_state_t )
  *
  *  @sa add_click_callback_slider
  *  @sa add_hover_callback_slider
  *
  *  @return 0 on success, -1 on error.
  */
DLLEXPORT int           add_release_callback_slider ( UISlider_t     *p_slider , void (*callback) ( UISlider_t*, ui_mouse_state_t ) );

// Drawing
/* !
  *  Draw a UI slider.
  *
  *  @param window   : Pointer to UI window
  *  @param p_slider : Pointer to slider 
  *
  *  @sa draw_element
  *
  *  @return 0 on success, -1 on error.
  */
DLLEXPORT int           draw_slider                 ( UIWindow_t   *window   , UISlider_t *p_slider );

// Collision
/* !
  *  Checks for pointer slider overlap
  * 
  *  @param p_slider    : Pointer to slider
  *  @param mouse_state : Mouse state
  *
  *  @return true if cursor is on the slider, and false otherwise
  */
DLLEXPORT bool          slider_in_bounds            ( UISlider_t     *p_slider , ui_mouse_state_t mouse_state );

// Deallocators
/* !
  *  Deallocates a slider and its contents
  *  @param p_slider    : Pointer to slider
  *
  *  @return 
  */
DLLEXPORT int           destroy_slider              ( UISlider_t     *p_slider );