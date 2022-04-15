#include <UI/UIWindow.h>

UIWindow_t  *create_window            ( void )
{
	// Initialized data
	UIWindow_t *ret = calloc(1, sizeof(UIWindow_t));

	// Check memory
	{
		#ifndef NDEBUG
			if(ret==(void*)0)
				goto noMem;
		#endif
	}

	return ret;

	// Argument check
	{
		noMem:
		#ifndef NDEBUG
			ui_print_error("[UI] [Window] Failed to allocate memory in call to function \"%s\"\n", __FUNCSIG__);
		#endif
		return 0;
	}
}

UIWindow_t  *load_window              ( const char *path )
{
	// Argument check
	{
		#ifndef NDEBUG
			if(path==(void*)0)
				goto noPath;
		#endif
	}

	// Uninitialized data
	u8         *data;
	UIButton_t *ret;

	// Initialized data
	size_t      i   = 0;

	// Load up the file
	i    = ui_load_file(path, 0, false);
	data = calloc(i, sizeof(u8));
	ui_load_file(path, data, false);

	ret = load_window_as_json(data);

	// Finish up
	free(data);

	return ret;

	// Error handling
	{
	noPath:
		#ifndef NDEBUG
			ui_print_error("[UI] [Window] Null pointer provided for \"path\"\n");
		#endif
		return 0;
	invalidFile:
		#ifndef NDEBUG
			ui_print_error("[UI] [Window] Failed to load file %s\n", path);
		#endif
		return 0;
	}
}

UIWindow_t  *load_window_as_json      ( char       *token )
{
	// TODO: Argument check

	// Initialized data
	UIWindow_t  *ret         = 0;
	size_t       len         = strlen(token),
                 token_count = parse_json(token, len, 0, (void*)0);
    JSONToken_t *tokens      = calloc(token_count, sizeof(JSONToken_t));

	char        *width       = 0,
		        *height      = 0,
		        *name        = 0,
		       **elements    = 0;

    // Parse the JSON
    parse_json(token, len, token_count, tokens);

    // Search through values and pull out relevent information
    for (size_t j = 0; j < token_count; j++)
    {
		if (strcmp("name"    , tokens[j].key) == 0)
		{
			if (tokens[j].type == JSONstring)
				name = tokens[j].value.n_where;
			else
				goto name_type_error;

			continue;
		}
		if (strcmp("width"   , tokens[j].key) == 0)
		{
			if (tokens[j].type == JSONprimative)
				width = tokens[j].value.n_where;
			else
				goto width_type_error;

			continue;
		}
		if (strcmp("height"  , tokens[j].key) == 0)
		{
			if (tokens[j].type == JSONprimative)
				height = tokens[j].value.n_where;
			else
				goto height_type_error;

			continue;

		}
		if (strcmp("elements", tokens[j].key) == 0)
		{
			if (tokens[j].type == JSONarray)
				elements = tokens[j].value.a_where;
			else
				goto element_type_error;

			continue;

		}
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

	// Make a blank window
	ret = construct_window(name, atoi(width), atoi(height));
	
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
			UIElement_t* element = (*(char *)elements[k] == '{') ? load_element_as_json(elements[k]) : load_element(elements[k]);
			
			// Error checking
			{
				#ifndef NDEBUG
					if(element == (void *)0)
						ui_print_warning("[UI] [Window] Erronious token detected at elements index %d. Skipping...\n", k+1);
				#endif
			}

			// Append the element to the window
			append_element_to_window(ret, element);
		}
	}

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
				name_type_error:
				width_type_error:
				height_type_error:
				element_type_error:
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
				no_elements:
				no_name:
				empty_name:
					return 0;
			#endif
		}
	}
}

UIWindow_t  *construct_window         ( char       *title, size_t         width      , size_t height )
{

	// Argument check
	{
		#ifndef NDEBUG
			if(title == (void *)0)
				goto no_title;
		#endif
	}

	// Initialized data
	UIWindow_t *ret       = create_window();
	size_t      title_len = strlen(title);

	// Set the window width and height
	ret->width  = width;
	ret->height = height;
	
	// Error handling
	{
		if (ret->width == 0)
			ret->width = 640;
		if (ret->height == 0)
			ret->height = 480;
	}

	// Set up the window
	{
		ret->window   = SDL_CreateWindow(ret->name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);
		SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
		ret->renderer = SDL_CreateRenderer(ret->window, -1, SDL_RENDERER_ACCELERATED);
		SDL_ShowWindow(ret->window);
		ret->is_open  = true;
	}

	// Set the window name
	{
		ret->name = calloc(title_len + 1, sizeof(u8));
		strncpy(ret->name, title, title_len);
	}

	return ret;

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

	// Initialized data
	UIElement_t* i = window->elements;

	// If there is no element, write the element pointer to the window struct
	if (i == 0)
	{
		window->elements = element;
		return 0;
	}

	// Walk to the end of the list
	while (i->next)
		i = i->next;

	// Attach the element
	i->next = element;

	return 0;
	// TODO: Error handling
}

