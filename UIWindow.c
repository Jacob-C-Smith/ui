#include <UI/UIWindow.h>

int          create_window            ( UIWindow_t **window )
{
	// Argument check
	{
		#ifndef NDEBUG
			if(window == (void *)0)
				goto no_window;
		#endif
	}

	// Initialized data
	UIWindow_t *i_window = calloc(1, sizeof(UIWindow_t));

	// Check memory
	{
		#ifndef NDEBUG
			if(i_window ==(void*)0)
				goto no_mem;
		#endif
	}

	*window = i_window;

	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_window:
			#ifndef NDEBUG
				ui_print_error("[UI] [Window] Null pointer provided for \"window\" in call to function \"%s\"\n", __FUNCSIG__);
			#endif
			return 0;
		}

		// Standard library errors
		{
			no_mem:
			#ifndef NDEBUG
				ui_print_error("[Standard Library] Failed to allocate memory in call to function \"%s\"\n", __FUNCSIG__);
			#endif
			return 0;
		}


	}
}

int          load_window              ( UIWindow_t **window, const char *path )
{
	// Argument check
	{
		#ifndef NDEBUG
			if(path==(void*)0)
				goto noPath;
			if(window == (void *)0)
				goto no_window;
		#endif
	}

	// Uninitialized data
	u8         *data;

	// Initialized data
	size_t      i   = 0;

	// Load up the file
	{
		i    = ui_load_file(path, 0, false);
		data = calloc(i, sizeof(u8));
		ui_load_file(path, data, false);
	}
	
	load_window_as_json(window, data);
	
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_window:
			#ifndef NDEBUG
				ui_print_error("[UI] [Window] Null pointer provided for \"window\" in call to function \"%s\"\n", __FUNCSIG__);
			#endif
			return 0;
			noPath:
			#ifndef NDEBUG
				ui_print_error("[UI] [Window] Null pointer provided for \"path\"\n");
			#endif
			return 0;
		}

		// File error
		{
			invalidFile:
			#ifndef NDEBUG
				ui_print_error("[UI] [Window] Failed to load file %s\n", path);
			#endif
			return 0;
		}
	}
}

int          load_window_as_json      ( UIWindow_t **window, char       *token_text )
{
	// TODO: Argument check

	// Initialized data
	UIInstance_t *instance      = ui_get_active_instance();
	UIWindow_t   *ret           = 0;
	size_t        len           = strlen(token_text),
		          element_count = 0;
    JSONToken_t  *token         = 0;

	dict         *window_json   = 0;
	char         *width         = 0,
		         *height        = 0,
		         *name          = 0,
		        **elements      = 0;

    // Parse the JSON
    parse_json(token_text, len, &window_json);

    // Get window info
	{
		token    = dict_get(window_json, "name");
		name     = JSON_VALUE(token, JSONstring);

		token    = dict_get(window_json, "width");
		width    = JSON_VALUE(token, JSONprimative);

		token    = dict_get(window_json, "height");
		height   = JSON_VALUE(token, JSONprimative);

		token    = dict_get(window_json, "elements");
		elements = JSON_VALUE(token, JSONarray);
	}

	// Error checking
	{
		#ifndef NDEBUG
			if (name == (void*)0)
				goto no_name;
			if (strlen(name) == (void*)0)
				goto empty_name;
		#endif
	}

	while (elements[++element_count]);

	// Make a blank window
	construct_window(window, name, (width) ? atoi(width) : 640, (height) ? atoi(height) : 480, element_count);
	
	ret = *window;

	instance->load_window = ret;
	
	// Error checking
	{
		#ifndef NDEBUG
			if (ret == (void *)0)
				goto window_construction_error;
			if (elements == (void *)0)
				goto no_elements;
		#endif
	}

	// Append all the elements
	{

		// Iterate over elements
		for (size_t k = 0; elements[k]; k++)
		{
			
			// Load the element as an object or a path
			UIElement_t* element = 0;
			(*(char*)elements[k] == '{') ? load_element_as_json(&element, elements[k]) : load_element(&element, elements[k]);
			
			// Error checking
			{
				#ifndef NDEBUG
					if(element == (void *)0)
					{
						ui_print_warning("[UI] [Window] Erronious token detected at elements index %d. Skipping...\n", k);
						continue;
					}
				#endif
			}

			// Append the element to the window
			append_element_to_window(ret, element);
		}
	}

	instance->load_window = 0;

	return ret;
	
	// Error handling
	{

		// Standard library errors
		{
			#ifndef NDEBUG
				no_mem:
					return 0;
			#endif
		}

		// JSON type errors
		{
			#ifndef NDEBUG
				// TODO: Print an error for each branch
				name_type_error:
				return 0;
				width_type_error:
					return 0;
				height_type_error:
					return 0;
				element_type_error:
					return 0;
				return 0;
			#endif
		}

		// Constructor errors
		{
			#ifndef NDEBUG
				window_construction_error:
					return 0;
			#endif
		}

		// Missing data
		{
			#ifndef NDEBUG
			// TODO: Print an error for each branch
				no_elements:
				no_name:
				empty_name:
					return 0;
			#endif
		}
	}
}

