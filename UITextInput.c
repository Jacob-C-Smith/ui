#include <UI/UITextInput.h>

int create_text_input(UITextInput_t** pp_text_input)
{
	UITextInput_t** p_text_input = 0;

	p_text_input = calloc(1, sizeof(UITextInput_t));

	*pp_text_input = p_text_input;

	return 0;
}

int load_text_input_as_dict(UITextInput_t** pp_text_input, dict* dictionary)
{
	char *placeholder = 0,
		 *text        = 0,
		 *x           = 0,
		 *y           = 0,
		 *width       = 0,
		 *height      = 0,
		 *buffer_len  = 0;

	// Parse JSON
	{
		JSONToken_t *token = 0;

		token = dict_get(dictionary, "placeholder");
		placeholder = JSON_VALUE(token, JSONstring);

		token = dict_get(dictionary, "text");
		text = JSON_VALUE(token, JSONstring);

		token = dict_get(dictionary, "x");
		x = JSON_VALUE(token, JSONprimative);

		token = dict_get(dictionary, "y");
		y = JSON_VALUE(token, JSONprimative);

		token = dict_get(dictionary, "length");
		buffer_len = JSON_VALUE(token, JSONprimative);

	}

	construct_text_input(pp_text_input, placeholder, text, atoi(x), atoi(y), atoi(buffer_len));

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

	// Draw the text input
	{
		if (instance->active_window->last)
		{
			if (instance->active_window->last->element.text_input == text_input)
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

bool text_input_in_bounds(UITextInput_t* text_input, ui_mouse_state_t mouse_state)
{
	i32  x = text_input->x,
		 y = text_input->y,
		 w = text_input->width,
		 h = text_input->height;
	
	// Check for bounds
	if (mouse_state.x >= x && mouse_state.y >= y && mouse_state.x <= x + w && mouse_state.y <= y + h)
		return true;

	return false;}

int destroy_text_input(UITextInput_t* text_input)
{
	return 0;
}
