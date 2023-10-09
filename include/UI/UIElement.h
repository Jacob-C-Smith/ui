#pragma once

#include <UI/UItypedef.h>
#include <UI/UI.h>

#include <UI/UIButton.h>
//#include <UI/UICanvas.h>
#include <UI/UICheckbox.h>
//#include <UI/UIChart.h>
#include <UI/UICheckbox.h>
#include <UI/UIDropdown.h>
#include <UI/UIImage.h>
#include <UI/UIRadioButton.h>
#include <UI/UISlider.h>
#include <UI/UILabel.h>
//#include <UI/UITextInput.h>

struct UIElement_s
{
    union {
        ui_button      *button;
        ui_canvas      *canvas;
        ui_chart       *chart;
        ui_checkbox    *checkbox;
        ui_dropdown    *dropdown;
        ui_image       *image;
        ui_label       *label;
        ui_radiobutton *radio_button;
        ui_slider      *slider;
        UITable_t       *table;
        ui_textinput   *text_input;
    };
    char    *name,
            *type;
    bool     draw;

};

// Allocators 

 /** !
  *  Allocate a UI Element
  *
  *  @param pp_element : Pointer to pointer to element
  *  
  *  @sa destroy_element
  *  
  *  @return 1 on success, 0 on error.  
  */
DLLEXPORT int create_element ( ui_element **pp_element );

// Constructors

 /** !
  *  Load a UI Button from a dict 
  *
  *  @param pp_element : Pointer to pointer to element
  *  @param path       : Path to element file
  * 
  *  @sa load_element_as_json 
  *  
  *  @return 1 on success, 0 on error.  
  */
DLLEXPORT int load_element ( ui_element **pp_element, const char path[] );

 /** !
  *  Load a UI Button from a JSON value
  *
  *  @param pp_element : Pointer to pointer to element
  *  @param p_value : JSON token text
  * 
  *  @return 1 on success, 0 on error.  
  */
DLLEXPORT int load_element_as_json_value ( ui_element **pp_element, json_value *p_value );
DLLEXPORT int construct_element          ( ui_element **element   , char       *name   , char *type, void *element_data );

// Callbacks
DLLEXPORT int click_element   ( ui_element *element, ui_mouse_state_t mouse_state );
DLLEXPORT int hover_element   ( ui_element *element, ui_mouse_state_t mouse_state );
DLLEXPORT int release_element ( ui_element *element, ui_mouse_state_t mouse_state );

// Add callbacks
DLLEXPORT int add_click_callback_element   ( ui_element *element, void (*callback)(ui_element*, ui_mouse_state_t) );
DLLEXPORT int add_hover_callback_element   ( ui_element *element, void (*callback)(ui_element*, ui_mouse_state_t) );
DLLEXPORT int add_release_callback_element ( ui_element *element, void (*callback)(ui_element*, ui_mouse_state_t) );

// Bounds
DLLEXPORT bool in_bounds ( ui_element *element, ui_mouse_state_t mouse_state );

// Drawing
DLLEXPORT int draw_element ( ui_window *window, ui_element *element );

// Destructor
DLLEXPORT int destroy_element ( ui_element **pp_element );