int          construct_window         ( UIWindow_t **window, char       *title, size_t         width      , size_t height, size_t element_count )
{

	// Argument check
	{
		#ifndef NDEBUG
			if(title == (void *)0)
				goto no_title;
		#endif
	}

	// Initialized data
	UIWindow_t *i_window  = 0;
	size_t      title_len = strlen(title);

	create_window(&i_window);

	// Set the window width and height
	i_window->width  = width;
	i_window->height = height;
	
	// Error handling
	{
		if (i_window->width == 0)
			i_window->width = 640;
		if (i_window->height == 0)
			i_window->height = 480;
	}

	// Set up the window
	{
		i_window->window   = SDL_CreateWindow(i_window->name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);
		SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
		SDL_SetHint(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, "1");
		i_window->renderer = SDL_CreateRenderer(i_window->window, -1, SDL_RENDERER_ACCELERATED);
		SDL_ShowWindow(i_window->window);
		i_window->is_open  = true;
	}

	// Set the window name
	{
		i_window->name = calloc(title_len + 1, sizeof(u8));
		strncpy(i_window->name, title, title_len);
	}

	dict_construct(&i_window->elements, element_count);

	*window = i_window;

	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_title:
				return 0;
		}
	}
}

int          append_element_to_window ( UIWindow_t *window, UIElement_t  *element )
{

	// TODO: Argument check	

	dict_add(window->elements, element->name, element);

	return 0;
	// TODO: Error handling
}

UIElement_t *find_element             ( UIWindow_t *window, char         *name )
{
	UIElement_t *ret = dict_get(window->elements, name);
	
	return ret;
}

int          resize_window            ( UIWindow_t *window )
{
	SDL_SetWindowSize(window->window, window->width, window->height);

	return 0;
}

int          draw_window              ( UIWindow_t *window )
{

	// Argument check
	{
		#ifndef NDEBUG
			if (window == (void *)0)
				goto no_window;
			if (window->drag)
				return 0;
		#endif
	}

	// Uninitialized data
	int          w,
		         h,
		         t_1,
		         t_2;

	// Initialized data
	SDL_Rect      r         = { 0,0,0,0 };

	size_t        len       = strlen(window->name),
		          g_len     = len * 8;

	dict         *elements  = window->elements;

	UIInstance_t *instance = ui_get_active_instance();

	// Clear the window
	{
		SDL_SetRenderDrawColor(window->renderer, (u8)instance->background, (u8)(instance->background >> 8), (u8)(instance->background >> 16), 0);
		SDL_RenderClear(window->renderer);
	}
	
	// Draw the window
	{

		// Window parameters
		{
			SDL_GetWindowSize(window->window, &w, &h);

			// Spacing 
			t_1 = (((w - 48) / 2) - (g_len / 2)),
			t_2 = (((w - 48) / 2) + (g_len / 2));
			r.x = w - 48, r.y = 0, r.w = 29, r.h = 11;
		}

		// Draw window borders
		{
			SDL_SetRenderDrawColor(window->renderer, (u8)instance->primary, (u8)(instance->primary >> 8), (u8)(instance->primary >> 16), 0);
			SDL_RenderDrawLine(window->renderer, 0, 5, 0, h - 1);
			SDL_RenderDrawLine(window->renderer, w - 1, 5, w - 1, h - 1);
			SDL_RenderDrawLine(window->renderer, 0, h - 1, w - 1, h - 1);
		}

		// Draw the top window border
		{
			SDL_RenderDrawLine(window->renderer, 0, 5, t_1 - 2, 5);
			SDL_RenderDrawLine(window->renderer, t_1 - 2, 0, t_1 - 2, 10);

			SDL_RenderDrawLine(window->renderer, w - 1, 5, t_2 + 1, 5);
			SDL_RenderDrawLine(window->renderer, t_2 + 2, 0, t_2 + 2, 10);

			SDL_RenderFillRect(window->renderer, &r);
		}

		// Draw the window name
		ui_draw_text(window->name, window, t_1 + 1, 0, 1);

		// Draw the red box in the top right of the window
		{

			// Adjust the rectangle
			r.x++, r.y++, r.w -= 2, r.h -= 2;

			// Draw the box
			SDL_SetRenderDrawColor(window->renderer, 0xff, 0, 0, 0);
			SDL_RenderFillRect(window->renderer, &r);
		}

	}

	// Draw UI elements
	if(elements->n_entries) {

		// Allocate for a list of element pointers
		void** values = calloc(elements->n_entries, sizeof(void*));

		// Error check
		{
			#ifndef NDEBUG
				if(values == (void*)0)
					goto no_mem;
			#endif
		}

		// Populate element pointer list
		dict_values(elements, values);

		// Iterate over element pointer list
		for (size_t i = 0; i < elements->n_entries; i++)

			// Draw each element
			draw_element(window, values[i]);

		// Redraw the last element 
		if(window->last)
			draw_element(window, window->last);

		// Free element list
		free(values);
	}

	// Present the window
	SDL_RenderPresent(window->renderer);

	return 0;

	// TODO: Error handling
	{
		no_mem:
		no_window:
			return 0;
	}
}

