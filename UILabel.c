#include <UI/UILabel.h>

UILabel_t* create_label     ( void )
{
	// Initialized data
	UILabel_t *ret = calloc(1, sizeof(UILabel_t));
	
	// Check allocated memory, if in debug mode
	{
		#ifndef NDEBUG
		if (ret == (void*)0)
			goto noMem;
		#endif
	}
	
	// Return a pointer to the start of the struct
	return (UIButton_t *) ret;

	// Error handling
	{
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

UILabel_t* load_label       ( const char  path [ ] )
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

UILabel_t* load_label_as_json_tokens (JSONToken_t* tokens, size_t token_count)
{
	// TODO: Argument check

	UILabel_t *ret  = create_label();

	char      *text = 0,
		      *x    = 0,
		      *y    = 0;

    // Search through values and pull out relevent information
    for (size_t j = 0; j < token_count; j++)
    {

        // Handle comments
		if (strcmp("type", tokens[j].key) == 0)
		{
			if (tokens[j].type == JSONstring)
				if (strcmp(tokens[j].value.n_where, "LABEL") != 0)
					goto notALabel;
		}
		else if (strcmp("text", tokens[j].key) == 0)
		{
			if (tokens[j].type == JSONstring)
				text = tokens[j].value.n_where;

		}
		else if ( strcmp("x", tokens[j].key) == 0 )
		{
			if (tokens[j].type == JSONprimative)
				x = tokens[j].value.n_where;
			else
				goto x_type_error;
		}
		else if (strcmp("y", tokens[j].key) == 0)
		{
			if (tokens[j].type == JSONprimative)
				y = tokens[j].value.n_where;
			else
				goto y_type_error;
		}
		else if (strcmp("name", tokens[j].key) == 0)
			continue;
		else if (strcmp("hidden", tokens[j].key) == 0)
			continue;// TODO
		else
			ui_print_warning("[UI] [Label] Unknown token encountered when parsing label, token %d/%d\n", j+1, token_count);
    }

	ret = construct_label(text, atoi(x), atoi(y));

	return ret;

	// TODO: Error handling
	notALabel:
		ui_print_error("[UI] [Label] NOT A LABEL!\n");
		no_mem:
		x_type_error:
		y_type_error:
		return 0;
}

UILabel_t* construct_label(char* text, i32 x, i32 y)
{
	// Argument check
	{
		#ifndef NDEBUG
			if(text == (void *)0)
				goto no_text;
		#endif
	}

	UILabel_t *ret = create_label();

	// Construct the label
	{
		// Set the name
		{
			size_t len = strlen(text);
			ret->text  = calloc(len+1, sizeof(u8));

			// Error checking
			{
				#ifndef NDEBUG
					if(ret->text == (void *)0)
						goto no_mem;
				#endif
			}
			
			// Copy the string
			strncpy(ret->text, text, len);
		}

		// Set the position
		ret->x = x,
		ret->y = y;
	}

	return ret;

	// Error handling
	{
		
		// Argument errors
		{
			no_text:
				return 0;
		}

		// Standard library
		{
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
		ui_draw_text(label->text, window, label->x, label->y, 1);
	}
	label->width  = strlen(label->text) * 8;
	label->height = 8;

	return 0;

	// TODO: Error handling
}

int        click_label      ( UILabel_t* label, mouse_state_t mouse_state)
{

	// Iterate through callbacks
	for (size_t i = 0; i < label->on_click_count; i++)
	{
		// Define the callback function
		void (*callback)(UILabel_t*, mouse_state_t) = label->on_click[i];

		// Call the callback function
		(*callback)(label, mouse_state);

	}

	return 0;
}

void       destroy_label    ( UILabel_t  *label )
{
	free(label->text);
	free(label);
}
