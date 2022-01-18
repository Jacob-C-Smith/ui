#include <UI/UIButton.h>

UIElement_t* create_button()
{
    // Initialized data
    UIElement_t *ret    = create_element();
    ret->element.button = calloc(1, sizeof(UIButton_t));

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

UIButton_t* load_button_as_json_tokens ( JSONToken_t *tokens, size_t token_count )
{
    UIButton_t *ret = create_button();

    // Search through values and pull out relevent information
    for (size_t j = 0; j < token_count; j++)
    {
        // Handle comments
        if (strcmp("type", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONstring)
                if (strcmp(tokens[j].value.n_where, "BUTTON") != 0)
                    goto notAButton;
        }
        else if (strcmp("text", tokens[j].key) == 0)
        {
            size_t len = strlen(tokens[j].value.n_where);

            ret->text = calloc(len + 1, sizeof(char));
            strncpy(ret->text, tokens[j].value.n_where, len);

            continue;
        }
        else if (strcmp("x", tokens[j].key) == 0)
        {
            ret->x = atoi(tokens[j].value.n_where);
            continue;
        }
        else if (strcmp("y", tokens[j].key) == 0)
        {
            ret->y = atoi(tokens[j].value.n_where);
            continue;
        }
        else
            ui_print_warning("[UI] [Button] Unknown token encountered when parsing button, token %d/%d\n", j + 1, token_count);
    }

    return ret;

    // TODO: Error handling
    {
        notAButton:
            ui_print_error("[UI] [Button] NOT A BUTTON\n");
            return 0;
    }
}

int hover_button(UIButton_t* button, mouse_state_t mouse_state)
{
    return 0;
}

int click_button(UIButton_t* button, mouse_state_t mouse_state)
{
    button->depressed = true;

    // Iterate through callbacks
    for (size_t i = 0; i < button->on_click_count; i++)
    {
        // Define the callback function
        void (*callback)(UIDropdown_t*, mouse_state_t) = button->on_click[i];

        // Call the callback function
        (*callback)(button, mouse_state);

    }

    return 0;
}

int release_button ( UIButton_t* button, mouse_state_t mouse_state )
{
    button->depressed = false;
    return 0;
}

int add_hover_callback_button(UIButton_t* button, void(*callback)(UIButton_t*, mouse_state_t))
{
    // TODO: Argument check

    // If this is the first callback, set the max to 1 and 
    if (button->on_click_max == 0)
    {
        button->on_click_max = 1;
        button->on_click     = calloc(1, sizeof(void*));
    }


    // Simple heuristic that doubles callbacks lists length if there is no space to 
    // store the callback pointer
    if (button->on_click_count + 1 > button->on_click_max)
    {
        // Double the max
        button->on_click_max *= 2;

        // Allocate the maximum number of callbacks
        void **callbacks = calloc(button->on_click_max, sizeof(void*)),
              *t         = button->on_click;

        // Copy all the callbacks from the button to the new callback list
        memcpy(callbacks, button->on_click, button->on_click_count * sizeof(void *));

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

int draw_button ( UIWindow_t* window, UIButton_t* button )
{
    size_t   l = strlen(button->text);

    SDL_Rect r = { button->x+1, button->y+1, (l * 8) + 5, 12 };
    
    button->width  = r.w,
    button->height = r.h;

    if (button->depressed==false)
    {
        SDL_SetRenderDrawColor(window->renderer, 0x80, 0x80, 0x80, 0xff);
        SDL_RenderDrawLine(window->renderer, r.x + r.w - 1, r.y, r.x + r.w - 1, r.y + r.h - 1);
        SDL_RenderDrawLine(window->renderer, r.x, r.y + r.h - 1, r.x + r.w - 1, r.y + r.h - 1);
        r.x--, r.y--;
    }

    SDL_SetRenderDrawColor(window->renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderDrawRect(window->renderer, &r);
    
    ui_draw_text(button->text, window, r.x + 3, r.y + 1, 1);

    return 0;
}

int destroy_button(UIButton_t* button)
{
    free(button);
    return 0;
}
