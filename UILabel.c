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

	UILabel_t *ret = create_label();

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
			char   *label_text     = tokens[j].value.n_where;
			size_t  label_text_len = strlen(label_text);

			ret->text              = calloc(label_text_len+1, sizeof(u8));

			// TODO: Check allocated memory

			strncpy(ret->text, label_text, label_text_len);
        }
		else if ( strcmp("name", tokens[j].key) == 0)
			continue;
		else if ( strcmp("x", tokens[j].key) == 0 )
		{
			if ( tokens[j].type == JSONprimative )
				ret->x = atoi(tokens[j].value.n_where);
		}
		else if (strcmp("y", tokens[j].key) == 0)
		{
			if ( tokens[j].type == JSONprimative )
				ret->y = atoi(tokens[j].value.n_where);
		}
		else if (strcmp("hidden", tokens[j].key) == 0)
			;// TODO
		else
			ui_print_warning("[UI] [Label] Unknown token encountered when parsing label, token %d/%d\n", j+1, token_count);
    }

	return ret;

	// TODO: Error handling
	notALabel:
		ui_print_error("[UI] [Label] NOT A LABEL!\n");
		return 0;
}

int        draw_label       ( UIWindow_t *window, UILabel_t* label )
{
	// TODO: Argument checks
	if(label->hidden == false) 
		SDL_SetRenderDrawColor(window->renderer, 0x00, 0x00, 0x00, 0xff);
		ui_draw_text(label->text, window, label->x, label->y, 1);

	label->width  = strlen(label->text) * 8;
	label->height = 8;

	return 0;

	// TODO: Error handling
}

int click_label(UILabel_t* label, mouse_state_t mouse_state)
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
