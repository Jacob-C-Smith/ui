#include <UI/UIRadioButton.h>

UIRadioButton_t *create_radio_button              ( void )
{
    // Allocate for a checkbox
    UIRadioButton_t* ret = calloc(1, sizeof(UIRadioButton_t));

    // Check memory
    {
        if(ret == (void *)0)
            goto out_of_memory;
    }

    return ret;

    // Error handling
    {

        // Standard library errors
        {
            out_of_memory:
                ui_print_error("[Standard library] Failed to allocate memory in call to function \"%s\"\n",__FUNCSIG__);
                return 0;
        }
    }
}

UIRadioButton_t *load_radio_button                ( const char   *path )
{
    // Argument check
    {
        #ifndef NDEBUG
            if(path == (void *)0)
                goto no_path;
        #endif
    }

    // Initialized data
    UIRadioButton_t *ret        = 0;
    char            *token_text = 0;
    size_t           token_len  = 0;

    // Load up file
    token_len  = ui_load_file(path, 0, false);
    token_text = calloc(token_len, sizeof(u8));

    // Check memory
    {
        #ifndef NDEBUG
            if(token_text == (void*)0)
                goto out_of_memory;
        #endif
    }

    ui_load_file(path, token_text, false);

    // Construct the checkbox
    ret = 0;// load_radio_button_as_json(token_text);

    free(token_text);

    return ret;

    // Error handling
    {

        // Standard library errors
        {
            out_of_memory:
                ui_print_error("[Standard library] Failed to allocate memory in call to function \"%s\"\n",__FUNCSIG__);
                return 0;
        }

        // Argument errors
        {
            no_path:
                ui_print_error("[UI] [Radio Button] Null pointer provided for \"path\" in call to function \"%s\"\n", __FUNCSIG__);
                return 0;
        }
    }
}

