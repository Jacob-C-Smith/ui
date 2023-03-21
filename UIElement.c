#include <UI/UIElement.h>

#define ELEMENT_COUNT 9

char* element_names[ELEMENT_COUNT] =
{
    "BUTTON",
    "CHECKBOX",
    "DROPDOWN",
    "IMAGE",
    "LABEL",
    "RADIO BUTTON",
    "SLIDER",
    "TABLE",
    "TEXT INPUT"
};

void* load_callbacks[ELEMENT_COUNT] =
{
    load_button_as_dict,
    load_checkbox_as_dict,
    load_dropdown_as_dict,
    load_image_as_dict,
    load_label_as_dict,
    load_radio_button_as_dict,
    load_slider_as_dict,
    load_table_as_dict,
    load_text_input_as_dict
};

void* click_callbacks[ELEMENT_COUNT] =
{
    click_button,
    click_checkbox,
    click_dropdown,
    click_image,
    click_label,
    click_radio_button,
    click_slider,
    click_table,
    click_text_input
};

void* hover_callbacks[ELEMENT_COUNT] =
{
    hover_button,
    hover_checkbox,
    hover_dropdown,
    hover_image,
    hover_label,
    hover_radio_button,
    hover_slider,
    hover_table,
    hover_text_input
};

void* release_callbacks[ELEMENT_COUNT] =
{
    release_button,
    release_checkbox,
    release_dropdown,
    release_image,
    release_label,
    release_radio_button,
    release_slider,
    release_table,
    release_text_input
};

void* add_click_callbacks[ELEMENT_COUNT] =
{
    add_click_callback_button,
    add_click_callback_checkbox,
    add_click_callback_dropdown,
    add_click_callback_image,
    add_click_callback_label,
    add_click_callback_radio_button,
    add_click_callback_slider,
    0,
    add_click_callback_text_input
};

void* add_hover_callbacks[ELEMENT_COUNT] =
{
    add_hover_callback_button,
    add_hover_callback_checkbox,
    add_hover_callback_dropdown,
    add_hover_callback_image,
    add_hover_callback_label,
    add_hover_callback_radio_button,
    add_hover_callback_slider,
    0,
    add_hover_callback_text_input
};

void* add_release_callbacks[ELEMENT_COUNT] =
{
    add_release_callback_button,
    add_release_callback_checkbox,
    add_release_callback_dropdown,
    add_release_callback_image,
    add_release_callback_label,
    add_release_callback_radio_button,
    add_release_callback_slider,
    0,
    add_release_callback_text_input
};

void* draw_callback[ELEMENT_COUNT] =
{
    draw_button,
    draw_checkbox,
    draw_dropdown,
    draw_image,
    draw_label,
    draw_radio_button,
    draw_slider,
    draw_table,
    draw_text_input
};

void* destructor_callback[ELEMENT_COUNT] =
{
    destroy_button,
    destroy_checkbox,
    destroy_dropdown,
    destroy_image,
    destroy_label,
    destroy_radio_button,
    destroy_slider,
    0,
    destroy_text_input
};

void* bounds_callback[ELEMENT_COUNT] =
{
    button_in_bounds,
    checkbox_in_bounds,
    dropdown_in_bounds,
    image_in_bounds,
    label_in_bounds,
    radio_button_in_bounds,
    slider_in_bounds,
    table_in_bounds,
    text_input_in_bounds
};

dict *load_lut        = 0;
dict *click_lut       = 0;
dict *hover_lut       = 0;
dict *release_lut     = 0;
dict *add_click_lut   = 0;
dict *add_hover_lut   = 0;
dict *add_release_lut = 0;
dict *draw_lut        = 0;
dict *destructor_lut  = 0;
dict *bounds_lut      = 0;

