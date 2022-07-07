#pragma once

#include <UI/UItypedef.h>
#include <UI/UI.h>

#include <UI/UIButton.h>
//#include <UI/UICanvas.h>
#include <UI/UICheckbox.h>
//#include <UI/UIChart.h>
#include <UI/UICheckbox.h>
#include <UI/UIDropdown.h>
//#include <UI/UIImage.h>
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
    UITextInput_t   *text_input;
};

struct UIElement_s
{
    char               *name,
                       *type;
    union UIElement_u   element;
};

// Allocators 
DLLEXPORT int          create_element               ( UIElement_t **element );

// Constructors
DLLEXPORT int          load_element                 ( UIElement_t **element, const char   path[] );
DLLEXPORT int          load_element_as_json         ( UIElement_t **element, char        *token_text );
DLLEXPORT int          construct_element            ( UIElement_t **element, char        *name      , char *type, void          *element_data );

// Callbacks
DLLEXPORT int          click_element                ( UIElement_t *element   , mouse_state_t  mouse_state );
DLLEXPORT int          hover_element                ( UIElement_t *element   , mouse_state_t  mouse_state );
DLLEXPORT int          release_element              ( UIElement_t *element   , mouse_state_t  mouse_state );

// Add callbacks
DLLEXPORT int          add_click_callback_element   ( UIElement_t *element, void          (*callback)(UIElement_t*, mouse_state_t));
DLLEXPORT int          add_hover_callback_element   ( UIElement_t *element, void          (*callback)(UIElement_t*, mouse_state_t));
DLLEXPORT int          add_release_callback_element ( UIElement_t *element, void          (*callback)(UIElement_t*, mouse_state_t));

// Bounds detection
DLLEXPORT bool         in_bounds                    ( UIElement_t *element   , mouse_state_t  mouse_state );

// Drawing
DLLEXPORT int          draw_element                 ( UIWindow_t  *window    , UIElement_t   *element );

// Destructor
DLLEXPORT int          destroy_element              ( UIElement_t *element );