int          process_window_input     ( UIWindow_t *window )
{
	UIInstance_t *instance = ui_get_active_instance();
	SDL_Event     e;

	// Process events
	while (SDL_PollEvent(&e)) {
		switch (e.type)
		{

		case SDL_QUIT:
			window->is_open = false;
			break;

		case SDL_KEYDOWN:
		{
			/*const  u8* keyboardState = SDL_GetKeyboardState(NULL);

			if (keyboardState[SDL_SCANCODE_F2])
			{
				destroy_window(window);
				window = load_window("UI/UI-Window.json");
				instance->windows = window;
				window->is_open = true;
			}*/
			if (e.key.keysym.sym == SDLK_BACKSPACE)
			{
				if (window->last)
					if (strcmp(window->last->type, "TEXT INPUT") == 0)
					{
						UITextInput_t* text_input = window->last->element.text_input;
						size_t text_len = strlen(text_input->text);
						
						text_input->text[text_len - 1] = (char)0;

						text_input->width = 8 + (8 * text_len - 1);

					}
			}

		}
		break;

		case SDL_MOUSEBUTTONUP:
		{
			ui_mouse_state_t mouse_state = { 0,0,0 };

			// Create the mouse_state struct
			{
				if (e.button.button == SDL_BUTTON_LEFT)
					mouse_state.button |= UI_M1;
				if (e.button.button == SDL_BUTTON_MIDDLE)
					mouse_state.button |= UI_M3;
				if (e.button.button == SDL_BUTTON_RIGHT)
					mouse_state.button |= UI_M2;
				if (e.wheel.y > 0)
				{
					mouse_state.button |= UI_SWUP;
				}
				if (e.wheel.y < 0)
				{
					mouse_state.button |= UI_SWDOWN;
				}
				mouse_state.x = e.button.x;
				mouse_state.y = e.button.y;
			}
			
			release_window(window, mouse_state);

		}
		break;

		case SDL_MOUSEBUTTONDOWN:
		{
			ui_mouse_state_t mouse_state = { 0,0,0 };

			// Create the mouse_state struct
			{
				if (e.button.button == SDL_BUTTON_LEFT)
					mouse_state.button |= UI_M1;
				if (e.button.button == SDL_BUTTON_MIDDLE)
					mouse_state.button |= UI_M3;
				if (e.button.button == SDL_BUTTON_RIGHT)
					mouse_state.button |= UI_M2;
				if (e.wheel.y > 0)
					mouse_state.button |= UI_SWUP;
				if (e.wheel.y < 0)
					mouse_state.button |= UI_SWDOWN;
				mouse_state.x = e.button.x;
				mouse_state.y = e.button.y;
			}

			click_window(window, mouse_state);
		}
		break;

		case SDL_MOUSEMOTION:
		{

			// Is the window being dragged?
			// TODO: Fix mouse cursor snapping to top left corner of window
			if (window->drag)
			{
				window->rx += e.motion.xrel,
				window->ry += e.motion.yrel;
			}

			// This is used for the oncoming callbacks
			ui_mouse_state_t mouse_state = { 0,0,0 };

			// Set the button state
			{

				// Left mouse click?
				if (e.button.button == SDL_BUTTON_LEFT)
					mouse_state.button |= UI_M1;

				// Right mouse click?
				if (e.button.button == SDL_BUTTON_RIGHT)
					mouse_state.button |= UI_M2;

				// Middle mouse click?
				if (e.button.button == SDL_BUTTON_MIDDLE)
					mouse_state.button |= UI_M3;

				// Scroll wheel?
				if (e.type == SDL_MOUSEWHEEL)
				{
					if (e.wheel.y > 0)
						mouse_state.button |= UI_SWUP;
					else if (e.wheel.y < 0)
						mouse_state.button |= UI_SWDOWN;
					else;
				}

				// Set the mouse location
				mouse_state.x = e.button.x;
				mouse_state.y = e.button.y;
			}


			hover_window(window, mouse_state);
		}
		break;

		case SDL_TEXTINPUT:
			if(window->last)
				if (strcmp(window->last->type, "TEXT INPUT") == 0)
				{//
					UITextInput_t* text_input = window->last->element.text_input;
					strcat(text_input->text, e.text.text);
					text_input->width = 8 + (8 * strlen(text_input->text));
				}
			break;
		case SDL_WINDOWEVENT:
			break;
		default:
			break;
		}
	}
	
	if (window->drag)
	{
		int x = 0, y = 0;

		SDL_GetGlobalMouseState(&x, &y);
		SDL_SetWindowPosition(window->window, x, y);
	}
	return 0;
}