UIElement_t *find_element             ( UIWindow_t *window, char         *name )
{
	UIElement_t *i = window->elements;

	while (i)
	{
 		if (strcmp(i->name, name) == 0)
			return i;
		i = i->next;
	}

	return 0;
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
		#endif
	}

	// Uninitialized data
	int          w,
		         h,
		         t_1,
		         t_2;

	// Initialized data
	SDL_Rect     r         = { 0,0,0,0 };

	size_t       len       = strlen(window->name),
		         g_len     = len*8;

	UIElement_t  *element  = window->elements;
	UIInstance_t *instance = ui_get_active_instance();

	// Clear the window
	{
		SDL_SetRenderDrawColor(window->renderer, (u8)instance->background, (u8)(instance->background >> 8), (u8)(instance->background >> 16), 0);
		SDL_RenderClear(window->renderer);
	}
	
	// Draw window borders
	{
		SDL_GetWindowSize(window->window, &w, &h);

		t_1 = (((w - 48) / 2) - (g_len / 2)),
		t_2 = (((w - 48) / 2) + (g_len / 2));

		r.x = w - 48, r.y = 0, r.w = 29, r.h = 11;

		SDL_SetRenderDrawColor(window->renderer, (u8)instance->primary, (u8)(instance->primary >> 8), (u8)(instance->primary >> 16), 0);
		SDL_RenderDrawLine(window->renderer, 0, 5, 0, h - 1);
		SDL_RenderDrawLine(window->renderer, w - 1, 5, w - 1, h - 1);
		SDL_RenderDrawLine(window->renderer, 0, h - 1, w - 1, h - 1);
	}

	// Draw the window name
	ui_draw_text(window->name, window, t_1 + 1, 0, 1);

	// Draw the top window border
	{
		SDL_RenderDrawLine(window->renderer, 0, 5, t_1 - 2, 5);
		SDL_RenderDrawLine(window->renderer, t_1 - 2, 0, t_1 - 2, 10);

		SDL_RenderDrawLine(window->renderer, w - 1, 5, t_2 + 1, 5);
		SDL_RenderDrawLine(window->renderer, t_2 + 1, 0, t_2 + 1, 10);

		SDL_RenderFillRect(window->renderer, &r);
	}

	// Draw the red box in the top right of the window
	{
		r.x++, r.y++, r.w -= 2, r.h -= 2;

		SDL_SetRenderDrawColor(window->renderer, 0xff, 0, 0, 0);
		SDL_RenderFillRect(window->renderer, &r);
	}

	// Draw UI elements
	while (element)
	{
		if(element != window->last)
			draw_element(window, element);
		element = element->next;
	}

	// TODO: Draw last element. Its overdraw. Its okay. I don't care enough to change it at the moment
	if(window->last)
		draw_element(window, window->last);

	// Present the window
	SDL_RenderPresent(window->renderer);

	return 0;

	// Error handling
	{
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
			const  u8* keyboardState = SDL_GetKeyboardState(NULL);

			if (keyboardState[SDL_SCANCODE_F2])
			{
				destroy_window(window);
				window = load_window("UI/UI-Window.json");
				instance->windows = window;
				window->is_open = true;
			}
			if (e.key.keysym.sym == SDLK_BACKSPACE)
			{
				if (window->last)
					if (window->last->type == UI_TEXTINPUT)
					{
						UITextInput_t* text_input = window->last->element.text_input;
						size_t text_len = strlen(text_input->text);
						
						text_input->text[text_len - 1] = (char)0;

						text_input->width = 8 + (8 * text_len - 1);

					}
			}
			else if (keyboardState[SDL_SCANCODE_ESCAPE])
				window->is_open = 0;

		}
		break;

		case SDL_MOUSEBUTTONUP:
		{
			mouse_state_t mouse_state = { 0,0,0 };

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
			release_window(instance->windows, mouse_state);

		}
		break;

		case SDL_MOUSEBUTTONDOWN:
		{
			mouse_state_t mouse_state = { 0,0,0 };

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

			click_window(instance->windows, mouse_state);
		}
		break;

		case SDL_MOUSEMOTION:
		{
			mouse_state_t mouse_state = { 0,0,0 };

			if (e.button.button == SDL_BUTTON_LEFT)
				mouse_state.button |= UI_M1;
			if (e.button.button == SDL_BUTTON_RIGHT)
				mouse_state.button |= UI_M2;
			if (e.button.button == SDL_BUTTON_MIDDLE)
				mouse_state.button |= UI_M3;

			if (e.type == SDL_MOUSEWHEEL)
			{
				if (e.wheel.y > 0)
					mouse_state.button |= UI_SWUP;
				else if (e.wheel.y < 0)
					mouse_state.button |= UI_SWDOWN;
				else;
			}

			mouse_state.x = e.button.x;
			mouse_state.y = e.button.y;

			hover_window(instance->windows, mouse_state);
		}
		break;

		case SDL_TEXTINPUT:
			if(window->last)
				if (window->last->type == UI_TEXTINPUT)
				{
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

	return 0;
}

int          click_window             ( UIWindow_t *window, mouse_state_t mouse_state )
{
	UIElement_t *i = window->elements;
	
	UIInstance_t *instance = ui_get_active_instance();

	ui_append_window(instance, ui_remove_window(instance, window->name));

	// Iterate over elements
	while (i)
	{

		// Did the user click on the element on the iterator?
		if (in_bounds(i, mouse_state))
		{
			window->last = i;
			click_element(i, mouse_state);
		}

		i = i->next;
	}

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
	{
		// TODO
	}

	return 0;
}

int          hover_window             ( UIWindow_t *window, mouse_state_t mouse_state )
{
	UIElement_t* i = window->elements;

	while (i)
	{
		if (in_bounds(i, mouse_state))
			hover_element(i, mouse_state);
		i = i->next;
	}

	return 0;
}

int          release_window           ( UIWindow_t *window, mouse_state_t mouse_state )
{
	UIElement_t* i = window->elements;

	while (i)
	{
		if (in_bounds(i, mouse_state))
			release_element(i, mouse_state);
		i = i->next;
	}

	return 0;
	return 0;
}

int          destroy_window           ( UIWindow_t *window )
{
	//free(window->name);
	SDL_DestroyWindow(window->window);
	SDL_DestroyRenderer(window->renderer);
	free(window);
}