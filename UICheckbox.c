#include <UI/UICheckbox.h>

UICheckbox_t *create_checkbox              ( void )
{
    // Allocate for a checkbox
    UICheckbox_t* ret = calloc(1, sizeof(UICheckbox_t));

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

UICheckbox_t *load_checkbox                ( const char   *path )
{
    // Argument check
    {
        #ifndef NDEBUG
            if(path == (void *)0)
                goto no_path;
        #endif
    }

    // Initialized data
    UICheckbox_t *ret        = 0;
    char         *token_text = 0;
    size_t        token_len  = 0;

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
    ret = 0;// load_checkbox_as_json(token_text);

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
                ui_print_error("[UI] [Checkbox] Null pointer provided for \"path\" in call to function \"%s\"\n", __FUNCSIG__);
                return 0;
        }
    }
}

UICheckbox_t *load_checkbox_as_json_tokens ( JSONToken_t  *tokens  , size_t        token_count)
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

int           hover_checkbox               ( UICheckbox_t *checkbox, mouse_state_t mouse_state)
{
    return 0;
}

int           click_checkbox               ( UICheckbox_t *checkbox, mouse_state_t mouse_state)
{

    // Toggle checkbox selection
    {
        s32 y = mouse_state.y - checkbox->y;

        y /= 15;

        checkbox->checked[y] = (checkbox->checked[y]) ? false : true;
    }

    // Iterate through callbacks
    for (size_t i = 0; i < checkbox->on_click_count; i++)
    {
        // Define the callback function
        void (*callback)(UICheckbox_t*, mouse_state_t) = checkbox->on_click[i];

        // Call the callback function
        (*callback)(checkbox, mouse_state);

    }

    return 0;
}

int           change_checkbox              ( UICheckbox_t *checkbox, mouse_state_t mouse_state )
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

        if (checkbox->checked[i] == true)
            ui_draw_text("\200", window, r.x + 2, r.y + 1, 1);

        ui_draw_text(checkbox->labels[i], window, r.x + 14, r.y + 2, 1);
    
        r.y += 15;

    }
    return 0;

}

int           destroy_checkbox             ( UICheckbox_t *checkbox )
{
    free(checkbox);
    return 0;
}