int init_element ( void )
{

    // Construct a dictionary for each type of callback
    {
        dict_construct(&load_lut       , ELEMENT_COUNT);
        dict_construct(&click_lut      , ELEMENT_COUNT);
        dict_construct(&hover_lut      , ELEMENT_COUNT);
        dict_construct(&release_lut    , ELEMENT_COUNT);
        dict_construct(&add_click_lut  , ELEMENT_COUNT);
        dict_construct(&add_hover_lut  , ELEMENT_COUNT);
        dict_construct(&add_release_lut, ELEMENT_COUNT);
        dict_construct(&draw_lut       , ELEMENT_COUNT);
        dict_construct(&bounds_lut     , ELEMENT_COUNT);
        dict_construct(&destructor_lut , ELEMENT_COUNT);
    }

    // Populate callbacks
    for (size_t i = 0; i < ELEMENT_COUNT; i++)
    {
        dict_add(load_lut       , element_names[i], load_callbacks[i]);
        dict_add(click_lut      , element_names[i], click_callbacks[i]);
        dict_add(hover_lut      , element_names[i], hover_callbacks[i]);
        dict_add(release_lut    , element_names[i], release_callbacks[i]);
        dict_add(add_click_lut  , element_names[i], add_click_callbacks[i]);
        dict_add(add_hover_lut  , element_names[i], add_hover_callbacks[i]);
        dict_add(add_release_lut, element_names[i], add_release_callbacks[i]);
        dict_add(draw_lut       , element_names[i], draw_callback[i]);
        dict_add(bounds_lut     , element_names[i], bounds_callback[i]);
        dict_add(destructor_lut , element_names[i], destructor_callback[i]);
    }

    return 1;
}

int create_element ( UIElement_t **element )
{
    // Argument check
    {
        #ifndef NDEBUG
            if (element == (void *)0)
                goto no_element;
        #endif
    }

    UIElement_t* i_element = calloc(1, sizeof(UIElement_t));
    
    // Check memory
    {
        #ifndef NDEBUG
            if (i_element == (void*)0)
                goto out_of_memory;
        #endif
    }

    *element = i_element;

    return 1;

    // Error checking
    {
        // Argument errors
        {
            no_element:
            #ifndef NDEBUG
                ui_print_error("[UI] [Element] Null pointer provided for \"element\" in call to function \"%s\"\n",__FUNCTION__);
            #endif
            return 0;
        }

        // Standard library errors
        {
            out_of_memory:
                #ifndef NDEBUG
                    ui_print_error("[Standard library] Out of memory in call to function \"%s\"\n",__FUNCTION__);
                #endif
                return 0;
        }
    }
}

int load_element ( UIElement_t **element, const char path[])
{

    // Argument check
    {
        #ifndef NDEBUG
            if (path == (void*)0)
                goto no_path;
            if (element == (void*)0)
                goto no_element;
        #endif
    }

    // Uninitialized data
    u8          *data;
    UIElement_t *i_element;

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
    load_element_as_json(element, data);

    // Free resources
    free(data);

    return 1;

    // Error handling
    {

        // Debug only errors
        {

            #ifndef NDEBUG

                // Argument errors
                {
                    no_path:
                        ui_print_error("[UI] [Element] No path provided to function \"%s\"\n", __FUNCTION__);
                        return 0;     
                    no_element:
                        ui_print_error("[UI] [Element] Null pointer provided for \"element\" in call to function \"%s\"\n",__FUNCTION__);
                        return 0;
                }

                // Standard library errors
                {
                    out_of_memory:
                        ui_print_error("[Standard library] Out of meory in call to function \"%s\"\n", __FUNCTION__);
                        return 0;
                }

            #endif
        }
    }
}

int load_element_as_json(UIElement_t **element, char* token_text)
{
    
    // Argument check
    {
        #ifndef NDEBUG
            if(token_text == (void *)0)
                goto no_token_text;
        #endif  
    }

    // Initialized data
    size_t       len          = strlen(token_text);
    dict        *dictionary   = 0;
    
    char        *type         = 0,
                *name         = 0;
    void        *element_data = 0;

    // Parse the JSON
    parse_json(token_text, len, &dictionary);

    // Get data for the element
    {
        JSONToken_t *token = 0;

        token = dict_get(dictionary, "type");
        type  = JSON_VALUE(token, JSONstring);

        token = dict_get(dictionary, "name");
        name  = JSON_VALUE(token, JSONstring);
    }

    // Error checking
    {
        #ifndef NDEBUG
            if(type == (void *)0)
                goto no_type;
            if(name == (void *)0)
                goto no_name;
        #endif
    }

    // Construct the element
    {
        
        // Initialized data
        int (*constructor)(void*, void*) = dict_get(load_lut, type);

        // Error checking
        {
            #ifndef NDEBUG
                if (constructor == (void *)0)
                    goto not_implemented;
            #endif
        }

        // Call the element constructor for the specific type
        (*constructor)((void*) &element_data, dictionary);

        // Construct the element
        construct_element(element, name, type, element_data);

    }

    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_token_text:
                ui_print_error("[UI] [Element] Null pointer provided for \"token_text\" in call to function \"%s\"\n", __FUNCTION__);
                return 0;
        }

        // Standard library errors
        {
            out_of_memory:
                ui_print_error("[Standard library] Out of meory in call to function \"%s\"\n", __FUNCTION__);
                return 0;
        }

        // Interface errors
        {
            not_implemented:
                ui_print_error("[UI] [Element] Failed to call constructor for type \"%s\" in call to function \"%s\"\n", type, __FUNCTION__);
                return 0;
        }

        no_name:
        no_type:
            return 0;
    }
}

