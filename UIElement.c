#include <UI/UIElement.h>

UIElement_t* create_element(void)
{
    UIElement_t* ret = calloc(1, sizeof(UIElement_t));
    // TODO: Check memory
    return ret;

    // TODO: Error checking
}

UIElement_t* load_element ( const char* path )
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
    i    = ui_load_file(path, 0, false);
    data = calloc(i, sizeof(u8));
    ui_load_file(path, data, false);

    // Parse the JSON into a button
    ret = load_element_as_json(data);

    // Free resources
    free(data);

    return ret;

    // Error handling
    {
    noPath:
        #ifndef NDEBUG
            ui_print_error("[UI] [Element] No path provided to function \"%s\"\n", __FUNCSIG__);
        #endif
        return 0;

    }
}

UIElement_t* load_element_as_json(char* token_text)
{

    // Initialized data
    UIElement_t *ret         = create_element();
    size_t       len         = strlen(token_text),
                 token_count = parse_json(token_text, len, 0, (void*)0);
    JSONToken_t *tokens      = calloc(token_count, sizeof(JSONToken_t));

    // Parse the JSON
    parse_json(token_text, len, token_count, tokens);

    // Search through values and pull out relevent information
    for (size_t j = 0; j < token_count; j++)
    {

        // Handle type
        if (strcmp("type", tokens[j].key) == 0)

            // Make sure the type of the type token is a string
            if (tokens[j].type == JSONstring)
            {
                if      (strcmp(tokens[j].value.n_where, "BUTTON")       == 0)
                {
                    ret->type           = UI_BUTTON;
                    ret->element.button = load_button_as_json_tokens(tokens, token_count);
                    break;
                }
                else if (strcmp(tokens[j].value.n_where, "CANVAS")       == 0)
                {
                    break;
                }
                else if (strcmp(tokens[j].value.n_where, "CHART")        == 0)
                {
                    break;
                }
                else if (strcmp(tokens[j].value.n_where, "CHECKBOX")     == 0)
                {
                    ret->type = UI_CHECKBOX;
                    ret->element.checkbox = load_checkbox_as_json_tokens(tokens, token_count);
                    break;
                }
                else if (strcmp(tokens[j].value.n_where, "CONTAINER")    == 0)
                {
                    break;
                }
                else if (strcmp(tokens[j].value.n_where, "DROPDOWN")     == 0)
                {
                    ret->type = UI_DROPDOWN;
                    ret->element.dropdown = load_dropdown_as_json_tokens(tokens, token_count);
                    break;
                }
                else if (strcmp(tokens[j].value.n_where, "IMAGE")        == 0)
                {
                    break;
                }
                else if (strcmp(tokens[j].value.n_where, "LABEL")        == 0)
                {
                    ret->type          = UI_LABEL;
                    ret->element.label = load_label_as_json_tokens(tokens, token_count);
                    break;
                }
                else if (strcmp(tokens[j].value.n_where, "RADIO BUTTON") == 0)
                {
                    break;
                }
                else if (strcmp(tokens[j].value.n_where, "SLIDER")       == 0)
                {
                    break;
                }
                else if (strcmp(tokens[j].value.n_where, "TEXT INPUT")   == 0)
                {
                    break;
                }
                else
                    goto badType;
            }
    }


    return ret;

    // TODO: Error handling
    badType:
        ui_print_error("[UI] [Element] Unknown element type encountered.\n");
        return 0;
}

int click_element(UIElement_t* element, mouse_state_t mouse_state)
{
    switch (element->type)
    {
    case UI_BUTTON:
        click_button(element->element.button, mouse_state);
        break;
    case UI_CANVAS:
        // TODO: 
        // draw_canvas(window, element->element.canvas);
        break;
    case UI_CHART:
        // TODO:
        // draw_chart(window, element->element.chart);
        break;
    case UI_CHECKBOX:
        click_checkbox(element->element.checkbox, mouse_state);
        break;
    case UI_DROPDOWN:
        click_dropdown(element->element.dropdown, mouse_state);
        break;
    case UI_IMAGE:
        // TODO:
        // draw_image(window, element->element.image);
        break;
    case UI_LABEL:
        click_label(element->element.label, mouse_state);
        break;
    case UI_RADIOBUTTON:
        // TODO:
        break;
    case UI_SLIDER:
        // TODO:
        break;
    case UI_TEXTINPUT:
        // TODO:

        break;
    }

    return 0;
}

