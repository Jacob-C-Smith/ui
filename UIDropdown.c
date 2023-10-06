#include <UI/UIDropdown.h>

int create_dropdown              ( UIDropdown_t **pp_dropdown )
{

    // Initialized data
    UIDropdown_t *p_dropdown = calloc(1, sizeof(UIDropdown_t));
    
    // Check memory
    {
        #ifndef NDEBUG
            if ( p_dropdown == (void *)0 )
                goto no_mem;
        #endif
    }

    *pp_dropdown = p_dropdown;

    return 1;
    
    // Error handling
    {
        #ifndef NDEBUG
            no_mem:
                ui_print_error("[Standard Library] Failed to allocate memory in call to function \"%s\"\n", __FUNCTION__);
                return 0;
        #endif
    }
}

int load_dropdown_as_json_value        ( UIDropdown_t** pp_dropdown, json_value *p_value )
{

    // Argument check
	{
		#ifndef NDEBUG
			if(pp_dropdown == (void *)0)
				goto no_dropdown;
			if (p_value == (void*)0)
				goto no_value;
		#endif
	}

	// Initialized data
	UIDropdown_t *p_dropdown = 0;
    json_value **pp_options = 0,
                 *p_options  = 0,
                 *p_x        = 0,
                 *p_y        = 0,
                 *p_index    = 0;

	// Get properties from the dictionary
    if ( p_value->type == JSON_VALUE_OBJECT )
    {

        // Initialized data
        dict *p_dict = p_value->object;

        p_options = dict_get(p_dict, "options");
        p_x       = dict_get(p_dict, "x");
		p_y       = dict_get(p_dict, "y");
        p_index   = dict_get(p_dict, "index");
    }

	// Construct the dropdown
	{

		// Allocate a dropdown
		if ( create_dropdown(&p_dropdown) == 0)
			goto failed_to_allocate_label;

        // Set the options
        if ( p_options->type == JSON_VALUE_ARRAY)
        {

            // Initialized data
            size_t options_count = 0;

            array_get(p_options->list, 0, &options_count);

            pp_options  = calloc(options_count, sizeof(json_value *));

            p_dropdown->options = calloc(options_count, sizeof(char *));

            array_get(p_options->list, pp_options, 0);

            for (size_t i = 0; i < options_count; i++)
            {

                // Copy the label
                {

                    // Initialized data
                    size_t len = strlen(pp_options[i]->string);

                    if (len > p_dropdown->longest_option)
                        p_dropdown->longest_option = len;

                    // Allocate memory for label text
                    p_dropdown->options[i] = calloc(len+1, sizeof(char));
                    
                    // Copy the string
                    strncpy(p_dropdown->options[i], pp_options[i]->string, len);
                }
            }
            
            p_dropdown->options_count = options_count;
        }

		// Set the x
        if ( p_x->type == JSON_VALUE_INTEGER)
		    p_dropdown->x = p_x->integer;
        // Default
        else
            goto wrong_x_type;

		// Set the y
        if ( p_y->type == JSON_VALUE_INTEGER)
		    p_dropdown->y = p_y->integer;
        // Default
        else
            goto wrong_y_type;
        
        // Set the index
        if ( p_index )
        {
            if ( p_index->type == JSON_VALUE_INTEGER)
		        p_dropdown->index = p_index->integer;
            // Default
            else
                goto wrong_index_type;
        }
        p_dropdown->collapsed = true;
	}

	// Return
	*pp_dropdown = p_dropdown;

	// Success
	return 1;
    wrong_x_type:
    wrong_y_type:
    wrong_index_type:
        return 0;
	// Error handling
	{

		// Argument errors
		{
			no_dropdown:
				#ifndef NDEBUG
					ui_print_error("[UI] [Dropdown] Null pointer provided for \"pp_dropdown\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
			no_value:
				#ifndef NDEBUG
					ui_print_error("[UI] [Dropdown] Null pointer provided for \"p_value\" in call to function \"%s\"\n", __FUNCTION__);
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

int construct_dropdown(UIDropdown_t** pp_dropdown, char** options, i32 x, i32 y, i32 index)
{

    UIDropdown_t *dropdown = 0;
    create_dropdown(pp_dropdown);

    dropdown = *pp_dropdown;


    // Construct the dropdown
    {

        // Copy position
        {
            dropdown->x = x;
            dropdown->y = y;
        }

        // Copy index 
        dropdown->index = index;

        // Copy options
        {

            // Initialized data
            size_t option_count   = 0;
            size_t longest_option = 0;

            // Count each option
            while (options[++option_count]);

            dropdown->options_count = option_count;

            // Allocate options
            dropdown->options = calloc(option_count, sizeof(char *));

            // TOOD: Memory check

            // Iterate over each option
            for (size_t i = 0; i < option_count; i++)
            {

                // Initialized data
                char   *option         = options[i],
                       *i_option       = 0;
                size_t  option_len     = strlen(option);

                longest_option = (option_len > longest_option) ? option_len : longest_option;

                // Allocate for the option
                i_option = calloc(option_len + 1, sizeof(char));

                // TOOD: Memory check

                // Copy the option string
                strncpy(i_option, option, option_len);

                dropdown->options[i] = i_option;
            }

            dropdown->longest_option = longest_option;
        }

        // Set collapsed status
        dropdown->collapsed = true;
    }

    // Error detection
    if (dropdown->index >= dropdown->options_count || dropdown->index < 0)
        dropdown->index = 0;


    return 1;
}
 
int hover_dropdown               ( UIDropdown_t* dropdown, ui_mouse_state_t mouse_state)
{
    if ( dropdown->collapsed == false )
    {
        s32 x = mouse_state.x - dropdown->x,
            y = mouse_state.y - dropdown->y-12;

        if (y >= 0)
        {
            dropdown->hover_index = y / 11;
            if (dropdown->hover_index >= dropdown->options_count)
                dropdown->hover_index = dropdown->options_count-1;
            dropdown->index = dropdown->hover_index;
        }
        else
        {
            dropdown->hover_index = -1;
        }
    }

    // Iterate through callbacks
    for (size_t i = 0; i < dropdown->on_hover_count; i++)
    {
        // Define the callback function
        void (*callback)(UIDropdown_t*, ui_mouse_state_t) = dropdown->on_hover;

        // Call the callback function
        (*callback)(dropdown, mouse_state);

    }

    return 0;

}

int release_dropdown(UIDropdown_t* p_dropdown, ui_mouse_state_t mouse_state)
{
    // Iterate through callbacks
    for (size_t i = 0; i < p_dropdown->on_release_count; i++)
    {
        // Define the callback function
        void (*callback)(UIDropdown_t*, ui_mouse_state_t) = p_dropdown->on_release[i];

        // Call the callback function
        (*callback)(p_dropdown, mouse_state);

    }

    return 0;
}

int add_click_callback_dropdown(UIDropdown_t* p_dropdown, void(*callback)(UIDropdown_t*, ui_mouse_state_t))
{
    // TODO: Argument check

    // If this is the first callback, set the max to 1 and 
    if (p_dropdown->on_click_max == 0)
    {
        p_dropdown->on_click_max = 1;
        p_dropdown->on_click = calloc(1, sizeof(void*));
    }

    // Simple heuristic that doubles callbacks lists length when there is no space to store the callback pointer
    if (p_dropdown->on_click_count + 1 > p_dropdown->on_click_max)
    {
        // Double the max
        p_dropdown->on_click_max *= 2;

        p_dropdown->on_click = realloc(p_dropdown->on_click, p_dropdown->on_click_max);
    }

    // Increment the callback counter and install the new callback
    p_dropdown->on_click[p_dropdown->on_click_count++] = callback;

    return 0;
}

int add_hover_callback_dropdown(UIDropdown_t* p_dropdown, void(*callback)(UIDropdown_t*, ui_mouse_state_t))
{
    return 0;
}

int add_release_callback_dropdown(UIDropdown_t* p_dropdown, void(*callback)(UIDropdown_t*, ui_mouse_state_t))
{
    // TODO: Argument check

    // If this is the first callback, set the max to 1 and 
    if (p_dropdown->on_release_max == 0)
    {
        p_dropdown->on_release_max = 1;
        p_dropdown->on_release = calloc(1, sizeof(void*));
    }

    // Simple heuristic that doubles callbacks lists length when there is no space to store the callback pointer
    if (p_dropdown->on_release_count + 1 > p_dropdown->on_release_max)
    {
        // Double the max
        p_dropdown->on_release_max *= 2;

        p_dropdown->on_release = realloc(p_dropdown->on_release, p_dropdown->on_release_max);
    }

    // Increment the callback counter and install the new callback
    p_dropdown->on_release[p_dropdown->on_release_count++] = callback;

    return 0;
}

bool dropdown_in_bounds(UIDropdown_t* p_dropdown, ui_mouse_state_t mouse_state)
{
    i32 x = p_dropdown->x,
        y = p_dropdown->y,
        w = p_dropdown->width,
        h = p_dropdown->height;


    // Check for bounds
    if (mouse_state.x >= x && mouse_state.y >= y && mouse_state.x <= x + w && mouse_state.y <= y + h)
        return true;

    return false;
}

int click_dropdown               ( UIDropdown_t *dropdown, ui_mouse_state_t mouse_state )
{
    // Initialized data
    UIInstance_t *instance = ui_get_active_instance();
    
    // Toggle dropdown
    dropdown->collapsed ^= true;

    // Iterate through callbacks
    for (size_t i = 0; i < dropdown->on_click_count; i++)
    {
        // Define the callback function
        void (*callback)(UIDropdown_t *, ui_mouse_state_t) = dropdown->on_click[i];

        // Call the callback function
        (*callback)(dropdown, mouse_state);

    }

    return 0;
}

int destroy_dropdown             ( UIDropdown_t* dropdown)
{
    free(dropdown);
    return 0;
}

int draw_dropdown                ( UIWindow_t* window, UIDropdown_t* dropdown)
{
    // TODO: Argument check

    // Initialized data
    size_t   longest_option_len = 0,
             current_len        = 0;

    SDL_Rect r                  = { 0, 0, 0, 0 };

    UIInstance_t *instance = ui_get_active_instance();

    // 16 pixels of box drawings plus the string
    r.x = dropdown->x,
    r.y = dropdown->y,
    r.w = (dropdown->longest_option*8)+16,
    r.h = 12;

    dropdown->width  = r.w,
    dropdown->height = r.h;

    SDL_SetRenderDrawColor(window->renderer, (u8)instance->accent_1, (u8)(instance->accent_1 >> 8), (u8)(instance->accent_1 >> 16), 0xff);

    SDL_RenderFillRect(window->renderer, &r);
    SDL_SetRenderDrawColor(window->renderer, (u8)instance->primary, (u8)(instance->primary >> 8), (u8)(instance->primary >> 16), 0xff);

    SDL_RenderDrawRect(window->renderer, &r);

    ui_draw_text(dropdown->options[dropdown->index], window, r.x + 3, r.y + 1, 1);
    SDL_RenderDrawLine(window->renderer, r.x + r.w - 12, r.y + 2, r.x + r.w - 12, r.y + r.h - 3);

    if ( dropdown->collapsed == false )
    {
        SDL_SetRenderDrawColor(window->renderer, (u8)instance->primary, (u8)(instance->primary >> 8), (u8)(instance->primary >> 16), 0xff);
        ui_draw_text("\203", window, r.x + r.w - 10, r.y + 1, 1);
        for(size_t i = 0; i < dropdown->options_count; i++ )
        {
            if (i == dropdown->hover_index)
            {
                SDL_Rect s = { r.x + 2, 1 + r.y + (11 * (i + 1)), r.w - 2, 11 };
                SDL_SetRenderDrawColor(window->renderer, (u8)instance->accent_3, (u8)(instance->accent_3 >> 8), (u8)(instance->accent_3 >> 16), 0xff);
                SDL_RenderFillRect(window->renderer, &s);
            }
            else
            {
                SDL_Rect s = { r.x + 2, 1 + r.y + (11 * (i + 1)), r.w - 2, 11 };
                SDL_SetRenderDrawColor(window->renderer, (u8)instance->background, (u8)(instance->background >> 8), (u8)(instance->background >> 16), 0xff);
                SDL_RenderFillRect(window->renderer, &s);
            }

            SDL_SetRenderDrawColor(window->renderer, (u8)instance->primary, (u8)(instance->primary >> 8), (u8)(instance->primary >> 16), 0xff);
            ui_draw_text(dropdown->options[i], window, r.x + 5, 1 + r.y + (11 * (i + 1)),1);
            SDL_SetRenderDrawColor(window->renderer, (u8)instance->accent_3, (u8)(instance->accent_3 >> 8), (u8)(instance->accent_3 >> 16), 0xff);
            SDL_RenderDrawLine(window->renderer, r.x + 1, r.y + (11 * (i + 2)), r.x + r.w, r.y + (11 * (i + 2)));
            dropdown->height += 12;
        }
        SDL_RenderDrawLine(window->renderer, r.x + 1, r.y + r.h, r.x + 1, r.y + r.h + (12 * dropdown->options_count) - (dropdown->options_count + 1));
        SDL_RenderDrawLine(window->renderer, r.x + r.w , r.y + 1, r.x + r.w, r.y + r.h + (12 * dropdown->options_count) - (dropdown->options_count + 1));
        
    }
    else
    {
        ui_draw_text("\202", window, r.x + r.w - 10, r.y + 1, 1);
    }
    return 0;
}