int construct_element(UIElement_t **element, char *name, char *type, void* element_data)
{
    // Argument check
    {
        #ifndef NDEBUG
            if(element_data == (void *)0)
                goto no_element_data;

        #endif
    }

    // Initialized data
    UIElement_t *i_element = 0;
    
    create_element(element);
    
    i_element = *element;

    // Construct the element
    {

        i_element->label = (UIButton_t*)element_data;
                
        // Set the name
        {
            size_t len = strlen(name);
            i_element->name = calloc(len + 1, sizeof(u8));

            // Error handling
            {
                #ifndef NDEBUG
                    if(i_element->name == (void *)0)
                        goto no_mem;
                #endif
            }

            strncpy(i_element->name, name, len);
        }

        // Set the type
        {
            size_t len = strlen(type);
            i_element->type = calloc(len + 1, sizeof(u8));

            // Error handling
            {
                #ifndef NDEBUG
                    if(i_element->type == (void *)0)
                        goto no_mem;
                #endif
            }

            strncpy(i_element->type, type, len);
        }
    }

    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_element_data:
            invalid_type:
            no_mem:
                return 0;
        }
    }
}

int click_element(UIElement_t* element, ui_mouse_state_t mouse_state)
{
    UIInstance_t *instnace = ui_get_active_instance();

    UIWindow_t *w = instnace->active_window;

    // Initialized data
    int (*click)(void*, ui_mouse_state_t) = dict_get(click_lut, element->type);

    (*click)((void*)element->label, mouse_state); // Call the element constructor for the specific type
    
    // Set last
    if(instnace->active_window == w)
        instnace->active_window->last = element;

    return 0;
}

int hover_element(UIElement_t* element, ui_mouse_state_t mouse_state)
{
    // Initialized data
    int (*hover)(void*, ui_mouse_state_t) = dict_get(hover_lut, element->type);

    // Call the element constructor for the specific type
    (*hover)((void*)element->label, mouse_state);


    return 0;
}

int release_element(UIElement_t* element, ui_mouse_state_t mouse_state)
{
    // TODO: Argument check

    // Initialized data
    bool (*release)(void*, ui_mouse_state_t) = dict_get(release_lut, element->type);

    // Call the element constructor for the specific type
    return (*release)((void*)element->label, mouse_state);


    return 0;
}

int add_click_callback_element(UIElement_t* element, void(*callback)(UIElement_t*, ui_mouse_state_t))
{
    // TODO: Argument check

    // Initialized data
    bool (*add_click_callback)(void*, void(*callback)(UIElement_t*, ui_mouse_state_t)) = dict_get(add_click_lut, element->type);

    // Call the element constructor for the specific type
    return (*add_click_callback)((void*)element->label, callback);


    return 0;
}

int add_hover_callback_element(UIElement_t* element, void(*callback)(UIElement_t*, ui_mouse_state_t))
{
    // TODO: Argument check

    // Initialized data
    bool (*add_hover_callback)(void*, void(*callback)(UIElement_t*, ui_mouse_state_t)) = dict_get(add_hover_lut, element->type);

    // Call the element constructor for the specific type
    return (*add_hover_callback)((void*)element->label, callback);

    return 0;
}

