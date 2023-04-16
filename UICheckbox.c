#include <UI/UICheckbox.h>

int create_checkbox              ( UICheckbox_t **pp_checkbox )
{
    // Argument check
    {
        #ifndef NDEBUG
            if(pp_checkbox == (void *)0)
                goto no_checkbox;
        #endif
    }

    // Allocate for a checkbox
    UICheckbox_t* p_checkbox = calloc(1, sizeof(UICheckbox_t));

    // Check memory
    {
        if(p_checkbox == (void *)0)
            goto no_mem;
    }

    *pp_checkbox = p_checkbox;

    return 1;

    // TODO: Error handling
    {
        // Argument errors
        {
            no_checkbox:
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

int load_checkbox_as_json_value ( UICheckbox_t **pp_checkbox, JSONValue_t *p_value )
{

    // Argument check
	{
		#ifndef NDEBUG
			if(pp_checkbox == (void *)0)
				goto no_checkbox;
			if (p_value == (void*)0)
				goto no_value;
		#endif
	}

	// Initialized data
	UICheckbox_t *p_checkbox = 0;
	array        *p_labels   = 0,
                 *p_checked  = 0;
	signed        x          = 0,
		          y          = 0;
    JSONValue_t **pp_labels  = 0,
                **pp_checked = 0;

	// Get properties from the dictionary
    if (p_value->type == JSONobject)
    {

        // Initialized data
        dict *p_dict = p_value->object;

        p_labels  = JSON_VALUE(((JSONValue_t *)dict_get(p_dict, "labels")), JSONarray);
        p_checked = JSON_VALUE(((JSONValue_t *)dict_get(p_dict, "checked")), JSONarray);
        x         = JSON_VALUE(((JSONValue_t *)dict_get(p_dict, "x"))   , JSONinteger);
		y         = JSON_VALUE(((JSONValue_t *)dict_get(p_dict, "y"))   , JSONinteger);
    }

	// Error checking
	{
		// TODO
	}

	// Construct the checkbox
	{

		// Allocate a checkbox
		if ( create_checkbox(&p_checkbox) == 0)
			goto failed_to_allocate_label;

        // Set the labels and checks
        {

            // Initialized data
            size_t labels_count = 0;

            array_get(p_labels, 0, &labels_count);

            pp_labels  = calloc(labels_count, sizeof(JSONValue_t *));
            pp_checked = calloc(labels_count, sizeof(JSONValue_t *));

            p_checkbox->labels = calloc(labels_count, sizeof(char *));
            p_checkbox->checks = calloc(labels_count, sizeof(bool));

            array_get(p_labels, pp_labels, 0);
            array_get(p_labels, pp_checked, 0);

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

    

		// Set the label x, y, and size
		p_checkbox->x    = x;
		p_checkbox->y    = y;
	}

	// Return
	*pp_checkbox = p_checkbox;

	// Success
	return 1;

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

int construct_checkbox(UICheckbox_t** checkbox, char** labels, bool* checked, i32 x, i32 y)
{
    // TODO: Argument check
    {

    }

    // Initialized data
    UICheckbox_t *i_checkbox = 0;

    create_checkbox(checkbox);
    
    i_checkbox = *checkbox;

    // Construct the checkbox
    {

        // Initialized data
        size_t label_count   = 0,
               longest_label = 0;

        // Count labels
        while (labels[++label_count]);

        i_checkbox->label_count = label_count;

        dict_construct(&i_checkbox->labels, label_count);

        // Allocate for and copy labels, check states
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

            i_checkbox->labels[i] = i_label;

        }

        i_checkbox->longest_label = longest_label;
        i_checkbox->checks        = calloc(label_count, sizeof(bool));

        // Set x
        i_checkbox->x = x;

        // Set y
        i_checkbox->y = y;

    }

    return 1;

    // TODO: Error handling

}

int           hover_checkbox               ( UICheckbox_t *checkbox, ui_mouse_state_t mouse_state)
{
    s32 x = mouse_state.x - checkbox->x,
        y = mouse_state.y - checkbox->y;

    if (y >= 0)
    {
        checkbox->hover_index = (y / 15) ;
        if (checkbox->hover_index > checkbox->label_count)
            checkbox->hover_index = checkbox->label_count - 1;
    }
    else
    {
        checkbox->hover_index = -1;
    }

    
    return 0;
}

int           click_checkbox               ( UICheckbox_t *checkbox, ui_mouse_state_t mouse_state)
{
    if(checkbox->hover_index != -1)
        checkbox->checks[checkbox->hover_index] ^= true;

    // Iterate through callbacks
    for (size_t i = 0; i < checkbox->on_click_count; i++)
    {
        // Define the callback function
        void (*callback)(UICheckbox_t*, ui_mouse_state_t) = checkbox->on_click[i];

        // Call the callback function
        (*callback)(checkbox, mouse_state);

    }

    return 1;
}

int           release_checkbox              ( UICheckbox_t *checkbox, ui_mouse_state_t mouse_state )
{
    // Iterate through callbacks
    for (size_t i = 0; i < checkbox->on_release_count; i++)
    {
        // Define the callback function
        void (*callback)(UICheckbox_t*, ui_mouse_state_t) = checkbox->on_release[i];


        // Call the callback function
        if (callback)
            (*callback)(checkbox, mouse_state);

    }

    return 0;
}

int add_click_callback_checkbox(UICheckbox_t* checkbox, void(*callback)(UICheckbox_t*, ui_mouse_state_t))
{
    // TODO:
    return 0;
}

int add_hover_callback_checkbox(UICheckbox_t* checkbox, void(*callback)(UICheckbox_t*, ui_mouse_state_t))
{
    // TODO:
    return 0;
}

int add_release_callback_checkbox(UICheckbox_t* checkbox, void(*callback)(UICheckbox_t*, ui_mouse_state_t))
{
    // TODO:
    return 0;
}

int           draw_checkbox                ( UIWindow_t   *window  , UICheckbox_t *checkbox )
{
    UIInstance_t* instance = ui_get_active_instance();
    SDL_Rect r = { checkbox->x, checkbox->y, 12, 12 };

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

    return 0;

}


bool       checkbox_in_bounds  ( UICheckbox_t  *checkbox, ui_mouse_state_t mouse_state)
{
	// Initialized data
	i32  x = checkbox->x,
		 y = checkbox->y,
		 w = checkbox->width,
		 h = checkbox->height;
	
	// Check for bounds
	if (mouse_state.x >= x && mouse_state.y >= y && mouse_state.x <= x + w && mouse_state.y <= y + h)
		return true;

	return false;

}


int           destroy_checkbox             ( UICheckbox_t *checkbox )
{
    free(checkbox);
    return 0;
}
