#pragma once

#include <JSON/JSON.h>

#include <UI/UItypedef.h>
#include <UI/UI.h>

#include <UI/UItypedef.h>
#include <UI/UIButton.h>
#include <UI/UICanvas.h>
#include <UI/UIChart.h>
#include <UI/UICheckbox.h>
#include <UI/UIDropdown.h>
#include <UI/UIImage.h>
#include <UI/UILabel.h>
#include <UI/UIRadioButton.h>
#include <UI/UISlider.h>
#include <UI/UITextInput.h>

struct UIWindow_s {
	bool               is_open;
	char              *name;
	UIElement_t       *elements;
	UIElement_t       *last;
	SDL_Window        *window;
	SDL_Renderer      *renderer;
	struct UIWindow_s *next;
};

UIWindow_t  *create_window            ( void );
 
UIWindow_t  *load_window              ( const char *path );
UIWindow_t  *load_window_as_json      ( char       *token );

int          append_element_to_window ( UIWindow_t *window, UIElement_t   *element );
UIElement_t *find_element             ( UIWindow_t *window, char *name );

int          click_window             ( UIWindow_t *window, mouse_state_t  mouse_state );
int          hover_window             ( UIWindow_t *window, mouse_state_t  mouse_state );

int          draw_window              ( UIWindow_t *window );

int          destroy_window           ( UIWindow_t *window );

