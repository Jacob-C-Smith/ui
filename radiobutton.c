#include <UI/radiobutton.h>

int create_radio_button(ui_radiobutton** pp_radio_button)
{
    
    // Argument check
    {
        #ifndef NDEBUG
            if(pp_radio_button == (void *)0)
                goto no_radio_button;
        #endif
    }

    // Allocate a UIRadioButton_s
    ui_radiobutton* p_radio_button = calloc(1, sizeof(ui_radiobutton));

    // Check memory
    {
        if(p_radio_button == (void *)0)
            goto no_mem;
    }

    // Return 
    *pp_radio_button = p_radio_button;

    // Success
    return 1;

    // TODO: Error handling
    {
        // Argument errors
        {
            no_radio_button:
            #ifndef NDEBUG

            #endif
            return 0;
        }

        // Standard library errors
        {
            no_mem:
                ui_print_error("[Standard library] Failed to allocate memory in call to function \"%s\"\n",__FUNCTION__);
                return 0;
        }
    }
}

int load_radio_button_as_json_value ( ui_radiobutton **pp_radio_button, json_value *p_value )
{
    // Argument check
	{
		#ifndef NDEBUG
			if(pp_radio_button == (void *)0)
				goto no_radio_button;
			if (p_value == (void*)0)
				goto no_value;
		#endif
	}

	// Initialized data
	ui_radiobutton *p_radio_button = 0;
	json_value     *p_labels       = 0,
	                *p_x            = 0,
		            *p_y            = 0,
                    *p_index        = 0,
                   **pp_labels      = 0,
                   **pp_checked     = 0;

	// Get properties from the dictionary
    if (p_value->type == JSON_VALUE_OBJECT)
    {

        // Initialized data
        dict *p_dict = p_value->object;

        p_labels  = dict_get(p_dict, "labels");
        p_x       = dict_get(p_dict, "x");
		p_y       = dict_get(p_dict, "y");
        p_index   = dict_get(p_dict, "index");
    }

	// Construct the checkbox
	{

		// Allocate a checkbox
		if ( create_radio_button(&p_radio_button) == 0)
			goto failed_to_allocate_label;

        // Set the labels and checks
        if ( p_labels->type == JSON_VALUE_ARRAY)
        {

            // Initialized data
            size_t labels_count = 0;

            // Dump the contents of the array
            {

                // Get the size of the array
                array_get(p_labels->list, 0, &labels_count);

                // Allocate memory for arrays
                pp_labels = calloc(labels_count, sizeof(json_value *));
                p_radio_button->labels = calloc(labels_count, sizeof(char *));

                // Error checking
                if ( pp_labels == (void *) 0 )
                    goto no_mem;
                if ( p_radio_button->labels == (void *) 0 )
                    goto no_mem;
                
                // Dump the array
                array_get(p_labels->list, pp_labels, 0);
            }

            // Iterate over each label
            for (size_t i = 0; i < labels_count; i++)

            // Copy the label
            {
                
                // Initialized data
                size_t len = strlen(pp_labels[i]->string);

                if ( len > p_radio_button->longest_label )
                    p_radio_button->longest_label = len;

                // Allocate memory for label text
                p_radio_button->labels[i] = calloc(len+1, sizeof(char));
                
                // Error checking
                if ( p_radio_button->labels[i] == (void *) 0 )
                    goto no_mem;

                // Copy the string
                strncpy(p_radio_button->labels[i], pp_labels[i]->string, len);
            }
            
            p_radio_button->label_count = labels_count;
        }

		// Set the x
        if ( p_x->type == JSON_VALUE_INTEGER )
		    p_radio_button->x = p_x->integer;
        // Default
        else
            goto wrong_x_type;
        
        // Set the y
        if ( p_y->type == JSON_VALUE_INTEGER )
		    p_radio_button->y = p_y->integer;
        // Default
        else
            goto wrong_y_type;

		// Set the index
        if ( p_index->type == JSON_VALUE_INTEGER )
		    p_radio_button->index = p_index->integer;
        // Default
        else
            goto wrong_index_type;

	}

	// Return
	*pp_radio_button = p_radio_button;

	// Success
	return 1;

    no_mem:
    wrong_x_type:
    wrong_y_type:
    wrong_index_type:
        return 0;

	// Error handling
	{

		// Argument errors
		{
			no_radio_button:
				#ifndef NDEBUG
					ui_print_error("[UI] [Radio Button] Null pointer provided for \"pp_radio_button\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
			no_value:
				#ifndef NDEBUG
					ui_print_error("[UI] [Radio Button] Null pointer provided for \"p_value\" in call to function \"%s\"\n", __FUNCTION__);
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

int construct_radio_button(ui_radiobutton** radio_button, char** labels, size_t index, i32 x, i32 y)
{
    // TODO: Argument check
    {

    }

    // Initialized data
    ui_radiobutton *i_radio_button = 0;

    create_radio_button(radio_button);
    
    i_radio_button = *radio_button;

    // Construct the radio button
    {

        // Initialized data
        size_t label_count   = 0,
               longest_label = 0;

        // Count labels
        while (labels[++label_count]);

        i_radio_button->label_count = label_count;

        dict_construct(&i_radio_button->labels, label_count, 0);

        // Allocate for and copy labels
        for (size_t i = 0; i < label_count; i++)
        {

            // Initialized data
            char   *label   = labels[i],
                   *i_label = 0;
            size_t  i_length = strlen(label);

            
            longest_label = (i_length > longest_label) ? i_length : longest_label;


            // Allocate for the option
            i_label = calloc(i_length + 1, sizeof(char));

            // TOOD: Memory check

            // Copy the option string
            strncpy(i_label, label, i_length);

            i_radio_button->labels[i] = i_label;

        }

        i_radio_button->longest_label = longest_label;

        i_radio_button->index = index;

        // Set x
        i_radio_button->x = x;

        // Set y
        i_radio_button->y = y;

    }

    return 1;
}

int hover_radio_button(ui_radiobutton* radio_button, ui_mouse_state mouse_state)
{
    s32 x = mouse_state.x - radio_button->x,
        y = mouse_state.y - radio_button->y;

    if (y >= 0)
    {
        radio_button->hover_index = (y / 15) ;
        if (radio_button->hover_index >= radio_button->label_count)
            radio_button->hover_index = radio_button->label_count - 1;
    }
    else
    {
        radio_button->hover_index = -1;
    }

    
    return 0;
}

int click_radio_button(ui_radiobutton* radio_button, ui_mouse_state mouse_state)
{
    if (radio_button->hover_index != -1)
        radio_button->index = radio_button->hover_index;

    // Iterate through callbacks
    for (size_t i = 0; i < radio_button->on_click_count; i++)
    {
        // Define the callback function
        void (*callback)(ui_radiobutton*, ui_mouse_state) = radio_button->on_click[i];

        // Call the callback function
        (*callback)(radio_button, mouse_state);

    }

    return 0;
}

int release_radio_button(ui_radiobutton* radio_button, ui_mouse_state mouse_state)
{
    return 0;
}

int add_click_callback_radio_button(ui_radiobutton* radio_button, void(*callback)(ui_radiobutton*, ui_mouse_state))
{
    return 0;
}

int add_hover_callback_radio_button(ui_radiobutton* radio_button, void(*callback)(ui_radiobutton*, ui_mouse_state))
{
    return 0;
}

int add_release_callback_radio_button(ui_radiobutton* radio_button, void(*callback)(ui_radiobutton*, ui_mouse_state))
{
    return 0;
}

int draw_radio_button(ui_window* window, ui_radiobutton* radio_button)
{
    ui_instance* instance = ui_get_active_instance();
    SDL_Rect r = { radio_button->x, radio_button->y, 12, 12 };

    radio_button->width  = 12,
    radio_button->height = 18 * radio_button->label_count;

    for (size_t i = 0; i < radio_button->label_count; i++)
    {
        SDL_SetRenderDrawColor(window->renderer, (u8)instance->primary, (u8)(instance->primary >> 8), (u8)(instance->primary >> 16), 0xff);
        ui_draw_circle(5, window, radio_button->x+6, radio_button->y + (i*15) + 6);

        if (i == radio_button->index)
            ui_draw_text("\201", window, r.x + 3, r.y + (i)+1, 1);

        ui_draw_text(radio_button->labels[i], window, r.x + 14, r.y + 3, 1);

        r.y += 14;
    }

    return 0;
}

bool radio_button_in_bounds(ui_radiobutton* radio_button, ui_mouse_state mouse_state)
{
	// Initialized data
	i32  x = radio_button->x,
		 y = radio_button->y,
		 w = radio_button->width,
		 h = radio_button->height;
	
	// Check for bounds
	if (mouse_state.x >= x && mouse_state.y >= y && mouse_state.x <= x + w && mouse_state.y <= y + h)
		return true;

	return false;
}

int destroy_radio_button(ui_radiobutton* radio_button)
{
    return 0;
}
