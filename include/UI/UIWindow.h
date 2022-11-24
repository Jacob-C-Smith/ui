#pragma once

#include <string.h>

#include <dict/dict.h>
#include <JSON/JSON.h>

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
#include <UI/UITextInput.h>


struct UIWindow_s {
	bool               is_open,
	                   drag;
	char              *name;
	size_t             width,
		               height;
	i32                rx,
		               ry;
	dict              *elements;
	UIElement_t       *last;
	SDL_Window        *window;
	SDL_Renderer      *renderer;
};

// Allocators
DLLEXPORT int          create_window            ( UIWindow_t  **window );
 
// Constructors
DLLEXPORT int          load_window              ( UIWindow_t  **window, const char *path );
DLLEXPORT int          load_window_as_json      ( UIWindow_t  **window, char       *token_text );
DLLEXPORT int          construct_window         ( UIWindow_t  **window, char       *title, size_t width, size_t height, size_t element_count );

// Element operations
DLLEXPORT int          append_element_to_window ( UIWindow_t *window, UIElement_t   *element );
DLLEXPORT UIElement_t *find_element             ( UIWindow_t *window, char *name );

DLLEXPORT int          resize_window            ( UIWindow_t *window );

// User interaction
DLLEXPORT int          process_window_input     ( UIWindow_t *window );
DLLEXPORT int          click_window             ( UIWindow_t *window, ui_mouse_state_t  mouse_state );
DLLEXPORT int          hover_window             ( UIWindow_t *window, ui_mouse_state_t  mouse_state );
DLLEXPORT int          release_window           ( UIWindow_t *window, ui_mouse_state_t  mouse_state );

// Drawing 
DLLEXPORT int          draw_window              ( UIWindow_t *window );

// Destruction
DLLEXPORT int          destroy_window           ( UIWindow_t *window );

