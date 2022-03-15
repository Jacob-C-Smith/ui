#include <UI/UIElement.h>

UIElement_t* create_element ( void )
{
    UIElement_t* ret = calloc(1, sizeof(UIElement_t));
    
    // Check memory
    {
        if (ret == (void*)0)
            goto out_of_memory;
    }

    return ret;

    // Error checking
    {

        // Standard library errors
        {
            out_of_memory:
                ui_print_error("[Standard library] Out of meory in call to function \"%s\"\n",__FUNCSIG__);
                return 0;
        }
    }
}

UIElement_t* load_element ( const char path[])
{

    // Argument check
    {
        #ifndef NDEBUG
        if (path == (void*)0)
            goto no_path;
        #endif
    }

    // Uninitialized data
    u8         *data;
    UIButton_t *ret;

    // Initialized data
    size_t      i    = 0;

    // Load up the file
    i    = ui_load_file(path, 0, false);
    data = calloc(i+1, sizeof(u8));

    // Error checking
    {
        #ifndef NDEBUG
            if(data == (void *) 0)
                goto out_of_memory;
        #endif      
    }

    ui_load_file(path, data, false);

    // Parse the JSON into a button
    ret = load_element_as_json(data);

    // Free resources
    free(data);

    return ret;

    // Error handling
    {

        // Debug only errors
        {

            #ifndef NDEBUG

                // Argument errors
                {
                    no_path:
                        ui_print_error("[UI] [Element] No path provided to function \"%s\"\n", __FUNCSIG__);
                        return 0;           
                }

                // Standard library errors
                {
                    out_of_memory:
                        ui_print_error("[Standard library] Out of meory in call to function \"%s\"\n", __FUNCSIG__);
                        return 0;
                }

            #endif
        }
    }
}

UIElement_t* load_element_as_json(char* token_text)
{
    
    // Argument check
    {
        if(token_text == (void *)0)
            goto no_token_text;
    }

    // Initialized data
    UIElement_t *ret         = create_element();
    size_t       len         = strlen(token_text),
                 token_count = parse_json(token_text, len, 0, (void*)0);
    JSONToken_t *tokens      = calloc(token_count, sizeof(JSONToken_t));

    // Error check
    {
        if (tokens == (void*)0)
            goto out_of_memory;
    }

    // Parse the JSON
    parse_json(token_text, len, token_count, tokens);

    // Search through values and pull out relevent information
    for (size_t j = 0; j < token_count; j++)
    {

        // Handle type
        if (strcmp("type", tokens[j].key) == 0){

            // Make sure the type of the type token is a string
            if (tokens[j].type == JSONstring)
            {
                if      (strcmp(tokens[j].value.n_where, "BUTTON")       == 0)
                {
                    ret->type           = UI_BUTTON;
                    ret->element.button = load_button_as_json_tokens(tokens, token_count);
                    continue;
                }
                else if (strcmp(tokens[j].value.n_where, "CANVAS")       == 0)
                {
                    continue;
                }
                else if (strcmp(tokens[j].value.n_where, "CHART")        == 0)
                {
                    continue;
                }
                else if (strcmp(tokens[j].value.n_where, "CHECKBOX")     == 0)
                {
                    ret->type = UI_CHECKBOX;
                    ret->element.checkbox = load_checkbox_as_json_tokens(tokens, token_count);
                    continue;
                }
                else if (strcmp(tokens[j].value.n_where, "CONTAINER")    == 0)
                {
                    continue;
                }
                else if (strcmp(tokens[j].value.n_where, "DROPDOWN")     == 0)
                {
                    ret->type = UI_DROPDOWN;
                    ret->element.dropdown = load_dropdown_as_json_tokens(tokens, token_count);
                    continue;
                }
                else if (strcmp(tokens[j].value.n_where, "IMAGE")        == 0)
                {
                    continue;
                }
                else if (strcmp(tokens[j].value.n_where, "LABEL")        == 0)
                {
                    ret->type          = UI_LABEL;
                    ret->element.label = load_label_as_json_tokens(tokens, token_count);
                    continue;
                }
                else if (strcmp(tokens[j].value.n_where, "RADIOBUTTON") == 0)
                {
                    ret->type = UI_RADIOBUTTON;
                    ret->element.radio_button = load_radio_button_as_json_tokens(tokens, token_count);
                    continue;
                }
                else if (strcmp(tokens[j].value.n_where, "SLIDER")       == 0)
                {
                    continue;
                }
                else if (strcmp(tokens[j].value.n_where, "TEXT INPUT")   == 0)
                {
                    continue;
                }
                else
                    goto badType;
            }
            else
            {

            }
        }
        else if (strcmp("name",tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONstring)
            {
                size_t len = strlen(tokens[j].value.n_where);
                ret->name  = calloc(len + 1, sizeof(char));
                
                strncpy(ret->name, tokens[j].value.n_where, len);

            }
        }

        if (ret->type && ret->name)
            break;
    }

    free(tokens);

    return ret;

    // Error handling
    {

        // Argument errors
        {
            no_token_text:
                ui_print_error("[UI] [Element] Null pointer provided for \"token_text\" in call to function \"%s\"\n", __FUNCSIG__);
                return 0;
        }

        // Standard library errors
        {
            out_of_memory:
                ui_print_error("[Standard library] Out of meory in call to function \"%s\"\n", __FUNCSIG__);
                return 0;
        }

        badType:
            ui_print_error("[UI] [Element] Unknown element type encountered.\n");
            return 0;
    }
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
        // click_canvas(window, element->element.canvas);
        break;
    case UI_CHART:
        // TODO:
        // click_chart(window, element->element.chart);
        break;
    case UI_CHECKBOX:
        click_checkbox(element->element.checkbox, mouse_state);
        break;
    case UI_DROPDOWN:
        click_dropdown(element->element.dropdown, mouse_state);
        break;
    case UI_IMAGE:
        // TODO:
        // click_image(window, element->element.image);
        break;
    case UI_LABEL:
        click_label(element->element.label, mouse_state);
        break;
    case UI_RADIOBUTTON:
        click_radio_button(element->element.radio_button, mouse_state);
        break;
    case UI_SLIDER:
        // TODO:
        break;
    case UI_TEXTINPUT:
        

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

int release_element(UIElement_t* element, mouse_state_t mouse_state)
{
    switch (element->type)
    {
    case UI_BUTTON:
        release_button(element->element.button, mouse_state);
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
        //hover_checkbox(element->element.checkbox, mouse_state);
        break;
    case UI_DROPDOWN:
        //hover_dropdown(element->element.dropdown, mouse_state);
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
        w = element->element.checkbox->width + (8*element->element.checkbox->longest_label),
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
        x = element->element.radio_button->x,
        y = element->element.radio_button->y,
        w = element->element.radio_button->width + (8 * element->element.radio_button->longest_label),
        h = element->element.radio_button->height;
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
            draw_radio_button(window, element->element.radio_button);
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
