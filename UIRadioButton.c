#include <UI/UIRadioButton.h>

int create_radio_button(UIRadioButton_t** pp_radio_button)
{
    
    // Argument check
    {
        #ifndef NDEBUG
            if(pp_radio_button == (void *)0)
                goto no_radio_button;
        #endif
    }

    // Allocate a UIRadioButton_s
    UIRadioButton_t* p_radio_button = calloc(1, sizeof(UIRadioButton_t));

    // Check memory
    {
        if(p_radio_button == (void *)0)
            goto no_mem;
    }

    // Return 
    *pp_radio_button = p_radio_button;

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

int load_radio_button_as_dict ( UIRadioButton_t **pp_radio_button, dict *dictionary )
{
    // TODO: Argument check
    {
        #ifndef NDEBUG
            if(pp_radio_button == (void *)0)
                ;// TODO
            if (dictionary == 0)
                goto no_token_count;
        #endif
    }

    // Initialized data
    UIRadioButton_t  *ret           = 0;
    size_t            j             = 0,
                      label_count   = 0,
                      longest_label = 0;
    char            **labels        = 0,
                     *x             = 0,
                     *y             = 0,
                     *index         = 0;

    // Get data for the constructor
    {
        JSONToken_t *token = 0;

        token  = dict_get(dictionary, "labels");
        labels = JSON_VALUE(token, JSONarray);

        token  = dict_get(dictionary, "x");
        x      = JSON_VALUE(token, JSONprimative);

        token  = dict_get(dictionary, "y");
        y      = JSON_VALUE(token, JSONprimative);

        token  = dict_get(dictionary, "index");
        index  = JSON_VALUE(token, JSONprimative);
    }

    construct_radio_button(pp_radio_button, labels, atoi(index), atoi(x), atoi(y));

    return 1;

    // Error handling
    {
        notACheckbox:
        ui_print_error("[UI] [Radio Button] NOT A RADIO_BUTTON\n"); // TODO: Is this "RADIO_BUTTON" or "RADIOBUTTON"?

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
            ui_print_error("[UI] [Checkbox] Null pointer provided for \"tokens\" in call to function \"%s\"\n", __FUNCTION__);
            return 0;

        no_token_count:
            ui_print_error("[UI] [Checkbox] \"token_count\" is zero in call to function \"%s\"\n", __FUNCTION__);
            return 0;
        }



        // Missing JSON errors
        {
        no_checkbox_name:
            ui_print_error("[UI] [Checkbox] No \"name\" in \"token\" in call to function \"%s\"\n", __FUNCTION__);
            return 0;
        no_checkbox_text:
            ui_print_error("[UI] [Checkbox] No \"labels\" in \"token\" in call to function \"%s\"\n", __FUNCTION__);
            return 0;
        no_checkbox_x:
            ui_print_error("[UI] [Checkbox] No \"x\" in \"token\" in call to function \"%s\"\n", __FUNCTION__);
            return 0;
        no_checkbox_y:
            ui_print_error("[UI] [Checkbox] No \"y\" in \"token\" in call to function \"%s\"\n", __FUNCTION__);
            return 0;
        }
    }
}

int construct_radio_button(UIRadioButton_t** radio_button, char** labels, size_t index, i32 x, i32 y)
{
    // TODO: Argument check
    {

    }

    // Initialized data
    UIRadioButton_t *i_radio_button = 0;

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

        dict_construct(&i_radio_button->labels, label_count);

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

int hover_radio_button(UIRadioButton_t* radio_button, ui_mouse_state_t mouse_state)
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

int click_radio_button(UIRadioButton_t* radio_button, ui_mouse_state_t mouse_state)
{
    if (radio_button->hover_index != -1)
        radio_button->index = radio_button->hover_index;

    // Iterate through callbacks
    for (size_t i = 0; i < radio_button->on_click_count; i++)
    {
        // Define the callback function
        void (*callback)(UIRadioButton_t*, ui_mouse_state_t) = radio_button->on_click[i];

        // Call the callback function
        (*callback)(radio_button, mouse_state);

    }

    return 0;
}

int release_radio_button(UIRadioButton_t* radio_button, ui_mouse_state_t mouse_state)
{
    return 0;
}

int add_click_callback_radio_button(UIRadioButton_t* radio_button, void(*callback)(UIRadioButton_t*, ui_mouse_state_t))
{
    return 0;
}

int add_hover_callback_radio_button(UIRadioButton_t* radio_button, void(*callback)(UIRadioButton_t*, ui_mouse_state_t))
{
    return 0;
}

int add_release_callback_radio_button(UIRadioButton_t* radio_button, void(*callback)(UIRadioButton_t*, ui_mouse_state_t))
{
    return 0;
}

int draw_radio_button(UIWindow_t* window, UIRadioButton_t* radio_button)
{
    UIInstance_t* instance = ui_get_active_instance();
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

bool radio_button_in_bounds(UIRadioButton_t* radio_button, ui_mouse_state_t mouse_state)
{
	// Initialized data
	i32  x = radio_button->x,
		 y = radio_button->y,
		 w = radio_button->width,
		 h = radio_button->height;
	
	// Check for bounds
	if (mouse_state.x >= x && mouse_state.y >= y && mouse_state.x <= x + w && mouse_state.y <= y + h)
		return true;

	return false;}

int destroy_radio_button(UIRadioButton_t* radio_button)
{
    return 0;
}
