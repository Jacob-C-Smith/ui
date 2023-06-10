#include <UI/UITextInput.h>

int create_text_input(UITextInput_t** pp_text_input)
{
	UITextInput_t** p_text_input = 0;

	p_text_input = calloc(1, sizeof(UITextInput_t));

	*pp_text_input = p_text_input;

	return 0;
}

int load_text_input_as_json_value ( UITextInput_t **pp_text_input, JSONValue_t *p_value )
{
	JSONValue_t *p_placeholder = 0,
		        *p_text        = 0,
		        *p_x           = 0,
		        *p_y           = 0,
		        *p_buffer_len  = 0;

	// Parse JSON
	{

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
		if ( p_placeholder->type == JSONstring )
			placeholder = p_placeholder->string;
		// Default
		else
			goto wrong_placeholder_type;
		
		// Set the text
		if ( p_text )
		{
			if ( p_text->type == JSONstring )
				text = p_text->string;
			// Default
			else
				goto wrong_text_type;
		}
		// Set the x
		if ( p_x->type == JSONinteger )
			x = p_x->integer;
		// Default
		else
			goto wrong_x_type;

		// Set the y
		if ( p_y->type == JSONinteger )
			y = p_y->integer;
		// Default
		else
			goto wrong_y_type;

		// Set the buffer length
		if ( p_buffer_len->type == JSONinteger )
			buffer_len = p_buffer_len->integer;
		// Default
		else
			goto wrong_buffer_len_type;

		if ( construct_text_input(pp_text_input, placeholder, text, x, y, buffer_len) == 0 ) 
			goto failed_to_construct_text_input;
	}

	return 1;
wrong_placeholder_type:
wrong_text_type:
wrong_x_type:
wrong_y_type:
wrong_buffer_len_type:
failed_to_construct_text_input:
	return 0;
}

int construct_text_input(UITextInput_t** pp_text_input, char* placeholder, char* text, i32 x, i32 y, size_t buffer_len)
{
	UITextInput_t *p_text_input = 0;

	create_text_input(pp_text_input);
	p_text_input = *pp_text_input;

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

	return 0;
}

int hover_text_input(UITextInput_t* text_input, ui_mouse_state_t mouse_state)
{
	// Iterate through callbacks
    for (size_t i = 0; i < text_input->on_hover_count; i++)
    {
        // Define the callback function
        void (*callback)(UITextInput_t*, ui_mouse_state_t) = text_input->on_hover[i];

        // Call the callback function
        (*callback)(text_input, mouse_state);

    }

}

int click_text_input(UITextInput_t* text_input, ui_mouse_state_t mouse_state)
{

	return 0;
}

int release_text_input(UITextInput_t* text_input, ui_mouse_state_t mouse_state)
{
	return 0;
}

int add_click_callback_text_input(UITextInput_t* text_input, void(*callback)(UITextInput_t*, ui_mouse_state_t))
{
	return 0;
}

int add_hover_callback_text_input(UITextInput_t* text_input, void(*callback)(UITextInput_t*, ui_mouse_state_t))
{
	// TODO: Argument check

    // If this is the first callback, set the max to 1 and 
    if (text_input->on_hover_max == 0)
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

    return 0;

    // TODO: Error handling
}

int add_release_callback_text_input(UITextInput_t* text_input, void(*callback)(UITextInput_t*, ui_mouse_state_t))
{
	return 0;
}

int draw_text_input(UIWindow_t* window, UITextInput_t* text_input)
{
	// Argument check
	{
		#ifndef NDEBUG
			if(window == (void *)0)
				goto no_window;
			if(text_input == (void *)0)
				goto no_text_input;
		#endif
	}

	UIInstance_t *instance = ui_get_active_instance();
	SDL_Renderer *renderer = window->renderer;
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

	return 0;

	// Error handling
	{
		no_window:
		no_text_input:
			return 0;
	}

	return 0;
}

int  set_text_input_text ( UITextInput_t *p_text_input, char *text )
{
	size_t len = strlen(text);

	if(len > p_text_input->max_chars)
	{
		p_text_input->text = realloc(p_text_input->text, len+1);
		p_text_input->max_chars = len;
	}

	strncpy(p_text_input->text, text, len+1);


	p_text_input->width = 8 + (8 * len);

	return 1;
}

bool text_input_in_bounds(UITextInput_t* text_input, ui_mouse_state_t mouse_state)
{
	i32  x = text_input->x,
		 y = text_input->y,
		 w = text_input->width,
		 h = text_input->height;
	
	// Check for bounds
	if (mouse_state.x >= x && mouse_state.y >= y && mouse_state.x <= x + w && mouse_state.y <= y + h)
		return true;

	return false;
}

int destroy_text_input(UITextInput_t* text_input)
{
	return 0;
}
