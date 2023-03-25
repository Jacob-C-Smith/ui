#include <UI/UILabel.h>

int create_label     ( UILabel_t **pp_label )
{

	// Argument check
	{
		#ifndef NDEBUG
			if(pp_label == (void *)0)
				goto no_label;
		#endif
	}

	// Initialized data
	UILabel_t *p_label = calloc(1, sizeof(UILabel_t));
	
	// Error checking
	{
		#ifndef NDEBUG
			if (p_label == (void*)0)
				goto no_mem;
		#endif
	}
	
	// Return
	*pp_label = p_label;

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_label:
				#ifndef NDEBUG
					ui_print_error("[UI] [Label] Null pointer provided for \"label\" in call to function \"%s\"\n", __FUNCTION__);
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

int load_label_as_json_value (UILabel_t** pp_label, JSONValue_t *p_value)
{

	// Argument check
	{
		#ifndef NDEBUG
			if(pp_label == (void *)0)
				goto no_label;
			if (p_value == (void*)0)
				goto no_value;
		#endif
	}

	// Initialized data
	UILabel_t *p_label = 0;
	char      *text    = 0;
	signed     x       = 0,
		       y       = 0,
		       size    = 0;

	// Get properties from the dictionary
    if (p_value->type == JSONobject)
    {

        // Initialized data
        dict *p_dict = p_value->object;

        text = JSON_VALUE(((JSONValue_t *)dict_get(p_dict, "text")), JSONstring);
        x    = JSON_VALUE(((JSONValue_t *)dict_get(p_dict, "x"))   , JSONinteger);
		y    = JSON_VALUE(((JSONValue_t *)dict_get(p_dict, "y"))   , JSONinteger);
		size = JSON_VALUE(((JSONValue_t *)dict_get(p_dict, "size")), JSONinteger);
    }

	// Error checking
	{
		#ifndef NDEBUG
			if(!(text && x && y && size))
				goto no_text;
		#endif
	}

	// Construct the label
	{

		// Allocate a label
		if ( create_label(&p_label) == 0)
			goto failed_to_allocate_label;

		// Copy the label text
		{

			// Initialized data
			size_t label_text_len = strlen(text);

			// Allocate memory for the label text
			p_label->text = calloc(label_text_len+1, sizeof(char));

			// TODO: Check memory

			// Copy the string
			strncpy(p_label->text, text, label_text_len);
		}

		// Set the label x, y, and size
		p_label->x    = x;
		p_label->y    = y;
		p_label->size = size;
	}

	*pp_label = p_label;

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_label:
				#ifndef NDEBUG
					ui_print_error("[UI] [Label] Null pointer provided for \"pp_label\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
			no_value:
				#ifndef NDEBUG
					ui_print_error("[UI] [Label] Null pointer provided for \"p_value\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}

		// TODO:
		failed_to_allocate_label:

		// Insufficent data error
		{
			// TODO: 
			no_text:
			no_x:
			no_y:
				return 0;
		}
	}
}

int        draw_label       ( UIWindow_t *p_window, UILabel_t* p_label )
{

	// TODO: Argument checks
	UIInstance_t *instance = ui_get_active_instance();

	if (p_label->hidden == false)
	{
		SDL_SetRenderDrawColor(p_window->renderer, (u8)instance->primary, (u8)(instance->primary >> 8), (u8)(instance->primary >> 16), 0xff);
		ui_draw_text(p_label->text, p_window, p_label->x, p_label->y, p_label->size);
	}
	p_label->width  = strlen(p_label->text) * 8 * p_label->size;
	p_label->height = 8 * p_label->size;

	return 1;

	// TODO: Error handling
}

int        click_label      ( UILabel_t* p_label, ui_mouse_state_t mouse_state)
{

	// Iterate through callbacks
	for (size_t i = 0; i < p_label->on_click_count; i++)
	{
		// Define the callback function
		void (*callback)(UILabel_t*, ui_mouse_state_t) = p_label->on_click[i];

		// Call the callback function
		(*callback)(p_label, mouse_state);

	}

	return 0;
}

int hover_label(UILabel_t* p_label, ui_mouse_state_t mouse_state)
{

	// Iterate through callbacks
	for (size_t i = 0; i < p_label->on_hover_count; i++)
	{

		// Define the callback function
		void (*callback)(UILabel_t*, ui_mouse_state_t) = p_label->on_hover[i];

		// Call the callback function
		if (callback)
			(*callback)(p_label, mouse_state);

	}

	return 1;
}

int release_label(UILabel_t* p_label, ui_mouse_state_t mouse_state)
{

	// Iterate through callbacks
	for (size_t i = 0; i < p_label->on_release_count; i++)
	{
		// Define the callback function
		void (*callback)(UILabel_t*, ui_mouse_state_t) = p_label->on_release[i];


		// Call the callback function
		if (callback)
			(*callback)(p_label, mouse_state);

	}
	return 0;
}

int add_click_callback_label(UILabel_t* p_label, void(*callback)(UILabel_t*, ui_mouse_state_t))
{
    // TODO: Argument check

    // If this is the first callback, set the max to 1 and 
    if (p_label->on_click_max == 0)
    {
		p_label->on_click_max = 1;
		p_label->on_click = calloc(1, sizeof(void*));
    }

    // Simple heuristic that doubles callbacks lists length when there is no space to store the callback pointer
    if (p_label->on_click_count + 1 > p_label->on_click_max)
    {
        // Double the max
		p_label->on_click_max *= 2;

        realloc(p_label->on_click, p_label->on_click_max);
    }

    // Increment the callback counter and install the new callback
	p_label->on_click[p_label->on_click_count++] = callback;

    return 0;

    // TODO: Error handling
}

int add_hover_callback_label(UILabel_t* p_label, void(*callback)(UILabel_t*, ui_mouse_state_t))
{
	// TODO
	return 0;
}

int add_release_callback_label(UILabel_t* p_label, void(*callback)(UILabel_t*, ui_mouse_state_t))
{
	// TODO
	return 0;
}

bool       label_in_bounds  ( UILabel_t  *p_label, ui_mouse_state_t mouse_state)
{

	// Initialized data
	i32  x = p_label->x,
		 y = p_label->y,
		 w = p_label->width,
		 h = p_label->height;
	
	// Check for bounds
	if (mouse_state.x >= x && mouse_state.y >= y && mouse_state.x <= x + w && mouse_state.y <= y + h)
		return true;

	return false;

}

void       destroy_label    ( UILabel_t  *label )
{
	free(label->text);
	free(label);
}
