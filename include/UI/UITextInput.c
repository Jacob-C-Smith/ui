#include <UI/UITextInput.h>

UITextInput_t* create_text_input(void)
{
	UITextInput_t *ret = calloc(1,sizeof(UITextInput_t));

	// Error checking
	{
		#ifndef NDEBUG
			if(ret == (void *)0)
				goto no_mem;
		#endif 
	}

	return ret;

	// Error handling
	{

		// Standard library errors
		{
			no_mem:
				#ifndef NDEBUG
					ui_print_error("[UI] [Text Input] Failed to allocate memory in call to function \"%s\"\n", __FUNCSIG__);
				#endif
				return 0;
		}
	}
}

UITextInput_t* load_text_input_as_json_tokens(JSONToken_t* tokens, size_t token_count)
{
    
    // Argument check
    {
        #ifndef NDEBUG
            if(tokens == (void*)0)
                goto no_tokens;
            if (token_count == 0)
                goto no_token_count;
        #endif
    }
    size_t         j;

	UITextInput_t *ret         = 0;
	char          *x           = 0,
		          *y           = 0,
		          *placeholder = 0,
		          *text        = 0,
		          *max_chars   = 0;




    // Search through values and pull out relevent information
    for (j = 0; j < token_count; j++)
    {

        // Handle comments
        if      (strcmp("type", tokens[j].key) == 0)
        {

            // Type check
            if (tokens[j].type == JSONstring)
            {
                if (strcmp(tokens[j].value.n_where, "TEXT INPUT") != 0)
                    goto notATextInput;
            }
            else
                goto type_type_error;

            continue;
        }
        
        // button label
        else if (strcmp("text", tokens[j].key) == 0)
        {

            // Type check
            if (tokens[j].type == JSONstring)
                text = tokens[j].value.n_where;
            else
                goto text_type_error;
            continue;
        }

        // x position
        else if (strcmp("x", tokens[j].key) == 0)
        {

            // Type check
            if (tokens[j].type == JSONprimative)
                x = tokens[j].value.n_where;
            else
                goto x_type_error;

            continue;
        }
        
        // y position
        else if (strcmp("y", tokens[j].key) == 0)
        {

            // Type check
            if (tokens[j].type == JSONprimative)
                y = tokens[j].value.n_where;
            else
                goto y_type_error;

            continue;
        }

        // placeholder
        else if (strcmp("placeholder", tokens[j].key) == 0)
        {

            // Type check
            if (tokens[j].type == JSONstring)
                placeholder = tokens[j].value.n_where;
            else
                goto placeholder_type_error;

            continue;
        }

        else if (strcmp("char limit", tokens[j].key) == 0)
        {

            // Type check
            if (tokens[j].type == JSONprimative)
                max_chars = tokens[j].value.n_where;
            else
                goto char_lim_type_error;

            continue;
        }


        // unknown token
        else
            ui_print_warning("[UI] [Text Input] Unknown token encountered when parsing button, token %d/%d\n", j + 1, token_count);
    }

    // Check for important data
    {
        #ifndef NDEBUG
            if (text == 0)
                goto no_text;
            if (x == 0)
                goto no_x;
            if (y == 0)
                goto no_y;
        #endif  
    }

    // Construct the button
    ret = construct_text_input(placeholder, text, atoi(x), atoi(y), atoi(max_chars));

    return ret;

    // Error handling
    {
        notATextInput:
            ui_print_error("[UI] [Text Input] NOT A TEXT INPUT\n");
            return 0;
        
        // Standard library errors
        {
            out_of_memory:
                ui_print_error("[Standard library] Out of memory in call to function \"%s\"\n");
                return 0;
        }

        // Argument errors
        {
            no_tokens:
                ui_print_error("[UI] [Text Input] Null pointer provided for \"tokens\" in call to function \"%s\"\n", __FUNCSIG__);
                return 0;

            no_token_count:
                ui_print_error("[UI] [Text Input] \"token_count\" is zero in call to function \"%s\"\n", __FUNCSIG__);
                return 0;
        }

        // JSON type errors
        {
            type_type_error:
                ui_print_error("[UI] [Text Input] \"type\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONstring], __FUNCSIG__);
                return 0;
            text_type_error:
                ui_print_error("[UI] [Text Input] \"text\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONstring], __FUNCSIG__);
                return 0;
            x_type_error:
                ui_print_error("[UI] [Text Input] \"x\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONprimative], __FUNCSIG__);
                return 0;
            y_type_error:
                ui_print_error("[UI] [Text Input] \"y\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONprimative], __FUNCSIG__);
                return 0;
            char_lim_type_error:
            placeholder_type_error:

                return 0;
        }

        // Missing JSON errors
        {
            no_name:
                ui_print_error("[UI] [Text Input] No \"name\" in \"token\" in call to function \"%s\"\n", __FUNCSIG__);
                return 0;
            no_text:
                ui_print_error("[UI] [Text Input] No \"text\" in \"token\" in call to function \"%s\"\n", __FUNCSIG__);
                return 0;
            no_x:
                ui_print_error("[UI] [Text Input] No \"x\" in \"token\" in call to function \"%s\"\n", __FUNCSIG__);
                return 0;
            no_y:
                ui_print_error("[UI] [Text Input] No \"y\" in \"token\" in call to function \"%s\"\n", __FUNCSIG__);
                return 0;
        }
    }

	return ret;
}

UITextInput_t* construct_text_input(char* placeholder, char* text, i32 x, i32 y, size_t buffer_len)
{
	UITextInput_t *ret = create_text_input();

	// Construct the text input
	{
		ret->placeholder = placeholder,
		ret->text        = calloc(buffer_len, sizeof(u8)),
		ret->x           = x,
		ret->y           = y;
		ret->width       = 16,
		ret->height      = 16;
		ret->max_chars   = buffer_len;
	}

	return ret;
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

	SDL_Renderer *renderer = window->renderer;

	// Draw the text input
	{
		SDL_Rect r = { text_input->x, text_input->y, text_input->width, text_input->height };
		SDL_SetRenderDrawColor(renderer, 0xc0, 0xc0, 0xc0, 0xff);
		SDL_RenderDrawRect(renderer, &r);
		++r.x,
		++r.y,
		r.w-=2,
		r.h-=2;
		SDL_RenderDrawRect(renderer, &r);
	}

	// Draw the text
	{
		if (text_input)
		{
			if (strlen(text_input->text))
			{
				ui_draw_text(text_input->text, window, text_input->x+4, text_input->y+3,1);
			}
			else
			{

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
}

int click_text_input(UITextInput_t* text_input, mouse_state_t mouse_state)
{
	UIInstance_t *instance = ui_get_active_instance();

	return 0;
}

void destroy_text_input(UITextInput_t* text_input)
{

}
