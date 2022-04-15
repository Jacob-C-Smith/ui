#include <UI/UIButton.h>

UIButton_t *create_button              ( void )
{
    // Initialized data
    UIButton_t   *ret    = calloc(1,sizeof(UIButton_t));

    // Check allocated memory, if in debug mode
    {
        #ifndef NDEBUG
            if (ret == (void*)0)
                goto outOfMemory;
        #endif
    }

    return ret;

    // Error handling
    {
    outOfMemory:
        #ifndef NDEBUG
            ui_print_error("[UI] [Button] Failed to create a button; Out of memory\n");
        #endif
        return (void*)0;
    }
}

UIButton_t  *load_button_as_json_tokens ( JSONToken_t *tokens, size_t token_count )
{

    // Argument check
    {
        #ifndef NDEBUG
            if(tokens == (void*)0)
                goto no_tokens;
            if (token_count == 0)
                goto no_token_count;
        #endif
    }

    // Initialized data
    UIButton_t *ret = 0;
    size_t      j   = 0;

    // JSON data
    char *button_text = 0,
         *button_name = 0,
         *button_x    = 0,
         *button_y    = 0;

    // Search through values and pull out relevent information
    for (j = 0; j < token_count; j++)
    {

        // Handle comments
        if      (strcmp("type", tokens[j].key) == 0)
        {

            // Type check
            if (tokens[j].type == JSONstring)
            {
                if (strcmp(tokens[j].value.n_where, "BUTTON") != 0)
                    goto notAButton;
            }
            else
                goto button_type_type_error;
        }
        
        // button label
        else if (strcmp("text", tokens[j].key) == 0)
        {

            // Type check
            if (tokens[j].type == JSONstring)
                button_text = tokens[j].value.n_where;
            else
                goto button_text_type_error;
            continue;
        }

        // x position
        else if (strcmp("x", tokens[j].key) == 0)
        {

            // Type check
            if (tokens[j].type == JSONprimative)
                button_x = tokens[j].value.n_where;
            else
                goto button_x_type_error;

            continue;
        }
        
        // y position
        else if (strcmp("y", tokens[j].key) == 0)
        {

            // Type check
            if (tokens[j].type == JSONprimative)
                button_y = tokens[j].value.n_where;
            else
                goto button_y_type_error;

            continue;
        }

        // unknown token
        else
            ui_print_warning("[UI] [Button] Unknown token encountered when parsing button, token %d/%d\n", j + 1, token_count);
    }

    // Check for important data
    {
        #ifndef NDEBUG
            if (button_text == 0)
                goto no_button_text;
            if (button_x == 0)
                goto no_button_x;
            if (button_y == 0)
                goto no_button_y;
        #endif  
    }

    // Construct the button
    ret = construct_button(button_text, atoi(button_x), atoi(button_y));

    return ret;

    // Error handling
    {
        notAButton:
            ui_print_error("[UI] [Button] NOT A BUTTON\n");
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
                ui_print_error("[UI] [Button] Null pointer provided for \"tokens\" in call to function \"%s\"\n", __FUNCSIG__);
                return 0;

            no_token_count:
                ui_print_error("[UI] [Button] \"token_count\" is zero in call to function \"%s\"\n", __FUNCSIG__);
                return 0;
        }

        // JSON type errors
        {
            button_type_type_error:
                ui_print_error("[UI] [Button] \"type\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONstring], __FUNCSIG__);
                return 0;
            button_text_type_error:
                ui_print_error("[UI] [Button] \"text\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONstring], __FUNCSIG__);
                return 0;
            button_x_type_error:
                ui_print_error("[UI] [Button] \"x\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONprimative], __FUNCSIG__);
                return 0;
            button_y_type_error:
                ui_print_error("[UI] [Button] \"y\" token is of type \"%s\", but should be \"%s\" in call to function \"%s\"\n", token_types[tokens[j].type], token_types[JSONprimative], __FUNCSIG__);
                return 0;
        }

        // Missing JSON errors
        {
            no_button_name:
                ui_print_error("[UI] [Button] No \"name\" in \"token\" in call to function \"%s\"\n", __FUNCSIG__);
                return 0;
            no_button_text:
                ui_print_error("[UI] [Button] No \"text\" in \"token\" in call to function \"%s\"\n", __FUNCSIG__);
                return 0;
            no_button_x:
                ui_print_error("[UI] [Button] No \"x\" in \"token\" in call to function \"%s\"\n", __FUNCSIG__);
                return 0;
            no_button_y:
                ui_print_error("[UI] [Button] No \"y\" in \"token\" in call to function \"%s\"\n", __FUNCSIG__);
                return 0;
        }
    }
}

UIButton_t* construct_button ( char* text, i32 x, i32 y )
{
    // Argument check
    {
        #ifndef NDEBUG
            if(text == (void *)0)
                goto no_text;
        #endif
    }

    UIButton_t *ret = create_button();

    // Construct the button
    {

        // Set the button name
        {
            size_t len = strlen(text);

            ret->text  = calloc(len + 1, sizeof(char));

            // Error checking
            {
                #ifndef NDEBUG
                    if ( ret->text == (void *) 0 )
                        goto no_mem;
                #endif
            }

            strncpy(ret->text, text, len);
        }

        // Set the x location
        ret->x = x;

        // Set the y location
        ret->y = y;
    }

    return ret;

    // Error handling
    {

        // Argument errors
        {
            no_text:
                ui_print_error("[UI] [Button] Null pointer provided for \"text\" in call to function \"%s\"\n", __FUNCSIG__);
                return 0;
        }

        // Standard library errors
        {
            no_mem:
                ui_print_error("[Standard library] Out of memory in call to function \"%s\"\n", __FUNCSIG__);
                return 0;
        }
    }
}

int          hover_button               ( UIButton_t* button, mouse_state_t mouse_state)
{

    // Iterate through callbacks
    for (size_t i = 0; i < button->on_hover_count; i++)
    {
        // Define the callback function
        void (*callback)(UIDropdown_t*, mouse_state_t) = button->on_hover[i];


        // Call the callback function
        if (callback)
            (*callback)(button, mouse_state);

    }

    return 0;
}

int          click_button               ( UIButton_t* button, mouse_state_t mouse_state)
{
    button->depressed = true;

    // Iterate through callbacks
    for (size_t i = 0; i < button->on_click_count; i++)
    {
        // Define the callback function
        void (*callback)(UIDropdown_t*, mouse_state_t) = button->on_click[i];


        // Call the callback function
        if(callback)            
            (*callback)(button, mouse_state);

    }

    return 0;
}

int          release_button             ( UIButton_t* button, mouse_state_t mouse_state )
{
    button->depressed = false;
    return 0;
}

int          add_click_callback_button(UIButton_t* button, void(*callback)(UIButton_t*, mouse_state_t))
{
    // TODO: Argument check

    // If this is the first callback, set the max to 1 and 
    if (button->on_click_max == 0)
    {
        button->on_click_max = 1;
        button->on_click = calloc(1, sizeof(void*));
    }


    // Simple heuristic that doubles callbacks lists length if there is no space to 
    // store the callback pointer
    if (button->on_click_count + 1 > button->on_click_max)
    {
        // Double the max
        button->on_click_max *= 2;

        // Allocate the maximum number of callbacks
        void** callbacks = calloc(button->on_click_max, sizeof(void*)),
            * t = button->on_click;

        // Copy all the callbacks from the button to the new callback list
        memcpy(callbacks, button->on_click, button->on_click_count * sizeof(void*));

        // Set the click callback list pointer to the new list
        button->on_click = callbacks;

        // Free the old callback list
        free(t);
    }

    // Increment the callback counter and install the new callback
    button->on_click[button->on_click_count++] = callback;

    return 0;

    // TODO: Error handling
}

int          add_hover_callback_button  ( UIButton_t* button, void(*callback)(UIButton_t*, mouse_state_t))
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

int          draw_button                ( UIWindow_t* window, UIButton_t* button )
{
    if (button->hidden == true)
        return 0;

    size_t        l        = strlen(button->text);
    UIInstance_t *instance = ui_get_active_instance();
    SDL_Rect      r        = { button->x+1, button->y+1, (l * 8) + 5, 12 };
    
    button->width  = r.w,
    button->height = r.h;

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
    
    ui_draw_text(button->text, window, r.x + 3, r.y + 1, 1);

    return 0;
}

int          destroy_button             ( UIButton_t* button)
{
    free(button);
    return 0;
}
