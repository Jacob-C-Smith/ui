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

union UIElement_u
{
    UIButton_t      *button;
    UICanvas_t      *canvas;
    UIChart_t       *chart;
    UICheckbox_t    *checkbox;
    UIDropdown_t    *dropdown;
    UIImage_t       *image;
    UILabel_t       *label;
    UIRadioButton_t *radio_button;
    UISlider_t      *slider;
    UITable_t       *table;
    UITextInput_t   *text_input;
};

struct UIElement_s
{
    char               *name,
                       *type;
    union UIElement_u   element;
};

// Allocators 

 /* !
  *  Allocate a UI Element
  *
  *  @param pp_element : Pointer to pointer to element
  *  
  *  @sa destroy_element
  *  
  *  @return 0 on success, -1 on error.  
  */
DLLEXPORT int          create_element               ( UIElement_t **element );

// Constructors

 /* !
  *  Load a UI Button from a dict 
  *
  *  @param pp_element : Pointer to pointer to element
  *  @param path       : Path to element file
  * 
  *  @sa load_element_as_json 
  *  
  *  @return 0 on success, -1 on error.  
  */
DLLEXPORT int          load_element                 ( UIElement_t **element, const char   path[] );

 /* !
  *  Load a UI Button from JSON text
  *
  *  @param pp_element : Pointer to pointer to element
  *  @param token_text : JSON token text
  * 
  *  @return 0 on success, -1 on error.  
  */
DLLEXPORT int          load_element_as_json         ( UIElement_t **element, char        *token_text );
DLLEXPORT int          construct_element            ( UIElement_t **element, char        *name      , char *type, void          *element_data );

// Callbacks
DLLEXPORT int          click_element                ( UIElement_t *element   , ui_mouse_state_t  mouse_state );
DLLEXPORT int          hover_element                ( UIElement_t *element   , ui_mouse_state_t  mouse_state );
DLLEXPORT int          release_element              ( UIElement_t *element   , ui_mouse_state_t  mouse_state );

// Add callbacks
DLLEXPORT int          add_click_callback_element   ( UIElement_t *element, void          (*callback)(UIElement_t*, ui_mouse_state_t));
DLLEXPORT int          add_hover_callback_element   ( UIElement_t *element, void          (*callback)(UIElement_t*, ui_mouse_state_t));
DLLEXPORT int          add_release_callback_element ( UIElement_t *element, void          (*callback)(UIElement_t*, ui_mouse_state_t));

// Bounds detection
DLLEXPORT bool         in_bounds                    ( UIElement_t *element   , ui_mouse_state_t  mouse_state );

// Drawing
DLLEXPORT int          draw_element                 ( UIWindow_t  *window    , UIElement_t   *element );

// Destructor
DLLEXPORT int          destroy_element              ( UIElement_t *element );