UIRadioButton_t *load_radio_button_as_json_tokens ( JSONToken_t  *tokens  , size_t        token_count)
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
    UIRadioButton_t *ret           = create_radio_button();
    size_t           j             = 0,
                     label_count   = 0,
                     longest_label = 0;
    char           **labels        = 0,
                    *x             = 0,
                    *y             = 0,
                   **checked       = 0;
    bool             hidden        = false;

    // Search through values and pull out relevent information
    for (j = 0; j < token_count; j++)
    {
        if (strcmp("type", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONstring)
                if (strcmp(tokens[j].value.n_where, "RADIOBUTTON") != 0)
                    goto notARadioButton;
        }
        else if (strcmp("name", tokens[j].key) == 0)
            continue;
        if (strcmp("labels", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONarray)
                labels = tokens[j].value.a_where;
            else
                goto radio_button_labels_type_error;

            continue;
        }
        if (strcmp("x", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONprimative)
                x = tokens[j].value.n_where;
            else
                goto radio_button_x_type_error;

            continue;
        }
        if (strcmp("y", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONprimative)
                y = tokens[j].value.n_where;
            else
                goto radio_button_y_type_error;
        }
        if (strcmp("hidden", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONprimative)
                hidden = tokens[j].value.n_where;
            else
                goto radio_button_hidden_type_error;
        }

        if (strcmp("checked index", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONprimative)
                checked = tokens[j].value.n_where;
            else
                goto radio_button_checked_type_error;
        }

    }

    // Construct the checkbox
    {
        
        // Count the number of checkboxes
        for (; labels[label_count]; label_count++);

        // Set the label count
        ret->label_count = label_count;

        // Allocate for the list of labels
        ret->labels        = calloc(label_count, sizeof(char*));
        ret->checked_index = calloc(label_count, sizeof(bool));

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
            ret->checked_index = checked[i];
        }

        ret->longest_label = longest_label;

        // Set x
        ret->x = atoi(x);

        // Set y
        ret->y = atoi(y);

        // Set hidden
        ret->hidden = hidden;

        // Set checked index
        ret->checked_index = atoi(checked);

    }


    return ret;


    // Error handling
    {
        notARadioButton:
            ui_print_error("[UI] [Radio Button] NOT A RADIOBUTTON\n");

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
            ui_print_error("[UI] [Radio Button] Null pointer provided for \"tokens\" in call to function \"%s\"\n", __FUNCSIG__);
            return 0;

        no_token_count:
            ui_print_error("[UI] [Radio Button] \"token_count\" is zero in call to function \"%s\"\n", __FUNCSIG__);
            return 0;
        }

        // JSON type errors
        {
        radio_button_type_type_error:
            ui_print_error("[UI] [Radio Button] \"type\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONstring], __FUNCSIG__);
            return 0;
        radio_button_labels_type_error:
            ui_print_error("[UI] [Radio Button] \"labels\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONarray], __FUNCSIG__);
            return 0;
        radio_button_x_type_error:
            ui_print_error("[UI] [Radio Button] \"x\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONprimative], __FUNCSIG__);
            return 0;
        radio_button_y_type_error:
            ui_print_error("[UI] [Radio Button] \"y\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONprimative], __FUNCSIG__);
            return 0;
        radio_button_hidden_type_error:
            ui_print_error("[UI] [Radio Button] \"hidden\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONprimative], __FUNCSIG__);
            return 0;
        radio_button_checked_type_error:
            ui_print_error("[UI] [Radio Button] \"checked\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONprimative], __FUNCSIG__);
            return 0;

        }

        // Missing JSON errors
        {
        no_radio_button_name:
            ui_print_error("[UI] [Radio Button] No \"name\" in \"token\" in call to function \"%s\"\n", __FUNCSIG__);
            return 0;
        no_radio_button_text:
            ui_print_error("[UI] [Radio Button] No \"labels\" in \"token\" in call to function \"%s\"\n", __FUNCSIG__);
            return 0;
        no_radio_button_x:
            ui_print_error("[UI] [Radio Button] No \"x\" in \"token\" in call to function \"%s\"\n", __FUNCSIG__);
            return 0;
        no_radio_button_y:
            ui_print_error("[UI] [Radio Button] No \"y\" in \"token\" in call to function \"%s\"\n", __FUNCSIG__);
            return 0;
        }
    }
   
}

int           hover_radio_button               ( UIRadioButton_t *checkbox, mouse_state_t mouse_state)
{
    return 0;
}

int           click_radio_button               ( UIRadioButton_t * radio_button, mouse_state_t mouse_state)
{

    // Toggle checkbox selection
    {
        s32 y = mouse_state.y - radio_button->y;

        y /= 15;

        if( y < radio_button->label_count )
            radio_button->checked_index = y;

    }


    // Iterate through callbacks
    for (size_t i = 0; i < radio_button->on_click_count; i++)
    {
        // Define the callback function
        void (*callback)(UIRadioButton_t*, mouse_state_t) = radio_button->on_click[i];

        // Call the callback function
        (*callback)(radio_button, mouse_state);

    }

    return 0;
}

int           change_radio_button              ( UICheckbox_t *checkbox, mouse_state_t mouse_state )
{
    // Iterate through callbacks
    for (size_t i = 0; i < checkbox->on_change_count; i++)
    {
        // Define the callback function
        void (*callback)(UICheckbox_t*, mouse_state_t) = checkbox->on_change[i];

        // Call the callback function
        (*callback)(checkbox, mouse_state);

    }
    return 0;
}

int           draw_radio_button                ( UIWindow_t   *window  , UIRadioButton_t *radio_button )
{

    SDL_Rect r = { radio_button->x, radio_button->y, 12, 12 };
    radio_button->width  = 12,
    radio_button->height = 18 * radio_button->label_count;

    for (size_t i = 0; i < radio_button->label_count; i++)
    {
    
        SDL_SetRenderDrawColor(window->renderer, 0x00, 0x00, 0x00, 0xff);
        ui_draw_circle(5, window, r.x + 6, r.y + 6 );

        if (radio_button->checked_index == i)
            ui_draw_text("\201", window, r.x + 3, r.y + 1, 1);

        ui_draw_text(radio_button->labels[i], window, r.x + 14, r.y + 2, 1);
    
        r.y += 15;

    }
    return 0;

}

int           destroy_radio_button             ( UICheckbox_t *checkbox )
{
    free(checkbox);
    return 0;
}