int          click_window             ( UIWindow_t *window, ui_mouse_state_t mouse_state )
{
	dict          *elements = window->elements;
	void         **values   = 0;
	UIInstance_t  *instance = ui_get_active_instance();

	// Iterate over elements
	values = calloc(elements->n_entries, sizeof(void*));
	dict_values(elements, values);

	// Did the user click on the element on the iterator?
	for (size_t i = 0; i < elements->n_entries; i++)
		if (in_bounds(values[i], mouse_state))
			click_element(values[i], mouse_state);

	// Close window?
	{
		int w, h;

		SDL_GetWindowSize(window->window, &w, &h);
		
		if (mouse_state.x >= w - 48 && mouse_state.y >= 0 && mouse_state.x <= w - 20 && mouse_state.y <= 11)
		{

			// Left clicks minimize the window
			if (mouse_state.button & UI_M2)
				SDL_MinimizeWindow(window->window);

			// Right clicks close the window
			else if (mouse_state.button & UI_M1)
				window->is_open = false;
		}
	}
	
	// Drag window?
	if(window->drag == false) {
		int w, h;

		SDL_GetWindowSize(window->window, &w, &h);
		window->rx = 0;
		window->ry = 0;
		if (mouse_state.x >= 0 && mouse_state.y >= 0 && mouse_state.x <= w - 48 && mouse_state.y <= 11)
		{
			// Drag the window
			if (mouse_state.button & UI_M1)
			{
				
				window->rx = mouse_state.x,
				window->ry = mouse_state.y;
				window->drag = true;
			}
		}
	}

	return 0;
}

int          hover_window             ( UIWindow_t *window, ui_mouse_state_t mouse_state )
{
	dict* elements = window->elements;
	void** values = 0;
	UIInstance_t* instance = ui_get_active_instance();

	if (window->drag)
		SDL_SetWindowPosition(window, window->rx+mouse_state.x, window->ry+mouse_state.y);

	// Iterate over elements
	values = calloc(elements->n_entries, sizeof(void*));
	dict_values(elements, values);

	// Did the user click on the element on the iterator?
	for (size_t i = 0; i < elements->n_entries; i++)
		if (in_bounds(values[i], mouse_state))
			hover_element(values[i], mouse_state);

	

	return 0;
}

int          release_window           ( UIWindow_t *window, ui_mouse_state_t mouse_state )
{
	dict* elements = window->elements;
	void** values = 0;
	UIInstance_t* instance = ui_get_active_instance();

	if (window->drag)
		window->drag = false;

	// Iterate over elements
	values = calloc(elements->n_entries, sizeof(void*));
	dict_values(elements, values);

	// Did the user click on the element on the iterator?
	for (size_t i = 0; i < elements->n_entries; i++)
		if (in_bounds(values[i], mouse_state))
			release_element(values[i], mouse_state);

	return 0;
}

int          destroy_window           ( UIWindow_t *window )
{
	//free(window->name);
	SDL_DestroyRenderer(window->renderer);
	SDL_DestroyWindow(window->window);
	free(window);
}