int add_release_callback_element(UIElement_t* element, void(*callback)(UIElement_t*, ui_mouse_state_t))
{
    //switch (element->type)
    //{
    //case UI_BUTTON:
    //    add_release_callback_button(element->element.button, callback);
    //    break;
    //case UI_CANVAS:
    //    // TODO: 
    //    break;
    //case UI_CHART:
    //    // TODO:
    //    break;
    //case UI_CHECKBOX:
    //    add_release_callback_checkbox(element->element.checkbox, callback);
    //    break;
    //case UI_DROPDOWN:
    //    add_release_callback_dropdown(element->element.dropdown, callback);
    //    break;
    //case UI_IMAGE:
    //    // TODO:
    //    break;
    //case UI_LABEL:
    //    add_release_callback_label(element->element.label, callback);
    //    break;
    //case UI_RADIOBUTTON:
    //    add_release_callback_radio_button(element->element.radio_button, callback);
    //    break;
    //case UI_SLIDER:
    //    add_release_callback_slider(element->element.slider, callback);
    //    break;
    //case UI_TEXTINPUT:
    //    add_release_callback_text_input(element->element.text_input, callback);
    //    break;
    //}

    return 0;
}

bool in_bounds ( UIElement_t* element, ui_mouse_state_t mouse_state )
{

    // TODO: Argument check
    bool ret = false;
    // Initialized data
    bool (*bounds)(void*, ui_mouse_state_t) = dict_get(bounds_lut, element->type);

    // Call the element constructor for the specific type
    if(bounds)
        ret = (*bounds)((void*)element->label, mouse_state);

    return ret;

    // Initialized data
//    bool ret = false;
//    i32  x = 0,
//         y = 0,
//         w = 0,
//         h = 0;
//         
//    switch (element->type)
//    {
//    case UI_BUTTON:
//        x = element->element.button->x,
//        y = element->element.button->y,
//        w = element->element.button->width,
//        h = element->element.button->height;
//        break;
//    case UI_CANVAS:
//        // TODO: 
//        // draw_canvas(window, element->element.canvas);
//        break;
//    case UI_CHART:
//        // TODO:
//        // draw_chart(window, element->element.chart);
//        break;
//    case UI_CHECKBOX:
//        x = element->element.checkbox->x,
//        y = element->element.checkbox->y,
//        w = element->element.checkbox->width + (8*element->element.checkbox->longest_label),
//        h = element->element.checkbox->height;
//        break;
//    case UI_DROPDOWN:
//        x = element->element.dropdown->x,
//        y = element->element.dropdown->y,
//        w = element->element.dropdown->width,
//        h = element->element.dropdown->height;
//        break;
//    case UI_IMAGE:
//        // TODO:
//        // draw_image(window, element->element.image);
//        break;
//    case UI_LABEL:
//        x = element->element.label->x,
//        y = element->element.label->y,
//        w = element->element.label->width,
//        h = element->element.label->height;
//        break;
//    case UI_RADIOBUTTON:
//        x = element->element.radio_button->x,
//        y = element->element.radio_button->y,
//        w = element->element.radio_button->width + (8 * element->element.radio_button->longest_label),
//        h = element->element.radio_button->height;
//        break;
//    case UI_SLIDER:
//        x = element->element.slider->x,
//        y = element->element.slider->y+12,
//        w = element->element.slider->width,
//        h = 10+12;
//        break;
//    case UI_TEXTINPUT:
//        x = element->element.text_input->x,
//        y = element->element.text_input->y,
//        w = (element->element.text_input->width/8 > element->element.text_input->max_chars) ? element->element.text_input->max_chars*8 : element->element.text_input->width,
//        h = 12;
//
//        break;
//    }
//
//
//    return ret;
//
//    // TODO: Error handling
}

int draw_element( UIWindow_t *window, UIElement_t* element)
{
    // TODO: Argument check

    // Construct the element
    {

        // Initialized data
        int (*drawer)(void*, void*) = dict_get(draw_lut, element->type);

        // Call the element constructor for the specific type
        (*drawer)((void*)window, element->label);

    }

    return 0;

    // TODO: Error handling
}

int destroy_element(UIElement_t* element)
{
    free(element->label);
    free(element->name);
    free(element);

    return 0;
}
