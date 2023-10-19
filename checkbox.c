#include <ui/checkbox.h>

int create_checkbox ( ui_checkbox **pp_checkbox )
{

    // Argument check
    if ( pp_checkbox == (void *) 0 ) goto no_checkbox;

    // Initialized data
    ui_checkbox* p_checkbox = calloc(1, sizeof(ui_checkbox));

    // Error check
    if( p_checkbox == (void *) 0 ) goto no_mem;

    // Return a pointer to the caller
    *pp_checkbox = p_checkbox;

    // Success
    return 1;

    // Error handling
    {
        // Argument errors
        {
            no_checkbox:
                #ifndef NDEBUG
                    // TODO: 
                #endif

                // Error
                return 0;
        }

        // Standard library errors
        {
            no_mem:
                #ifndef NDEBUG
                    ui_print_error("[Standard library] Failed to allocate memory in call to function \"%s\"\n",__FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int load_checkbox_as_json_value ( ui_checkbox **pp_checkbox, json_value *p_value )
{

    // Argument check
    if ( pp_checkbox == (void *) 0 ) goto no_checkbox;
    if ( p_value     == (void *) 0 ) goto no_value;

	// Initialized data
	ui_checkbox *p_checkbox = 0;
	json_value   *p_labels   = 0,
                 *p_checked  = 0,
                **pp_labels  = 0,
                **pp_checked = 0,
                 *p_x        = 0,
                 *p_y        = 0;

	// Get properties from the dictionary
    if (p_value->type == JSON_VALUE_OBJECT)
    {

        // Initialized data
        dict *p_dict = p_value->object;

        p_labels  = dict_get(p_dict, "labels");
        p_checked = dict_get(p_dict, "checked");
        p_x       = dict_get(p_dict, "x");
		p_y       = dict_get(p_dict, "y");

        // TODO: Error checking
    }

	// Construct the checkbox
	{

		// Allocate a checkbox
		if ( create_checkbox(&p_checkbox) == 0 ) goto failed_to_allocate_label;

        // Set the labels and checks
        if ( p_labels->type == JSON_VALUE_ARRAY)
        {

            // Initialized data
            size_t labels_count = 0;

            array_get(p_labels->list, 0, &labels_count);

            pp_labels  = calloc(labels_count, sizeof(json_value *));
            pp_checked = calloc(labels_count, sizeof(json_value *));

            p_checkbox->labels = calloc(labels_count, sizeof(char *));
            p_checkbox->checks = calloc(labels_count, sizeof(bool));

            array_get(p_labels->list, pp_labels, 0);
            array_get(p_labels->list, pp_checked, 0);

            for (size_t i = 0; i < labels_count; i++)
            {

                // Copy the label
                {

                    // Initialized data
                    size_t len = strlen(pp_labels[i]->string);

                    if (len > p_checkbox->longest_label)
                        p_checkbox->longest_label = len;

                    // Allocate memory for label text
                    p_checkbox->labels[i] = calloc(len+1, sizeof(char));
                    
                    // Copy the string
                    strncpy(p_checkbox->labels[i], pp_labels[i]->string, len);
                }

                p_checkbox->checks[i] = pp_checked[i]->boolean; 
            }
            
            p_checkbox->label_count = labels_count;
        }

		// Set the x
        if ( p_x->type == JSON_VALUE_INTEGER )
		    p_checkbox->x = p_x->integer;
        // Default
        else
            goto wrong_x_type;

		// Set the y
        if ( p_y->type == JSON_VALUE_INTEGER )
		    p_checkbox->y = p_y->integer;
        // Default
        else
            goto wrong_y_type;
	}

	// Return
	*pp_checkbox = p_checkbox;

	// Success
	return 1;

    wrong_x_type:
    wrong_y_type:
        return 0;

	// Error handling
	{

		// Argument errors
		{
			no_checkbox:
				#ifndef NDEBUG
					ui_print_error("[UI] [Checkbox] Null pointer provided for \"pp_checkbox\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
			no_value:
				#ifndef NDEBUG
					ui_print_error("[UI] [Checkbox] Null pointer provided for \"p_value\" in call to function \"%s\"\n", __FUNCTION__);
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

int construct_checkbox ( ui_checkbox** pp_checkbox, char** labels, bool* checked, i32 x, i32 y )
{

    // TODO: Argument check
    //

    // Initialized data
    ui_checkbox *p_checkbox = 0;

    // Allocate a checkbox
    if ( create_checkbox(pp_checkbox) == (void *) 0 ) goto failed_to_allocate_checkbox;

    // Construct the checkbox
    {

        // Initialized data
        size_t label_count   = 0,
               longest_label = 0;

        // Count labels
        while (labels[++label_count]);

        // Store the quantity of labels
        p_checkbox->label_count = label_count;
        
        // Allocate memory for checks
        p_checkbox->checks = calloc(label_count, sizeof(bool));

        // Error check
        if ( p_checkbox->checks == (void *) 0 ) goto no_mem;

        // Construct a dictionary for the checkbox labels
        if ( dict_construct(&p_checkbox->labels, label_count, 0) == 0 ) goto failed_to_construct_dict;

        // Allocate for and copy labels, check states
        for (size_t i = 0; i < label_count; i++)
        {

            // Initialized data
            char   *label    = labels[i],
                   *i_label  = 0;
            size_t  i_length = strlen(label);

            // Find the longest label
            longest_label = (i_length > longest_label) ? i_length : longest_label;

            // Allocate for the option
            i_label = calloc(i_length + 1, sizeof(char));

            // TOOD: Memory check
            if ( i_label == (void *) 0 ) goto no_mem;

            // Copy the option string
            strncpy(i_label, label, i_length);

            // Store the label in the checkbox struct
            p_checkbox->labels[i] = i_label;

        }

        // Store the length of the longest label
        p_checkbox->longest_label = longest_label;

        // Set x
        p_checkbox->x = x;

        // Set y
        p_checkbox->y = y;

    }

    // Return a pointer to the caller
    *pp_checkbox = p_checkbox;
    
    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            
        }

        // dict errors
        {
            failed_to_construct_dict:;
        }

        // Standard library errors
        {
            no_mem:;
        }

        // UI errors
        {
            failed_to_allocate_checkbox:;
        }

        // TODO: remove

        // Error
        return 0;
    }

}

int hover_checkbox ( ui_checkbox *p_checkbox, ui_mouse_state mouse_state )
{

    // TODO: Argument check
	//

    // Initialized data
    s32 x = mouse_state.x - p_checkbox->x,
        y = mouse_state.y - p_checkbox->y;

    if ( y >= 0 )
    {
        p_checkbox->hover_index = (y / 15) ;
        if (p_checkbox->hover_index > p_checkbox->label_count)
            p_checkbox->hover_index = p_checkbox->label_count - 1;
    }
    else
    {
        p_checkbox->hover_index = -1;
    }

    // Success
    return 1;

    // TODO: Error handling
}

int click_checkbox ( ui_checkbox *p_checkbox, ui_mouse_state mouse_state)
{
    
    // TODO: Argument check
	//

    if(p_checkbox->hover_index != -1)
        p_checkbox->checks[p_checkbox->hover_index] ^= true;

    // Iterate through callbacks
    for (size_t i = 0; i < p_checkbox->on_click_count; i++)
    {
        // Define the callback function
        void (*callback)(ui_checkbox*, ui_mouse_state) = p_checkbox->on_click[i];

        // Call the callback function
        (*callback)(p_checkbox, mouse_state);

    }

    // Success
    return 1;

    // TODO: Error handling
    {

    }
}

int release_checkbox ( ui_checkbox *p_checkbox, ui_mouse_state mouse_state )
{

    // TODO: Argument check
	//

    // Iterate through callbacks
    for (size_t i = 0; i < p_checkbox->on_release_count; i++)
    {
        // Define the callback function
        void (*callback)(ui_checkbox*, ui_mouse_state) = p_checkbox->on_release[i];


        // Call the callback function
        if (callback)
            (*callback)(p_checkbox, mouse_state);

    }

    // Success
    return 1;
}

int add_click_callback_checkbox(ui_checkbox *p_checkbox, void(*callback)(ui_checkbox*, ui_mouse_state))
{

    // TODO: Argument check
	//

    // TODO:
    // Success
    return 1;

    // TODO: Error handling
    {

    }
}

int add_hover_callback_checkbox ( ui_checkbox *p_checkbox, void(*callback)(ui_checkbox*, ui_mouse_state) )
{
    
    // TODO: Argument check
	//

    // TODO:
    // Success
    return 1;

    // TODO: Error handling
    {

    }
}

int add_release_callback_checkbox ( ui_checkbox *p_checkbox, void(*callback)(ui_checkbox*, ui_mouse_state) )
{

    // TODO: Argument check
	//

    // Success
    return 1;

    // TODO: Error handling
    {

    }
}

int draw_checkbox ( ui_window *window, ui_checkbox *checkbox )
{

    // TODO: Argument check
	//

    // Initialized data
    ui_instance *instance = ui_get_active_instance();
    SDL_Rect      r        = { checkbox->x, checkbox->y, 12, 12 };

    checkbox->width  = 12,
    checkbox->height = 18*checkbox->label_count;

    for (size_t i = 0; i < checkbox->label_count; i++)
    {
        SDL_SetRenderDrawColor(window->renderer, (u8)instance->primary, (u8)(instance->primary >> 8), (u8)(instance->primary >> 16), 0xff);
        SDL_RenderDrawRect(window->renderer, &r);

        bool *v = checkbox->checks;

        if (v[i] == true)
            ui_draw_text("\200", window, r.x + 2, r.y + 1, 1);

        ui_draw_text(checkbox->labels[i], window, r.x + 14, r.y + 2, 1);

        r.y += 15;
    }

    // Success
    return 1;

    // TODO: Error handling
    {

    }
}


bool checkbox_in_bounds ( ui_checkbox  *checkbox, ui_mouse_state mouse_state)
{

    // TODO: Argument check
	//

	// Initialized data
	i32  x = checkbox->x,
		 y = checkbox->y,
		 w = checkbox->width,
		 h = checkbox->height;
	
	// Check for bounds
	if (mouse_state.x >= x && mouse_state.y >= y && mouse_state.x <= x + w && mouse_state.y <= y + h)

        // In bounds
		return true;

    // Out of bounds
	return false;

    // TODO: Error handling
    {

    }
}


int destroy_checkbox ( ui_checkbox *checkbox )
{
    // TODO: Argument check
    // 

    // TODO: 

    // Free the checkbox struct
    free(checkbox);

    // Success
    return 1;

    // TODO: Error handling
    {

    }
}
