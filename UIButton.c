#include <UI/UIButton.h>

int           create_button               ( UIButton_t **pp_button )
{
	// Argument check
    {
        #ifndef NDEBUG
            if( pp_button == (void *) 0 )
                goto no_button;
        #endif
    }

    // Allocate for a button
    UIButton_t* p_button = calloc(1, sizeof(UIButton_t));

    // Check memory
    {
        #ifndef NDEBUG
            if(p_button == (void *)0)
                goto no_mem;
        #endif
    }

    *pp_button = p_button;

    return 0;

    // Error handling
    {

        // Argument errors
        {
            no_button:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Button] Null pointer provided for \"pp_button\" in call to function \"%s\"\n",__FUNCTION__);
                #endif
                return -1;
        }

        // Standard library errors
        {
            no_mem:
                #ifndef NDEBUG
                    ui_print_error("[Standard library] Failed to allocate memory in call to function \"%s\"\n",__FUNCTION__);
                #endif
                return -1;
        }
    }
}

int           load_button_as_json_value         ( UIButton_t **pp_button, JSONValue_t *p_value )
{

    // Argument check
	{
		#ifndef NDEBUG
			if(pp_button == (void *)0)
				goto no_button;
			if (p_value == (void*)0)
				goto no_value;
		#endif
	}

	// Initialized data
	UIButton_t *p_button = 0;
	char       *label    = 0;
	signed      x        = 0,
		        y        = 0;

	// Get properties from the dictionary
    if (p_value->type == JSONobject)
    {

        // Initialized data
        dict *p_dict = p_value->object;

        label = JSON_VALUE(((JSONValue_t *)dict_get(p_dict, "label")), JSONstring);
        x     = JSON_VALUE(((JSONValue_t *)dict_get(p_dict, "x"))   , JSONinteger);
		y     = JSON_VALUE(((JSONValue_t *)dict_get(p_dict, "y"))   , JSONinteger);
    }

	// Error checking
	{
		#ifndef NDEBUG
			//if((label && x && y))
			//	goto no_x;
		#endif
	}

	// Construct the label
	{

		// Allocate a label
		if ( create_label(&p_button) == 0)
			goto failed_to_allocate_label;

		// Copy the label text
		{

			// Initialized data
			size_t label_text_len = strlen(label);

			// Allocate memory for the label text
			p_button->label = calloc(label_text_len+1, sizeof(char));

			// TODO: Check memory

			// Copy the string
			strncpy(p_button->label, label, label_text_len);
		}

		// Set the label x, y, and size
		p_button->x    = x;
		p_button->y    = y;
	}

	// Return
	*pp_button = p_button;

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_button:
				#ifndef NDEBUG
					ui_print_error("[UI] [Button] Null pointer provided for \"pp_button\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
			no_value:
				#ifndef NDEBUG
					ui_print_error("[UI] [Button] Null pointer provided for \"p_value\" in call to function \"%s\"\n", __FUNCTION__);
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

int           hover_button                ( UIButton_t  *p_button, ui_mouse_state_t mouse_state)
{

    // Argument check
    {
        #ifndef NDEBUG
            if ( p_button == (void *) 0 )
                goto no_button;
        #endif  
    }

    // Iterate through hover callbacks
    for (size_t i = 0; i < p_button->on_hover_count; i++)
    {

        // Define the callback function
        void (*callback)(UIButton_t*, ui_mouse_state_t) = p_button->on_hover[i];

        // Call the callback function
        if (callback)
            (*callback)(p_button, mouse_state);

    }

    return 0;

    // Error handling
    {

        // Argument errors
        {
            no_button:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Button] Null pointer provided for \"button\" in call to function \"%s\"\n", __FUNCTION__);
                #endif
                return 0;
        }
    }
}

int           click_button                ( UIButton_t  *p_button, ui_mouse_state_t mouse_state)
{
    p_button->depressed = true;

    // Iterate through callbacks
    for (size_t i = 0; i < p_button->on_click_count; i++)
    {
        // Define the callback function
        void (*callback)(UIButton_t*, ui_mouse_state_t) = p_button->on_click[i];


        // Call the callback function
        if(callback)            
            (*callback)(p_button, mouse_state);

    }

    return 0;
}

int           release_button              ( UIButton_t  *p_button, ui_mouse_state_t mouse_state )
{
    p_button->depressed = false;

    // Iterate through callbacks
    for (size_t i = 0; i < p_button->on_release_count; i++)
    {
        // Define the callback function
        void (*callback)(UIButton_t*, ui_mouse_state_t) = p_button->on_release[i];


        // Call the callback function
        if (callback)
            (*callback)(p_button, mouse_state);

    }
    return 0;
}

int           add_click_callback_button   ( UIButton_t  *p_button, void(*callback)(UIButton_t*, ui_mouse_state_t))
{
    // TODO: Argument check

    // If this is the first callback, set the max to 1 and 
    if (p_button->on_click_max == 0)
    {
        p_button->on_click_max = 1;
        p_button->on_click = calloc(1, sizeof(void*));
    }

    // Simple heuristic that doubles callbacks lists length when there is no space to store the callback pointer
    if (p_button->on_click_count + 1 > p_button->on_click_max)
    {
        // Double the max
        p_button->on_click_max *= 2;

        realloc(p_button->on_click, p_button->on_click_max);
    }

    // Increment the callback counter and install the new callback
    p_button->on_click[p_button->on_click_count++] = callback;

    return 0;

    // TODO: Error handling
}

