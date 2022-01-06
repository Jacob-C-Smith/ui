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
	size_t             ui_elements_count;
	void             **ui_elements;
	char              *name;
	SDL_Window        *window;
	SDL_Renderer      *renderer;
	struct UIWindow_s *next;
};

UIWindow_t  *createWindow       ( );
 
UIWindow_t  *loadWindow         ( const char *path );
UIWindow_t  *loadWindowAsJSON   ( char       *token );

int          drawWindow         ( UIWindow_t *window );

int          destroyWindow      ( UIWindow_t *window );

