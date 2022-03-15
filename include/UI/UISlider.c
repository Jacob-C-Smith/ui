#include <UI/UISlider.h>

UISlider_t* create_slider(void)
{
    // Initialized data
	UISlider_t *ret = calloc(1, sizeof(UILabel_t));
	
	// Check allocated memory, if in debug mode
	{
		#ifndef NDEBUG
		if (ret == (void*)0)
			goto noMem;
		#endif
	}
	
	// Return a pointer to the start of the struct
	return (UISlider_t *) ret;

	// Error handling
	{
		// Standard library errors
		{
			noMem:
			#ifndef NDEBUG
				ui_print_error("[UI] [Slider] Failed to create a slider; Out of memory\n");
			#endif
			return (void*)0;
		}
	}
}

UISlider_t* load_slider(const char path[])
{
    // Uninitialized data
    u8         *data;
	UISlider_t  *ret;

    // Initialized data
    size_t      i   = 0;

    // Load the file
    i    = ui_load_file(path, 0, false);
    data = calloc(i, sizeof(u8));
    ui_load_file(path, data, false);

	// Parse the JSON object
	ret = 0;// load_slider_as_json(data);

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

UISlider_t* load_slider_as_json_tokens(JSONToken_t* tokens, size_t token_count)
{
    // Argument check
    {
        #ifndef NDEBUG
            if(tokens == (void *)0)
                goto no_tokens;
            if (token_count == 0)
                goto no_token_count;
        #endif
    }

    // Initialized data
    UICheckbox_t *ret           = create_checkbox();
    size_t        j             = 0,
                  label_count   = 0,
                  longest_label = 0;
    char        **labels        = 0,
                 *x             = 0,
                 *y             = 0,
                **checked       = 0;
    bool          hidden        = false;

    // Search through values and pull out relevent information
    for (j = 0; j < token_count; j++)
    {
        if (strcmp("type", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONstring)
                if (strcmp(tokens[j].value.n_where, "CHECKBOX") != 0)
                    goto notACheckbox;
        }
        else if (strcmp("name", tokens[j].key) == 0)
            continue;
        if (strcmp("labels", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONarray)
                labels = tokens[j].value.a_where;
            else
                goto checkbox_labels_type_error;

            continue;
        }
        if (strcmp("x", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONprimative)
                x = tokens[j].value.n_where;
            else
                goto checkbox_x_type_error;

            continue;
        }
        if (strcmp("y", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONprimative)
                y = tokens[j].value.n_where;
            else
                goto checkbox_y_type_error;
        }
        if (strcmp("hidden", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONprimative)
                hidden = tokens[j].value.n_where;
            else
                goto checkbox_hidden_type_error;
        }

        if (strcmp("checked", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONarray)
                checked = tokens[j].value.a_where;
            else
                goto checkbox_checked_type_error;
        }

    }

    // Construct the checkbox
    {
        
        // Count the number of checkboxes
        for (; labels[label_count]; label_count++);

        // Set the label count
        ret->label_count = label_count;

        // Allocate for the list of labels
        ret->labels  = calloc(label_count, sizeof(char*));
        ret->checked = calloc(label_count, sizeof(bool));
        // Allocate for and copy labels, check states
        for (size_t i = 0; i < label_count; i++)
        {
            char   *l = labels[i];
            size_t  l_len = strlen(l);

            // Keep track of the longest element
            if (longest_label < l_len)
                longest_label = l_len;


            // Allocate for i'th label
            ret->labels[i]  = calloc(l_len + 1, sizeof(u8));
            
            // Copy string
            strncpy(ret->labels[i], l, l_len);

            // Set the checked parameter
            ret->checked[i] = checked[i];
        }

        ret->longest_label = longest_label;

        // Set x
        ret->x = atoi(x);

        // Set y
        ret->y = atoi(y);

        // Set hidden
        ret->hidden = hidden;

    }


    return ret;


    // Error handling
    {
        notACheckbox:
            ui_print_error("[UI] [Checkbox] NOT A CHECKBOX\n");

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
            ui_print_error("[UI] [Checkbox] Null pointer provided for \"tokens\" in call to function \"%s\"\n", __FUNCSIG__);
            return 0;

        no_token_count:
            ui_print_error("[UI] [Checkbox] \"token_count\" is zero in call to function \"%s\"\n", __FUNCSIG__);
            return 0;
        }

        // JSON type errors
        {
        chechbox_type_type_error:
            ui_print_error("[UI] [Checkbox] \"type\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONstring], __FUNCSIG__);
            return 0;
        checkbox_labels_type_error:
            ui_print_error("[UI] [Checkbox] \"labels\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONarray], __FUNCSIG__);
            return 0;
        checkbox_x_type_error:
            ui_print_error("[UI] [Checkbox] \"x\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONprimative], __FUNCSIG__);
            return 0;
        checkbox_y_type_error:
            ui_print_error("[UI] [Checkbox] \"y\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONprimative], __FUNCSIG__);
            return 0;
        checkbox_hidden_type_error:
            ui_print_error("[UI] [Checkbox] \"hidden\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONprimative], __FUNCSIG__);
            return 0;
        checkbox_checked_type_error:
            ui_print_error("[UI] [Checkbox] \"checked\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONarray], __FUNCSIG__);
            return 0;

        }

        // Missing JSON errors
        {
        no_checkbox_name:
            ui_print_error("[UI] [Checkbox] No \"name\" in \"token\" in call to function \"%s\"\n", __FUNCSIG__);
            return 0;
        no_checkbox_text:
            ui_print_error("[UI] [Checkbox] No \"labels\" in \"token\" in call to function \"%s\"\n", __FUNCSIG__);
            return 0;
        no_checkbox_x:
            ui_print_error("[UI] [Checkbox] No \"x\" in \"token\" in call to function \"%s\"\n", __FUNCSIG__);
            return 0;
        no_checkbox_y:
            ui_print_error("[UI] [Checkbox] No \"y\" in \"token\" in call to function \"%s\"\n", __FUNCSIG__);
            return 0;
        }
    }
}

int draw_slider(UIWindow_t* window, UISlider_t* slider)
{
    return 0;
}

int hover_slider(UISlider_t* slider, mouse_state_t mouse_state)
{
    return 0;
}

int click_slider(UISlider_t* slider, mouse_state_t mouse_state)
{
    return 0;
}

int release_slider(UISlider_t* slider, mouse_state_t mouse_state)
{
    return 0;
}

void destroy_slider(UISlider_t* slider)
{
}
