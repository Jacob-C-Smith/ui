#include <UI/UIWindow.h>

int create_window ( UIWindow_t **pp_window )
{
	// Argument check
	{
		#ifndef NDEBUG
			if(pp_window == (void *)0)
				goto no_window;
		#endif
	}

	// Initialized data
	UIWindow_t *p_window = calloc(1, sizeof(UIWindow_t));

	// Check memory
	if ( p_window == (void *) 0 )
		goto no_mem;

	// Return a pointer to the caller
	*pp_window = p_window;
	
	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_window:
				#ifndef NDEBUG
					ui_print_error("[UI] [Window] Null pointer provided for \"p_window\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}

		// Standard library errors
		{
			no_mem:
				#ifndef NDEBUG
					ui_print_error("[Standard Library] Failed to allocate memory in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error 
				return 0;
		}


	}
}

int load_window ( UIWindow_t **pp_window, const char *path )
{

	// Argument check
	{
		#ifndef NDEBUG
			if( path      == (void *) 0 ) goto no_path;
			if( pp_window == (void *) 0 ) goto no_window;
		#endif
	}

	// Initialized data
	size_t  len  = ui_load_file(path, 0, false);
	char   *data = calloc(len, sizeof(u8));

	// Error checking
	if ( data == (void *) 0 )
		goto no_mem;

	if ( ui_load_file(path, data, false) == 0 ) 
		goto failed_to_load_file;
	
	// Load the window as JSON text
	if ( load_window_as_json(pp_window, data) == 0 )
		goto failed_to_load_window;
	
	// Clean the scope
	free(data);
	
	// Success
	return 1;

	failed_to_load_file:
	failed_to_load_window:
		return 0;

	// Error handling
	{

		// Argument errors
		{
			no_window:
				#ifndef NDEBUG
					ui_print_error("[UI] [Window] Null pointer provided for \"window\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
			no_path:
				#ifndef NDEBUG
					ui_print_error("[UI] [Window] Null pointer provided for \"path\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}

		// Standard library errors
        {
            no_mem:
                #ifndef NDEBUG
                    ui_print_error("[Standard Library] Failed to allocate memory in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
	}
}

int load_window_as_json ( UIWindow_t **pp_window, char *text )
{

	// Argument check
	{
		if ( pp_window == (void *) 0 ) goto no_window;
		if ( text      == (void *) 0 ) goto no_text;
	}

	// Initialized data
	UIInstance_t *p_instance    = ui_get_active_instance();
	UIWindow_t   *p_window      = 0;
    JSONValue_t  *p_value       = 0,
	             *p_name        = 0,
	             *p_title       = 0,
	             *p_width       = 0,
	             *p_height      = 0,
	             *p_elements    = 0;

    // Parse the window file into a JSONValue
    if ( parse_json_value(text, 0, &p_value) == 0 )
        goto failed_to_parse_json;

    // Is the JSONValue the right type?
    if ( p_value->type == JSONobject )
	{
		
        p_name = dict_get(p_value->object, "name");
        p_title = dict_get(p_value->object, "title");
        p_width = dict_get(p_value->object, "width");
        p_height = dict_get(p_value->object, "height");
        p_elements = dict_get(p_value->object, "elements");
		
		// Check for missing parameters
		if ( ! ( p_name && p_title && p_width && p_height && p_elements ) ) 
			goto missing_elements;
    }

	// Construct the window
	{

		// Initialized data
		char   *name  = 0,
		       *title = 0;
		signed  width  = 0,
		        height = 0;
		size_t element_count = 0;
		SDL_Window   *window   = 0;
		SDL_Renderer *renderer = 0;
		dict *elements = 0;
		size_t element_data_max = 0;
		UIElement_t *element_data = 0;

		// Allocate memory for a UI window
		if ( create_window(&p_window) == 0 ) 
			goto failed_to_allocate_window;

		// Set the name
		if ( p_name->type == JSONstring )
		{

			// Initialized data
			size_t name_len = strlen(p_name->string);

			// Allocate memory for the name
			name = calloc(name_len + 1, sizeof(u8));

			// Error checking
			if ( name == (void *) 0 )
				goto no_mem;

			// Copy the name
			strncpy(name, p_name->string, name_len);
		}
		// Default
		else
			goto wrong_name_type;

		// Set the width
		if ( p_width->type == JSONinteger)
			width = p_width->integer;
		else
			goto wrong_width_type;
		
		// Set the height
		if ( p_height->type == JSONinteger)
			height = p_height->integer;
		else
			goto wrong_height_type;

		// Set the window title
		if ( p_title->type == JSONstring )
		{

			// Initialized data
			size_t title_len = strlen(p_title->string);

			// Allocate memory for the title
			title = calloc(title_len + 1, sizeof(u8));

			// Error checking
			if ( title == (void *) 0 )
				goto no_mem;

			// Copy the title
			strncpy(title, p_title->string, title_len);
		}

		// Create an SDL2 window
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN);

		// These are required for window functionality
		SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
		SDL_SetHint(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, "1");

		// Create an SDL2 renderer
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		*p_window = (UIWindow_t)
		{
			.is_open = true,
			.drag = false,
			.name = name,
			.title = title,
			.width = width,
			.height = height,
			.rx = 0,
			.ry = 0,
			.last = 0,
			.window = window,
			.renderer = renderer
		};

		// Load the window elements
		if ( p_elements->type == JSONarray )
		{

			// Initialized data	
			JSONValue_t **pp_elements = 0;

			// Get the contents of the array
			{
				array_get(p_elements->list, 0, &element_count);
				pp_elements = calloc(element_count+1, sizeof(JSONValue_t *));
				array_get(p_elements->list, pp_elements, &element_count);
			}
			
			// Set the load window
			p_instance->load_window = p_window;
			
			// Set the element max and the element array
			element_data_max = element_count;
			element_data = calloc(element_count+1, sizeof(UIElement_t *));

			// Construct a dictionary to contain the elements
			dict_construct(&elements, element_count);

			p_window->element_data_max = element_data_max;
			p_window->elements = elements;
			p_window->element_data = element_data;

			// Iterate over each element
			for (size_t i = 0; i < element_count; i++)
			{

				// Initialized data
				JSONValue_t *p_element = pp_elements[i];
				UIElement_t *constructed_element = 0;

				if ( load_element_as_json_value(&constructed_element, p_element) == 0)
					goto failed_to_load_element;

				append_element_to_window(p_window, constructed_element);
				
			}
			
			// Clean up
			free(pp_elements);
			
			// Clear the instance's reference to the loading window
			p_instance->load_window = 0;
		}

		
	}
	
	// Return a pointer to the caller
	*pp_window = p_window;

	// Success
	return 1;
	
	missing_elements:
	wrong_name_type:
	failed_to_allocate_window:
	wrong_width_type:
	failed_to_parse_json:
	no_mem:
	failed_to_load_element:
	wrong_height_type:

	// Error handling
	{

		// Argument errors
		{
			no_window:
				#ifndef NDEBUG
					ui_print_error("[UI] [Window] Null pointer provided for parameter \"pp_window\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;

			no_text:
				#ifndef NDEBUG
					ui_print_error("[UI] [Window] Null pointer provided for parameter \"text\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}

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
				failed_to_load_element:	
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
				missing_properties:
					return 0;
			#endif
		}

		// Missing data
		{
			#ifndef NDEBUG
			// TODO: Print an error for each branch
				no_elements:
				failed_to_parse_json:
				no_name:
				empty_name:
					return 0;
			#endif
		}
	}
}
 
int append_element_to_window ( UIWindow_t *p_window, UIElement_t *element )
{

	// TODO: Argument check	

	dict_add(p_window->elements, element->name, element);
	
	if (p_window->element_count >= p_window->element_data_max)
		goto resize;

	resize_done:

	p_window->element_data[p_window->element_count] = element;

	p_window->element_count++;

	// Success
	return 1;
	// TODO: Error handling

	resize:
		p_window->element_data_max *= 2;
		p_window->element_data = realloc(p_window->element_data, sizeof(void *) * p_window->element_data_max);
		goto resize_done;
}

UIElement_t *find_element ( UIWindow_t *p_window, char *name )
{
	UIElement_t *ret = dict_get(p_window->elements, name);
	
	return ret;
}

int resize_window ( UIWindow_t *p_window )
{
	SDL_SetWindowSize(p_window->window, p_window->width, p_window->height);

	return 1;
}

int set_file_drop_operation ( UIWindow_t *p_window, int (*callback_function)(UIWindow_t *p_window, char *path))
{

	// Argument check
	{
		#ifndef NDEBUG
			if ( p_window          == (void *) 0 ) goto no_window;
			if ( callback_function == (void *) 0 ) goto no_callback_function;
		#endif
	}

	// Set the path drop function
	p_window->path_drop_function = callback_function;

	// Success
	return 1;

	// Error handling
	{
		
		// Argument errors
		{
			no_window:
				#ifndef NDEBUG
					ui_print_error("[UI] [Window] Null pointer provided for parameter \"p_window\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;

			no_callback_function:
				#ifndef NDEBUG
					ui_print_error("[UI] [Window] Null pointer provided for parameter \"callback_function\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;

		}
	}
}

int draw_window ( UIWindow_t *p_window )
{

	// Argument check
	{
		#ifndef NDEBUG
			if ( p_window == (void *)0 ) goto no_window;
			if ( p_window->drag )
				return 0;
		#endif
	}

	// Initialized data
	UIInstance_t *instance = ui_get_active_instance();
	int w   = 0,
		h   = 0,
		t_1 = 0,
		t_2 = 0;
	SDL_Rect r = { 0,0,0,0 };

	size_t len   = strlen(p_window->title),
		   g_len = len * 8;

	dict *elements = p_window->elements;


	// Clear the window
	SDL_SetRenderDrawColor(p_window->renderer, (u8)instance->background, (u8)(instance->background >> 8), (u8)(instance->background >> 16), 0);
	(p_window->renderer);
	SDL_RenderClear(p_window->renderer);
	
	// Window parameters
	{
		SDL_GetWindowSize(p_window->window, &w, &h);

		// Spacing 
		t_1 = (((w - 48) / 2) - (g_len / 2)),
		t_2 = (((w - 48) / 2) + (g_len / 2));
		r.x = w - 48, r.y = 0, r.w = 29, r.h = 11;
	}

	// Draw window borders
	{
		SDL_SetRenderDrawColor(p_window->renderer, (u8)instance->primary, (u8)(instance->primary >> 8), (u8)(instance->primary >> 16), 0);
		SDL_RenderDrawLine(p_window->renderer, 0, 5, 0, h - 1);
		SDL_RenderDrawLine(p_window->renderer, w - 1, 5, w - 1, h - 1);
		SDL_RenderDrawLine(p_window->renderer, 0, h - 1, w - 1, h - 1);
	}

	// Draw the top window border
	{
		SDL_RenderDrawLine(p_window->renderer, 0, 5, t_1 - 2, 5);
		SDL_RenderDrawLine(p_window->renderer, t_1 - 2, 0, t_1 - 2, 10);
		SDL_RenderDrawLine(p_window->renderer, w - 1, 5, t_2 + 2, 5);
		SDL_RenderDrawLine(p_window->renderer, t_2 + 2, 0, t_2 + 2, 10);
		SDL_RenderFillRect(p_window->renderer, &r);
	}

	// Draw the window title
	ui_draw_text(p_window->title, p_window, t_1 + 1, 0, 1);

	// Draw the red box in the top right of the window
	{

		// Adjust the rectangle
		r.x++, r.y++, r.w -= 2, r.h -= 2;
			
		// In focus
		if (instance->active_window == p_window)
			SDL_SetRenderDrawColor(p_window->renderer, 0xff, 0, 0, 0);

		// Out of focus
		else
			SDL_SetRenderDrawColor(p_window->renderer, 0xc0, 0xc0, 0xc0, 0);

		// Draw the box
		SDL_RenderFillRect(p_window->renderer, &r);
	}

	// Draw UI elements
	if ( p_window->element_count )
	{

		// Iterate over element pointer list
		for (size_t i = 0; i < p_window->element_count; i++)

			// Draw each element
			draw_element(p_window, p_window->element_data[i]);

		// Redraw the last element (to avoid overdraw)
		if ( p_window->last )
			draw_element(p_window, p_window->last);

	}

	// Present the window
	SDL_RenderPresent(p_window->renderer);

	// Success
	return 1;

	// TODO: Error handling
	{
		no_mem:
		no_window:
			return 0;
	}
}

int process_window_input ( UIWindow_t *p_window )
{

	// Argument check
	{
		#ifndef NDEBUG
			if ( p_window == (void *) 0 ) goto no_window;
		#endif
	}

	// Initialized data
	UIInstance_t *instance = ui_get_active_instance();
	SDL_Event     e;

	dict_values(p_window->elements, p_window->element_data);

	// Process events
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{

		case SDL_QUIT:
			p_window->is_open = false;
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
				if (p_window->last)
				{
					if (strcmp(p_window->last->type, "TEXT INPUT") == 0)
					{
						UITextInput_t* text_input = p_window->last->text_input;
						size_t text_len = strlen(text_input->text);
						
						text_input->text[text_len - 1] = (char)0;

						text_input->width = 8 + (8 * text_len - 1);

					}
				}
				else if (strcmp(p_window->last->type, "TABLE") == 0)
				{
					p_window->last->table->last_x++;
				}
			}
			else if (e.key.keysym.sym == SDLK_TAB)
			{
				if (p_window->last)
					if (strcmp(p_window->last->type, "TEXT INPUT") == 0)
					{
						UITextInput_t *next       = 0;
						size_t last_i    = 0,
							   current_i = 0;

						// Find the current window->last index in the element list
						for (size_t i = 0; i < p_window->element_count; i++)
							if (p_window->element_data[i] == p_window->last)
								last_i = i;

						for (size_t i = p_window->element_count; i > 0; i--)
							if (strcmp(p_window->element_data[(last_i + i) % p_window->element_count]->type, "TEXT INPUT") == 0)
							{
								if ( p_window->element_data[(last_i + i) % p_window->element_count]->draw == false )
									continue;
									
								p_window->last = p_window->element_data[(last_i + i) % p_window->element_count];
							}
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
			
			release_window(p_window, mouse_state);

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

			click_window(p_window, mouse_state);
		}
		break;

		case SDL_MOUSEMOTION:
		{

			// Is the window being dragged?
			// TODO: Fix mouse cursor snapping to top left corner of window
			if (p_window->drag)
			{
				p_window->rx += e.motion.xrel,
				p_window->ry += e.motion.yrel;
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


			hover_window(p_window, mouse_state);
		}
		break;

		case SDL_TEXTINPUT:
			if(p_window->last)
				if (strcmp(p_window->last->type, "TEXT INPUT") == 0)
				{//
					UITextInput_t* text_input = p_window->last->text_input;
					strcat(text_input->text, e.text.text);
					text_input->width = 8 + (8 * strlen(text_input->text));
				}
			break;
		case SDL_WINDOWEVENT:
			break;
		case SDL_DROPFILE:
		{
			if ( p_window->path_drop_function )
				p_window->path_drop_function(p_window, e.drop.file);
		}
		default:
			break;
		}
	}
	
	if (p_window->drag)
	{
		int x = 0, y = 0;

		SDL_GetGlobalMouseState(&x, &y);
		SDL_SetWindowPosition(p_window->window, x, y);
	}
	return 0;
	
	// TODO: Error handling
	{
		no_mem:
		no_window:
			return 0;
	}
}

int click_window ( UIWindow_t *p_window, ui_mouse_state_t mouse_state )
{
	dict          *elements = p_window->elements;
	void         **values   = 0;
	UIInstance_t  *instance = ui_get_active_instance();


	// Did the user click on the element on the iterator?
	for (size_t i = 0; i < p_window->element_count; i++)
		if (in_bounds(p_window->element_data[i], mouse_state))
			click_element(p_window->element_data[i], mouse_state);

	// Close window?
	{
		int w, h;

		SDL_GetWindowSize(p_window->window, &w, &h);
		
		if (mouse_state.x >= w - 48 && mouse_state.y >= 0 && mouse_state.x <= w - 20 && mouse_state.y <= 11)
		{

			// Left clicks minimize the window
			if (mouse_state.button & UI_M2)
				SDL_MinimizeWindow(p_window->window);

			// Right clicks close the window
			else if (mouse_state.button & UI_M1)
				p_window->is_open = false;
		}
	}
	
	// Drag window?
	if(p_window->drag == false) {
		int w, h;

		SDL_GetWindowSize(p_window->window, &w, &h);
		p_window->rx = 0;
		p_window->ry = 0;
		if (mouse_state.x >= 0 && mouse_state.y >= 0 && mouse_state.x <= w - 48 && mouse_state.y <= 11)
		{
			// Drag the window
			if (mouse_state.button & UI_M1)
			{
				
				p_window->rx = mouse_state.x,
				p_window->ry = mouse_state.y;
				p_window->drag = true;
			}
		}
	}

	return 0;
}

int hover_window ( UIWindow_t *p_window, ui_mouse_state_t mouse_state )
{
	dict         *elements = p_window->elements;
	UIInstance_t *instance = ui_get_active_instance();

	if (p_window->drag)
		SDL_SetWindowPosition(p_window, p_window->rx+mouse_state.x, p_window->ry+mouse_state.y);

	// Iterate over elements

	// Did the user click on the element on the iterator?
	for (size_t i = 0; i < p_window->element_count; i++)
		if (in_bounds(p_window->element_data[i], mouse_state))
			hover_element(p_window->element_data[i], mouse_state);

	

	return 0;
}

int release_window ( UIWindow_t *p_window, ui_mouse_state_t mouse_state )
{
	dict* elements = p_window->elements;
	UIInstance_t* instance = ui_get_active_instance();

	if (p_window->drag)
		p_window->drag = false;

	// Iterate over elements

	// Did the user click on the element on the iterator?
	for (size_t i = 0; i < p_window->element_count; i++)
		if (in_bounds(p_window->element_data[i], mouse_state))
			release_element(p_window->element_data[i], mouse_state);

	return 0;
}

int destroy_window ( UIWindow_t *p_window )
{

	// Argument check
	{
		#ifndef NDEBUG
			if ( p_window == (void *) 0 )
				goto no_window;
		#endif
	}

	// Close the window
	p_window->is_open = false;

	// Free the window name
	free(p_window->name);

	// Free the window title
	free(p_window->title);

	// Free the window elements
	//dict_free_clear(p_window->elements, destroy_element);
	free(p_window->element_data);

	// Free the SDL2 renderer
	SDL_DestroyRenderer(p_window->renderer);

	// Free the SDL2 window
	SDL_DestroyWindow(p_window->window);

	// Free the UI Window
	free(p_window);

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_window:
				#ifndef NDEBUG
					printf("[UI] [Window] Null pointer provided for parameter \"p_window\" in call to function \"%s\"\n");
				#endif

				// Error
				return 0;
		}
	}
}