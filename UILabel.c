#include <UI/UILabel.h>

int create_label ( UILabel_t **pp_label )
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
	if ( p_label == (void *) 0 )
		goto no_mem;
	
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
					ui_print_error("[UI] [Label] Null pointer provided for \"pp_label\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error 
				return 0;
		}

		// Standard Library errors
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
	UIInstance_t *p_instance = ui_get_active_instance();
	UILabel_t    *p_label    = 0;
	JSONValue_t  *p_text     = 0,
	             *p_x        = 0,
		         *p_y        = 0,
		         *p_size     = 0,
	             *p_color    = 0;

	// Get properties from the dictionary
    if (p_value->type == JSONobject)
    {

		// Initialized data
		dict *p_dict = p_value->object;

        p_text  = dict_get(p_dict, "text");
        p_x     = dict_get(p_dict, "x");
		p_y     = dict_get(p_dict, "y");
		p_size  = dict_get(p_dict, "size");
		p_color = dict_get(p_dict, "color");

    }

	// Error checking
	{
		#ifndef NDEBUG
			if( ! ( p_text && p_x && p_y && p_size ) )
				goto missing_properties;
		#endif
	}

	// Construct the label
	{

		// Allocate a label
		if ( create_label(&p_label) == 0)
			goto failed_to_allocate_label;

		// Copy the label text
		if ( p_text->type == JSONstring )
		{

			// Initialized data
			size_t label_text_len = strlen(p_text->string);

			// Allocate memory for the label text
			p_label->text = calloc(label_text_len+1, sizeof(char));

			// Error check
			if ( p_label->text == (void *) 0 )
				goto no_mem;

			// Copy the string
			strncpy(p_label->text, p_text->string, label_text_len);
		}

		// Set the label color
		if ( p_color )
		{

			// Initialized data
			JSONValue_t *p_colors[3] = { 0, 0, 0 };
			size_t       len = 0;
			size_t       p_bytes[3] = { 0, 0, 0 };

			array_get(p_color->list, 0, &len);

			if ( len != 3 )
				goto wrong_color_length;
			
			array_get(p_color->list, &p_colors, 0);

			for (size_t i = 0; i < 3; i++)
				p_bytes[i] = p_colors[i]->integer;
			
			color c = 0;
			c |= p_bytes[0];
			c |= p_bytes[1] << 8;
			c |= p_bytes[2] << 16;

			p_label->c = c;
		}
		else
			p_label->c = p_instance->primary;

		// Set the x
		if ( p_x->type == JSONinteger)
			p_label->x = p_x->integer;
		// Default
		else
			goto wrong_x_type;

		// Set the y
		if ( p_y->type == JSONinteger)
			p_label->y = p_y->integer;
		// Default
		else
			goto wrong_y_type;

		// Set the size
		if ( p_size->type == JSONinteger)
			p_label->size = p_size->integer;
		// Default
		else
			goto wrong_size_type;
	}

	// Return
	*pp_label = p_label;

	// Success
	return 1;

	wrong_color_length:
	wrong_x_type:
	wrong_y_type:
	wrong_size_type:
	no_mem:
		return 0;

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
			missing_properties:
			no_x:
			no_y:
				return 0;
		}
	}
}

