#include <UI/UILabel.h>

int create_label     ( UILabel_t **label )
{
	// Argument check
	{
		#ifndef NDEBUG
			if(label == (void *)0)
				goto no_label;
		#endif
	}

	// Initialized data
	UILabel_t *i_label = calloc(1, sizeof(UILabel_t));
	
	// Error checking
	{
		#ifndef NDEBUG
		if (i_label == (void*)0)
			goto noMem;
		#endif
	}
	
	*label = i_label;

	// Return a pointer to the start of the struct
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_label:
				#ifndef NDEBUG
					ui_print_error("[UI] [Label] Null pointer provided for \"label\" in call to function \"%s\"\n", __FUNCSIG__);
				#endif
				return 0;
		}

		// Standard library errors
		{
			noMem:
			#ifndef NDEBUG
				ui_print_error("[UI] [Label] Failed to create a label; Out of memory\n");
			#endif
			return (void*)0;
		}
	}
}

int load_label       ( UILabel_t **label, const char  path [ ] )
{
	// Uninitialized data
    u8         *data;
	UILabel_t  *ret;

    // Initialized data
    size_t      i   = 0;

    // Load the file
    i    = ui_load_file(path, 0, false);
    data = calloc(i, sizeof(u8));
    ui_load_file(path, data, false);

	// Parse the JSON object
	ret = 0;// load_label_as_json(data);

    // Finish up
    free(data);

	// Return a pointer to the populated label
    return ret;

    // Error handling
    {
        invalidFile:
            #ifndef NDEBUG
                ui_print_error("[UI] [Label] Failed to load file %s\n", path);
            #endif
			return 0;
    }
}

int  load_label_as_dict (UILabel_t** label, dict* dictionary)
{

	// Argument check
	{
		#ifndef NDEBUG
			if(label == (void *)0)
				goto no_label;
			if (dictionary == (void*)0)
				goto no_dictionary;
		#endif
	}

	// Initialized data
	char      *text    = 0,
		      *x       = 0,
		      *y       = 0,
		      *size    = 0;

	
    // Get data for the constructor
	{
		
		JSONToken_t* token = 0;

		token  = dict_get(dictionary, "text");
		text   = JSON_VALUE(token, JSONstring);

		token  = dict_get(dictionary, "x");
		x      = JSON_VALUE(token, JSONprimative);

		token  = dict_get(dictionary, "y");
		y      = JSON_VALUE(token, JSONprimative);

		token = dict_get(dictionary, "size");
		size = JSON_VALUE(token, JSONprimative);

    }

	// Error checking
	{
		#ifndef NDEBUG
			if(text == (void *)0)
				goto no_text;
			if (x == (void*)0)
				goto no_x;
			if (y == (void*)0)
				goto no_y;
		#endif
	}

	construct_label(label, text, atoi(x), atoi(y), (size) ? atoi(size) : 1);

	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_label:
				#ifndef NDEBUG
					ui_print_error("[UI] [Label] Null pointer provided for \"label\" in call to function \"%s\"\n", __FUNCSIG__);
				#endif
				return 0;
			no_dictionary:
				#ifndef NDEBUG
					ui_print_error("[UI] [Label] Null pointer provided for \"dictionary\" in call to function \"%s\"\n", __FUNCSIG__);
				#endif
				return 0;
		}

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

int  construct_label( UILabel_t **label, char* text, i32 x, i32 y, i32 size)
{
	// Argument check
	{
		#ifndef NDEBUG
			if(text == (void *)0)
				goto no_text;
		#endif
	}

	// Initialized data
	UILabel_t *i_label = 0;

	// Allocate memory for a label
	create_label(label);

	// Get an internal reference to the label
	i_label = *label;

	// Construct the label
	{

		// Set the name
		{
			size_t len     = strlen(text);
			i_label->text  = calloc(len+1, sizeof(u8));

			// Error checking
			{
				#ifndef NDEBUG
					if(i_label->text == (void *)0)
						goto no_mem;
				#endif
			}
			
			// Copy the string
			strncpy(i_label->text, text, len);
		}

		// Set the position
		i_label->x = x,
		i_label->y = y;
		i_label->size = size;
	}

	return 1;

	// Error handling
	{
		
		// Argument errors
		{
			// TODO:
			no_text:
				return 0;
		}

		// Standard library
		{
			// TODO:
			no_mem:
				return 0;
		}
	}
}

int        draw_label       ( UIWindow_t *window, UILabel_t* label )
{

	// TODO: Argument checks
	UIInstance_t *instance = ui_get_active_instance();

	if (label->hidden == false)
	{
		SDL_SetRenderDrawColor(window->renderer, (u8)instance->primary, (u8)(instance->primary >> 8), (u8)(instance->primary >> 16), 0xff);
		ui_draw_text(label->text, window, label->x, label->y, label->size);
	}
	label->width  = strlen(label->text) * 8 * label->size;
	label->height = 8 * label->size;

	return 0;

	// TODO: Error handling
}

int        click_label      ( UILabel_t* label, ui_mouse_state_t mouse_state)
{

	// Iterate through callbacks
	for (size_t i = 0; i < label->on_click_count; i++)
	{
		// Define the callback function
		void (*callback)(UILabel_t*, ui_mouse_state_t) = label->on_click[i];

		// Call the callback function
		(*callback)(label, mouse_state);

	}

	return 0;
}

int hover_label(UILabel_t* label, ui_mouse_state_t mouse_state)
{

	// Iterate through callbacks
	for (size_t i = 0; i < label->on_hover_count; i++)
	{

		// Define the callback function
		void (*callback)(UILabel_t*, ui_mouse_state_t) = label->on_hover[i];

		// Call the callback function
		if (callback)
			(*callback)(label, mouse_state);

	}
}

int release_label(UILabel_t* label, ui_mouse_state_t mouse_state)
{

	// Iterate through callbacks
	for (size_t i = 0; i < label->on_release_count; i++)
	{
		// Define the callback function
		void (*callback)(UILabel_t*, ui_mouse_state_t) = label->on_release[i];


		// Call the callback function
		if (callback)
			(*callback)(label, mouse_state);

	}
	return 0;
}

int add_click_callback_label(UILabel_t* label, void(*callback)(UILabel_t*, ui_mouse_state_t))
{
    // TODO: Argument check

    // If this is the first callback, set the max to 1 and 
    if (label->on_click_max == 0)
    {
		label->on_click_max = 1;
		label->on_click = calloc(1, sizeof(void*));
    }

    // Simple heuristic that doubles callbacks lists length when there is no space to store the callback pointer
    if (label->on_click_count + 1 > label->on_click_max)
    {
        // Double the max
		label->on_click_max *= 2;

        realloc(label->on_click, label->on_click_max);
    }

    // Increment the callback counter and install the new callback
	label->on_click[label->on_click_count++] = callback;

    return 0;

    // TODO: Error handling
}

int add_hover_callback_label(UILabel_t* label, void(*callback)(UILabel_t*, ui_mouse_state_t))
{
	return 0;
}

int add_release_callback_label(UILabel_t* label, void(*callback)(UILabel_t*, ui_mouse_state_t))
{
	return 0;
}

bool       label_in_bounds  ( UILabel_t  *label, ui_mouse_state_t mouse_state)
{
	// Initialized data
	i32  x = label->x,
		 y = label->y,
		 w = label->width,
		 h = label->height;
	
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
