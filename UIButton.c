#include <UI/UIButton.h>

UIButton_t* createButton()
{
    // Initialized data
    UIButton_t* ret = calloc(1, sizeof(UIButton_t));

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
            UIPrintError("[UI] [Button] Failed to create a button; Out of memory\n");
        #endif
        return (void*)0;
    }
}

UIButton_t* loadButton ( const char* path )
{
    // Argument check
    {
        #ifndef NDEBUG
        if (path == (void*)0)
            goto noPath;
        #endif
    }

    // Uninitialized data
    u8         *data;
    UIButton_t *ret;

    // Initialized data
    size_t      i    = 0;

    // Load up the file
    i    = UILoadFile(path, 0, false);
    data = calloc(i, sizeof(u8));
    UILoadFile(path, data, false);

    // Parse the JSON into a button
    ret = loadButtonAsJSON(data);

    // Free resources
    free(data);

    return ret;

    // Error handling
    {
    noPath:
        #ifndef NDEBUG
            UIPrintError("[UI] [Button] No path provided to function \"%s\"\n", __FUNCSIG__);
        #endif
        return 0;

    }
}

UIButton_t* loadButtonAsJSON(char* token)
{
    // Initialized data
    UIButton_t* ret = createButton();
    size_t       len = strlen(token),
        tokenCount = parseJSON(token, len, 0, (void*)0);
    JSONToken_t* tokens = calloc(tokenCount, sizeof(JSONToken_t));

    // Parse the JSON
    parseJSON(token, len, tokenCount, tokens);

    // Search through values and pull out relevent information
    for (size_t j = 0; j < tokenCount; j++)
    {
        // Handle comments
        if (strcmp("comment", tokens[j].key) == 0)
        {

        }

        // 
    }
}

int hoverButton(UIButton_t* button, mouse_state_t mouse_state)
{
    return 0;
}

int clickButton(UIButton_t* button, mouse_state_t mouse_state)
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

int releaseButton(UIButton_t* button, mouse_state_t mouse_state)
{
    button->depressed = false;
    return 0;
}

int drawButton(UIWindow_t* window, UIButton_t* button)
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
    
    UIDrawText(button->text, window, r.x + 3, r.y + 1, 1);

    return 0;
}

int destroyButton(UIButton_t* button)
{
    return 0;
}
