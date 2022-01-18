#pragma once

#include <UI/UItypedef.h>
#include <UI/UI.h>

union UIElement_u
{
    UIButton_t      *button;
    UICanvas_t      *canvas;
    UIChart_t       *chart;
    UICheckbox_t    *checkbox;
    UIContainer_t   *container;
    UIDropdown_t    *dropdown;
    UIImage_t       *image;
    UILabel_t       *label;
    UIRadioButton_t *radio_button;
    UISlider_t      *slider;
    UITextInput_t   *text_input;
};

struct UIElement_s
{
    u16                 type;
    union UIElement_u   element;
    struct UIElement_s *next;
};

UIElement_t *create_element       ( void );

UIElement_t *load_element         ( const char   path[] );
UIElement_t *load_element_as_json ( char        *token_text );

int          click_element        ( UIElement_t *element   , mouse_state_t mouse_state ); 
int          hover_element        ( UIElement_t *element   , mouse_state_t mouse_state );
bool         in_bounds            ( UIElement_t *element   , mouse_state_t mouse_state );
int          draw_element         ( UIWindow_t  *window    , UIElement_t *element );