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
    UISlider_t   *ret           = create_slider();
    size_t        j             = 0,
                  label_count   = 0,
                  longest_label = 0;
    char         *x             = 0,
                 *y             = 0,
                 *width         = 0,
                 *min           = 0,
                 *max           = 0,
                 *step          = 0;
    bool          hidden        = false;

    // Search through values and pull out relevent information
    for (j = 0; j < token_count; j++)
    {
        if (strcmp("type", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONstring)
                if (strcmp(tokens[j].value.n_where, "SLIDER") != 0)
                    goto notACheckbox;
        }
        else if (strcmp("name", tokens[j].key) == 0)
            continue;
        else if (strcmp("x", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONprimative)
                x = tokens[j].value.n_where;
            else
                goto checkbox_x_type_error;

            continue;
        }
        else if (strcmp("y", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONprimative)
                y = tokens[j].value.n_where;
            else
                goto checkbox_y_type_error;
        }
        else if (strcmp("width", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONprimative)
                width = tokens[j].value.n_where;
            else
                // TODO:
                ;//goto checkbox_width_type_error;
                
        }
        else if (strcmp("min", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONprimative)
                min = tokens[j].value.n_where;
            else
                // TODO:
                ;//goto checkbox_min_type_error;

        }
        else if (strcmp("max", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONprimative)
                max = tokens[j].value.n_where;
            else
                // TODO:
                ;//goto checkbox_max_type_error;

        }
        else if (strcmp("step", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONprimative)
                step = tokens[j].value.n_where;
            else
                // TODO:
                ;//goto checkbox_step_type_error;

        }
    }

    // Construct the checkbox
    {
        
    

        // Set x
        ret->x = atoi(x);

        // Set y
        ret->y = atoi(y);

        // Set width
        ret->width = atoi(width);

        ret->min   = atof(min),
        ret->value = ret->min;
        ret->max   = atof(max);
        ret->step  = atof(step);

        ret->real_step =  ret->width / (ret->step * ret->max);

    }


    return ret;


    // Error handling
    {


        notACheckbox:
            ui_print_error("[UI] [Checkbox] NOT A CHECKBOX\n");

            return 0;

        // Standard library errors
        {

        // *alloc function failed
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

        // The "type" value was of the wrong type
        chechbox_type_type_error:
            ui_print_error("[UI] [Checkbox] \"type\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONstring], __FUNCSIG__);
            return 0;

        // The "labels" value was of the wrong type
        checkbox_labels_type_error:
            ui_print_error("[UI] [Checkbox] \"labels\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONarray], __FUNCSIG__);
            return 0;

        // The "x" value was of the wrong type
        checkbox_x_type_error:
            ui_print_error("[UI] [Checkbox] \"x\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONprimative], __FUNCSIG__);
            return 0;

        // The "y" value was of the wrong type
        checkbox_y_type_error:
            ui_print_error("[UI] [Checkbox] \"y\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONprimative], __FUNCSIG__);
            return 0;

        // The "hidden" value was of the wrong type
        checkbox_hidden_type_error:
            ui_print_error("[UI] [Checkbox] \"hidden\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONprimative], __FUNCSIG__);
            return 0;
        
        // The "checked" value was of the wrong type
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
    UIInstance_t *instance = ui_get_active_instance();

    SDL_SetRenderDrawColor(window->renderer, (u8)instance->primary, (u8)(instance->primary >> 8), (u8)(instance->primary >> 16), 0xff);
    SDL_RenderDrawLine(window->renderer, slider->x, slider->y + 10+12, slider->x + slider->width-4, slider->y + 10+12);
    ui_draw_format_text("\204", window, slider->x + (slider->value * slider->real_step)-8, slider->y+12, 1);

    if (slider->grab)
    {
        if (slider->value > slider->max)
            slider->value = slider->max;
        if (slider->value < slider->min)
            slider->value = slider->min;



    }
    char* s = calloc(32, sizeof(u8));

    sprintf(s, "%g", slider->value);
    ui_draw_format_text(s, window, slider->x + (slider->value * slider->real_step)-8, slider->y, 1);
    free(s);
    return 0;
}

int hover_slider(UISlider_t* slider, mouse_state_t mouse_state)
{
    static i32 lastx = -1,
               lasty = -1;

    // Is the slider being grabbed?
    if (slider->grab)
    {

        // First frame of grab?
        if (lastx == -1 && lasty == -1)
            goto set_last;

        // Change value
        i32 dx = mouse_state.x - lastx;
        
        slider->value += (dx/ slider->real_step);

        // Set last to mouse state
        set_last:
        lastx = mouse_state.x,
        lasty = mouse_state.y;
        
        return 0;
    }
    else {
        lastx = -1,
        lasty = -1;

    }

    return 0;
}

int click_slider(UISlider_t* slider, mouse_state_t mouse_state)
{
    slider->grab = true;
    return 0;
}

int release_slider(UISlider_t* slider, mouse_state_t mouse_state)
{
    slider->grab = false;
    float l = slider->value - fmodf(slider->value, slider->step),
          h = slider->value + fmodf(slider->value, slider->step);

    slider->value = (h - slider->value > l - slider->value) ? l : h;

    return 0;
}

void destroy_slider(UISlider_t* slider)
{

}