int           add_hover_callback_button   ( UIButton_t  *button, void(*callback)(UIButton_t*, ui_mouse_state_t))
{
    // TODO: Argument check

    // If this is the first callback, set the max to 1 and 
    if (button->on_hover_max == 0)
    {
        button->on_hover_max = 1;
        button->on_hover     = calloc(1, sizeof(void*));
    }


    // Simple heuristic that doubles callbacks lists length if there is no space to 
    // store the callback pointer
    if (button->on_hover_count + 1 > button->on_hover_max)
    {
        // Double the max
        button->on_hover_max *= 2;

        // Allocate the maximum number of callbacks
        void **callbacks = calloc(button->on_hover_max, sizeof(void*)),
              *t         = button->on_hover;

        // Copy all the callbacks from the button to the new callback list
        memcpy(callbacks, button->on_hover, button->on_hover_count * sizeof(void *));

        // Set the hover callback list pointer to the new list
        button->on_hover = callbacks;

        // Free the old callback list
        free(t);
    }

    // Increment the callback counter and install the new callback
    button->on_hover[button->on_hover_count++] = callback;

    return 0;

    // TODO: Error handling
}

int           add_release_callback_button ( UIButton_t  *button, void(*callback)(UIButton_t*, ui_mouse_state_t))
{
    // TODO: Argument check

    // If this is the first callback, set the max to 1 and 
    if (button->on_release_max == 0)
    {
        button->on_release_max = 1;
        button->on_release = calloc(1, sizeof(void*));
    }


    // Simple heuristic that doubles callbacks lists length if there is no space to 
    // store the callback pointer
    if (button->on_release_count + 1 > button->on_release_max)
    {
        // Double the max
        button->on_release_max *= 2;

        // Allocate the maximum number of callbacks
        void** callbacks = calloc(button->on_release_max, sizeof(void*)),
            * t = button->on_release;

        // Copy all the callbacks from the button to the new callback list
        memcpy(callbacks, button->on_release, button->on_release_count * sizeof(void*));

        // Set the release callback list pointer to the new list
        button->on_release = callbacks;

        // Free the old callback list
        free(t);
    }

    // Increment the callback counter and install the new callback
    button->on_release[button->on_release_count++] = callback;

    return 0;

    // TODO: Error handling
}

int           draw_button                 ( UIWindow_t  *window, UIButton_t *button )
{
    UIInstance_t *instance = ui_get_active_instance();
    size_t        l        = strlen(button->label);
    SDL_Rect      r        = { button->x+1, button->y+1, (l * 8) + 5, 12 };
    
    button->w  = r.w,
    button->h = r.h;

    if (button->depressed==false)
    {
        SDL_SetRenderDrawColor(window->renderer, (u8)instance->accent_2, (u8)(instance->accent_2 >> 8), (u8)(instance->accent_2 >> 16), 0xff);
        SDL_RenderDrawLine(window->renderer, r.x + r.w - 1, r.y, r.x + r.w - 1, r.y + r.h - 1);
        SDL_RenderDrawLine(window->renderer, r.x, r.y + r.h - 1, r.x + r.w - 1, r.y + r.h - 1);
        r.x--, r.y--;
    }

    SDL_SetRenderDrawColor(window->renderer, (u8)instance->accent_1, (u8)(instance->accent_1 >> 8), (u8)(instance->accent_1 >> 16), 0xff);
    SDL_RenderFillRect(window->renderer, &r);
    SDL_SetRenderDrawColor(window->renderer, (u8)instance->primary, (u8)(instance->primary >> 8), (u8)(instance->primary >> 16), 0xff);
    SDL_RenderDrawRect(window->renderer, &r);
    
    ui_draw_text(button->label, window, r.x + 3, r.y + 1, 1);

    return 0;
}

bool          button_in_bounds            ( UIButton_t  *button, ui_mouse_state_t mouse_state )
{
    // Initialized data
	i32  x = button->x,
		 y = button->y,
		 w = button->w,
		 h = button->h;
	
	// Check for bounds
	if (mouse_state.x >= x && mouse_state.y >= y && mouse_state.x <= x + w && mouse_state.y <= y + h)
		return true;

	return false;

}

int           destroy_button              ( UIButton_t  *p_button )
{

    // Argument check
    {
        if (p_button == (void*)0)
            goto no_button;
    }
        
    // Free label string
    free(p_button->label);

    // Free callbacks
    {
        free(p_button->on_click);
        free(p_button->on_hover);
        free(p_button->on_release);
    }

    // Free the button memory
    free(p_button);

    return 0;

    // Error handling
    {

        // Argument errors
        {
            no_button:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Button] Null pointer provided for \"p_button\" in call to function \"%s\"\n", __FUNCTION__);
                #endif
                return -1;
        }
    }
}