int draw_label ( UIWindow_t *p_window, UILabel_t* p_label )
{

	// Argument check
	{
		#ifndef NDEBUG
			if ( p_window == (void *) 0 )
				goto no_window;
			if ( p_label == (void *) 0 )
				goto no_label;
		#endif
	}

	// Initialized data
	UIInstance_t *p_instance = ui_get_active_instance();

	// Don't draw a hidden label
	if (p_label->hidden == false)
	{

		// Set the draw color
		SDL_SetRenderDrawColor(p_window->renderer, (u8)p_label->c, (u8)(p_label->c >> 8), (u8)(p_label->c >> 16), 0xff);

		// Draw the label text
		ui_draw_text(p_label->text, p_window, p_label->x, p_label->y, p_label->size);
	}

	// Update the width and the height
	p_label->width  = strlen(p_label->text) * 8 * p_label->size;
	p_label->height = 8 * p_label->size;

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_window:
				#ifndef NDEBUG
					ui_print_error("[UI] [Label] Null pointer provided for parameter \"p_window\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
			no_label:
				#ifndef NDEBUG
					ui_print_error("[UI] [Label] Null pointer provided for parameter \"p_label\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}

int click_label ( UILabel_t* p_label, ui_mouse_state_t mouse_state)
{

	// Argument check
	{
		#ifndef NDEBUG
			if ( p_label == (void *) 0 )
				goto no_label;
		#endif
	}

	// Iterate through callbacks
	for (size_t i = 0; i < p_label->on_click_count; i++)
	{
		// Define the callback function
		void (*callback)(UILabel_t*, ui_mouse_state_t) = p_label->on_click[i];

		// Call the callback function
		(*callback)(p_label, mouse_state);

	}

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_label:
				#ifndef NDEBUG
					ui_print_error("[UI] [Label] Null pointer provided for parameter \"p_label\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}

int hover_label ( UILabel_t* p_label, ui_mouse_state_t mouse_state)
{
	
	// Argument check
	{
		#ifndef NDEBUG
			if ( p_label == (void *) 0 )
				goto no_label;
		#endif
	}
	
	// Iterate through callbacks
	for (size_t i = 0; i < p_label->on_hover_count; i++)
	{

		// Define the callback function
		void (*callback)(UILabel_t*, ui_mouse_state_t) = p_label->on_hover[i];

		// Call the callback function
		if (callback)
			(*callback)(p_label, mouse_state);

	}

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_label:
				#ifndef NDEBUG
					ui_print_error("[UI] [Label] Null pointer provided for parameter \"p_label\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}

int release_label ( UILabel_t* p_label, ui_mouse_state_t mouse_state)
{

	// Argument check
	{
		#ifndef NDEBUG
			if ( p_label == (void *) 0 )
				goto no_label;
		#endif
	}

	// Iterate through callbacks
	for (size_t i = 0; i < p_label->on_release_count; i++)
	{
		// Define the callback function
		void (*callback)(UILabel_t*, ui_mouse_state_t) = p_label->on_release[i];


		// Call the callback function
		if (callback)
			(*callback)(p_label, mouse_state);

	}

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_label:
				#ifndef NDEBUG
					ui_print_error("[UI] [Label] Null pointer provided for parameter \"p_label\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}

int add_click_callback_label ( UILabel_t* p_label, void(*callback)(UILabel_t*, ui_mouse_state_t))
{

    // Argument check
	{
		#ifndef NDEBUG
			if ( p_label == (void *) 0 )
				goto no_label;
		#endif
	}

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
		
		if (p_label->on_click == (void *)0)
			goto no_mem;
    }

    // Increment the callback counter and install the new callback
	p_label->on_click[p_label->on_click_count++] = callback;

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_label:
				#ifndef NDEBUG
					ui_print_error("[UI] [Label] Null pointer provided for parameter \"p_label\" in call to function \"%s\"\n", __FUNCTION__);
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

int add_hover_callback_label ( UILabel_t* p_label, void(*callback)(UILabel_t*, ui_mouse_state_t))
{

	// Argument check
	{
		#ifndef NDEBUG
			if ( p_label == (void *) 0 )
				goto no_label;
		#endif
	}

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_label:
				#ifndef NDEBUG
					ui_print_error("[UI] [Label] Null pointer provided for parameter \"p_label\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}

int add_release_callback_label ( UILabel_t* p_label, void(*callback)(UILabel_t*, ui_mouse_state_t))
{
	
	// Argument check
	{
		#ifndef NDEBUG
			if ( p_label == (void *) 0 )
				goto no_label;
		#endif
	}

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_label:
				#ifndef NDEBUG
					ui_print_error("[UI] [Label] Null pointer provided for parameter \"p_label\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}

bool label_in_bounds ( UILabel_t  *p_label, ui_mouse_state_t mouse_state)
{

	// Argument check
	{
		#ifndef NDEBUG
			if ( p_label == (void *) 0 )
				goto no_label;
		#endif
	}

	// Initialized data
	i32  x = p_label->x,
		 y = p_label->y,
		 w = p_label->width,
		 h = p_label->height;
	
	// Check for intersection
	if (mouse_state.x >= x && mouse_state.y >= y && mouse_state.x <= x + w && mouse_state.y <= y + h)

		// Intersect
		return true;

	// No intersect
	return false;

	// Error handling
	{

		// Argument errors
		{
			no_label:
				#ifndef NDEBUG
					ui_print_error("[UI] [Label] Null pointer provided for parameter \"p_label\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}

int  print_label_to_file ( UILabel_t *p_label, FILE *f, char *name )
{
	JSONValue_t *p_value = calloc(1, sizeof(JSONValue_t));
	
	p_value->type = JSONobject;
	dict_construct(&p_value->object,5);

	{

		// Initialized data
		JSONValue_t *p_type = calloc(1, sizeof(JSONValue_t)),
		            *p_name = calloc(1, sizeof(JSONValue_t)),
		            *p_text = calloc(1, sizeof(JSONValue_t)),
		            *p_x    = calloc(1, sizeof(JSONValue_t)),
		            *p_y    = calloc(1, sizeof(JSONValue_t)),
		            *p_size = calloc(1, sizeof(JSONValue_t));

		{

			p_type->type = JSONstring;
			p_type->string = "LABEL";
			
			p_name->type = JSONstring;
			p_name->string = name;

			p_text->type = JSONstring;
			p_text->string = p_text;

			p_x->type = JSONstring;
			p_x->string = p_text;

			p_y->type = JSONstring;
			p_y->string = p_text;

			p_size->type = JSONstring;
			p_size->string = p_text;

			dict_add(p_value->object, "type", p_type);
			dict_add(p_value->object, "name", p_name);
			dict_add(p_value->object, "text", p_text);
			dict_add(p_value->object, "x", p_x);
			dict_add(p_value->object, "y", p_y);
			dict_add(p_value->object, "size", p_size);
		}

		print_json_value(p_value, f);

	}
}

int destroy_label ( UILabel_t  **pp_label )
{

	// Argument check
	{
		#ifndef NDEBUG
			if ( pp_label == (void *) 0 )
				goto no_label;
		#endif
	}

	// Initialized data
	UILabel_t *p_label = pp_label;

	// Free the label text and the callbacks
	free(p_label->text);
	free(p_label->on_click);
	free(p_label->on_hover);
	free(p_label->on_release);

	// Free the label
	free(p_label);
	
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_label:
				#ifndef NDEBUG
					ui_print_error("[UI] [Label] Null pointer provided for parameter \"pp_label\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}