int hover_element(UIElement_t* element, mouse_state_t mouse_state)
{
    switch (element->type)
    {
    case UI_BUTTON:
        hover_button(element->element.button, mouse_state);
        break;
    case UI_CANVAS:
        // TODO: 
        // draw_canvas(window, element->element.canvas);
        break;
    case UI_CHART:
        // TODO:
        // draw_chart(window, element->element.chart);
        break;
    case UI_CHECKBOX:
        hover_checkbox(element->element.checkbox, mouse_state);
        break;
    case UI_DROPDOWN:
        hover_dropdown(element->element.dropdown, mouse_state);
        break;
    case UI_IMAGE:
        // TODO:
        // draw_image(window, element->element.image);
        break;
    case UI_LABEL:
        //hover_label(element->element.label, mouse_state);
        break;
    case UI_RADIOBUTTON:
        // TODO:
        break;
    case UI_SLIDER:
        // TODO:
        break;
    case UI_TEXTINPUT:
        // TODO:

        break;
    }

    return 0;
}

bool in_bounds(UIElement_t* element, mouse_state_t mouse_state)
{

    // TODO: Argument check
    
    // Initialized data
    bool ret = false;
    i32  x = 0,
         y = 0,
         w = 0,
         h = 0;
         
    switch (element->type)
    {
    case UI_BUTTON:
        x = element->element.button->x,
        y = element->element.button->y,
        w = element->element.button->width,
        h = element->element.button->height;
        break;
    case UI_CANVAS:
        // TODO: 
        // draw_canvas(window, element->element.canvas);
        break;
    case UI_CHART:
        // TODO:
        // draw_chart(window, element->element.chart);
        break;
    case UI_CHECKBOX:
        x = element->element.checkbox->x,
        y = element->element.checkbox->y,
        w = element->element.checkbox->width,
        h = element->element.checkbox->height;
        break;
    case UI_DROPDOWN:
        x = element->element.dropdown->x,
        y = element->element.dropdown->y,
        w = element->element.dropdown->width,
        h = element->element.dropdown->height;
        break;
    case UI_IMAGE:
        // TODO:
        // draw_image(window, element->element.image);
        break;
    case UI_LABEL:
        x = element->element.label->x,
        y = element->element.label->y,
        w = element->element.label->width,
        h = element->element.label->height;
        break;
    case UI_RADIOBUTTON:
        // TODO:
        break;
    case UI_SLIDER:
        // TODO:
        break;
    case UI_TEXTINPUT:
        // TODO:

        break;
    }

    if (mouse_state.x >= x && mouse_state.y >= y && mouse_state.x <= x + w && mouse_state.y <= y + h)
        ret = true;

    return ret;

    // TODO: Error handling
}

int draw_element( UIWindow_t *window, UIElement_t* element)
{
    // TODO: Argument check

    switch (element->type)
    {
        case UI_BUTTON:
            draw_button(window, element->element.button);
            break;
        case UI_CANVAS:
            // TODO: 
            // draw_canvas(window, element->element.canvas);
            break;
        case UI_CHART:
            // TODO:
            // draw_chart(window, element->element.chart);
            break;
        case UI_CHECKBOX:
            draw_checkbox(window, element->element.checkbox);
            break;
        case UI_DROPDOWN:
            draw_dropdown(window, element->element.dropdown);
            break;
        case UI_IMAGE:
            // TODO:
            // draw_image(window, element->element.image);
            break;
        case UI_LABEL:
            draw_label(window, element->element.label);
            break;
        case UI_RADIOBUTTON:
            // TODO:
            break;
        case UI_SLIDER:
            // TODO:
            break;
        case UI_TEXTINPUT:
            // TODO:
            
            break;
    }

    return 0;

    // TODO: Error handling
}
