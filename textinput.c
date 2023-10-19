#include <ui/textinput.h>

int create_text_input ( ui_textinput **pp_text_input )
{

	// Argument check
	if ( pp_text_input == (void *) 0 ) goto no_text_input;

	// Initialized data
	ui_textinput** p_text_input = 0;

	// Allocate a text input
	p_text_input = calloc(1, sizeof(ui_textinput));

	// Error check
	if ( p_text_input == (void *) 0 ) goto no_mem;

	// Return a pointer to the caller
	*pp_text_input = p_text_input;

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_text_input:
				#ifndef NDEBUG

				#endif

				// Error
				return 0;
		}

		// Standard library errors
		{
			no_mem:
				#ifndef NDEBUG

				#endif

				// Error
				return 0;
		}
	}
}

int load_text_input_as_json_value ( ui_textinput **pp_text_input, json_value *p_value )
{

	// TODO: Argument check
	//

	// Initialized data 
	json_value *p_placeholder = 0,
		        *p_text        = 0,
		        *p_x           = 0,
		        *p_y           = 0,
		        *p_buffer_len  = 0;

	// Parse JSON
	{

		// Initialized data
		dict *p_dict = p_value->object;

		p_placeholder = dict_get(p_dict, "placeholder");
        p_text        = dict_get(p_dict, "text");
        p_x           = dict_get(p_dict, "x");
        p_y           = dict_get(p_dict, "y");
        p_buffer_len  = dict_get(p_dict, "length");

	}

	// Construct the text input
	{

		// Initialized data
		char  *placeholder = 0,
		      *text        = 0;
		i32    x           = 0,
		       y           = 0;
		size_t buffer_len  = 0;

		// Set the placeholder
		if ( p_placeholder->type == JSON_VALUE_STRING )
			placeholder = p_placeholder->string;
		// Default
		else
			goto wrong_placeholder_type;
		
		// Set the text
		if ( p_text )
		{
			if ( p_text->type == JSON_VALUE_STRING )
				text = p_text->string;
			// Default
			else
				goto wrong_text_type;
		}
		// Set the x
		if ( p_x->type == JSON_VALUE_INTEGER )
			x = p_x->integer;
		// Default
		else
			goto wrong_x_type;

		// Set the y
		if ( p_y->type == JSON_VALUE_INTEGER )
			y = p_y->integer;
		// Default
		else
			goto wrong_y_type;

		// Set the buffer length
		if ( p_buffer_len->type == JSON_VALUE_INTEGER )
			buffer_len = p_buffer_len->integer;
		// Default
		else
			goto wrong_buffer_len_type;

		// Construct a text input
		if ( construct_text_input(pp_text_input, placeholder, text, x, y, buffer_len) == 0 ) goto failed_to_construct_text_input;
	}

	// Success
	return 1;
		wrong_placeholder_type:
		wrong_text_type:
		wrong_x_type:
		wrong_y_type:
		wrong_buffer_len_type:
		failed_to_construct_text_input:

	// Error
	return 0;
}

int construct_text_input(ui_textinput** pp_text_input, char* placeholder, char* text, i32 x, i32 y, size_t buffer_len)
{

	// Argument check
	if ( pp_text_input == (void *) 0 ) goto no_text_input;

	// Initialized data
	ui_textinput *p_text_input = 0;

	// Allocate a text input
	if ( create_text_input(&p_text_input) == 0 ) goto failed_to_create_text_input;

	// Set the width and the height
	p_text_input->width = 8;
	p_text_input->height = 15;

	{

		{
			size_t placeholder_len = strlen(placeholder);
			p_text_input->placeholder = calloc(placeholder_len + 1, sizeof(char));
			strncpy(p_text_input->placeholder, placeholder, placeholder_len);

			p_text_input->width = (1 + placeholder_len) * 8;
		}

		p_text_input->text = calloc(buffer_len + 1, sizeof(char));


		if(text) {
			size_t text_len = strlen(text);
			strncpy(p_text_input->text, text, (text_len > buffer_len) ? buffer_len : text_len );
		}

		p_text_input->x = x;
		p_text_input->y = y;

	}

	// Return a pointer to the caller
	*pp_text_input = p_text_input;

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_text_input:
				#ifndef NDEBUG
					// TODO: 
				#endif

				// Error
				return 0;
		}

		// UI errors
		{
			failed_to_create_text_input:	
				#ifndef NDEBUG
					// TODO: 
				#endif

				// Error
				return 0;
		}
	}
}

int hover_text_input(ui_textinput* text_input, ui_mouse_state mouse_state)
{
	
	// TODO: Argument check
	//

	// Iterate through callbacks
    for (size_t i = 0; i < text_input->on_hover_count; i++)
    {

        // Initialized data
        void (*callback)(ui_textinput*, ui_mouse_state) = text_input->on_hover[i];

        // Call the callback function
        if ( callback )
			(*callback)(text_input, mouse_state);

    }

	// Success
	return 1;
}

int click_text_input(ui_textinput* text_input, ui_mouse_state mouse_state)
{

	// TODO:

	// Error
	return 0;
}

int release_text_input(ui_textinput* text_input, ui_mouse_state mouse_state)
{

	// TODO:

	// Error
	return 0;
}

int add_click_callback_text_input(ui_textinput* text_input, void(*callback)(ui_textinput*, ui_mouse_state))
{
	
	// TODO: 

	// Error
	return 0;
}

int add_hover_callback_text_input(ui_textinput* text_input, void(*callback)(ui_textinput*, ui_mouse_state))
{

	// TODO: Argument check
	//

    // If this is the first callback, set the max to 1 and 
    if ( text_input->on_hover_max == 0 )
    {
		text_input->on_hover_max = 1;
		text_input->on_hover = calloc(1, sizeof(void*));
    }

    // Simple heuristic that doubles callbacks lists length when there is no space to store the callback pointer
    if (text_input->on_hover_count + 1 > text_input->on_hover_max)
    {
        // Double the max
		text_input->on_hover_max *= 2;

        realloc(text_input->on_hover, text_input->on_hover_max);
    }

    // Increment the callback counter and install the new callback
	text_input->on_hover[text_input->on_hover_count++] = callback;

	// Success
    return 1;

    // TODO: Error handling
}

int add_release_callback_text_input(ui_textinput* text_input, void(*callback)(ui_textinput*, ui_mouse_state))
{

	// TODO:

	// Error
	return 0;
}

int draw_text_input(ui_window* window, ui_textinput* text_input)
{
	// Argument check
	if ( window     == (void *) 0 ) goto no_window;
	if ( text_input == (void *) 0 ) goto no_text_input;

	// Initialized data
	ui_instance *instance = ui_get_active_instance();
	SDL_Renderer *renderer = window->renderer;

	// Set the renderer color
    SDL_SetRenderDrawColor(window->renderer, (u8)instance->accent_2, (u8)(instance->accent_2 >> 8), (u8)(instance->accent_2 >> 16), 0xff);

	// Draw the text input
	{
		if (instance->active_window->last)
		{
			if (instance->active_window->last->text_input == text_input)
			{
				SDL_SetRenderDrawColor(window->renderer, (u8)instance->accent_3, (u8)(instance->accent_3 >> 8), (u8)(instance->accent_3 >> 16), 0xff);
			}
		}
		else
		{
			SDL_SetRenderDrawColor(window->renderer, (u8)instance->primary, (u8)(instance->primary >> 8), (u8)(instance->primary >> 16), 0xff);

		}

		SDL_Rect r = { text_input->x, text_input->y, text_input->width, text_input->height };
		SDL_RenderDrawRect(renderer, &r);
		++r.x,
		++r.y,
		r.w-=2,
		r.h-=2;
		SDL_RenderDrawRect(renderer, &r);
		SDL_SetRenderDrawColor(window->renderer, (u8)instance->primary, (u8)(instance->primary >> 8), (u8)(instance->primary >> 16), 0xff);

	}

	// Draw the text
	{
		if (text_input)
		{
			if (strlen(text_input->text))
			{
				ui_draw_text(text_input->text, window, text_input->x + 4, text_input->y + 3, 1);
			}
			else
			{
				if (text_input->placeholder)
				{
					text_input->width = (1 + strlen(text_input->placeholder)) * 8;

					SDL_SetRenderDrawColor(window->renderer, (u8)instance->accent_2, (u8)(instance->accent_2 >> 8), (u8)(instance->accent_2 >> 16), 0xff);
					ui_draw_text(text_input->placeholder, window, text_input->x + 4, text_input->y + 3, 1);

				}
			}

		}
	}

	// Success
	return 1;

	// Error handling
	{
		no_window:
		no_text_input:
			return 0;
	}
}

int  set_text_input_text ( ui_textinput *p_text_input, char *text )
{

	// TODO: Argument check
	//

	// Initialized data
	size_t len = strlen(text);

	if(len > p_text_input->max_chars)
	{
		p_text_input->text = realloc(p_text_input->text, len+1);
		p_text_input->max_chars = len;
	}

	// Copy the text into the text input
	strncpy(p_text_input->text, text, len+1);

	// Compute and store the new width
	p_text_input->width = 8 + (8 * len);

	// Success
	return 1;

	// TODO: Error handling
}

bool text_input_in_bounds(ui_textinput* text_input, ui_mouse_state mouse_state)
{

	// TODO: Argument check
	//

	// Initialized data
	i32  x = text_input->x,
		 y = text_input->y,
		 w = text_input->width,
		 h = text_input->height;
	
	// Check for bounds
	if (mouse_state.x >= x && mouse_state.y >= y && mouse_state.x <= x + w && mouse_state.y <= y + h)

		// In bounds
		return true;

	// Out of bounds
	return false;
}

int destroy_text_input(ui_textinput* text_input)
{

	// TODO: 

	// Error
	return 0;
}
