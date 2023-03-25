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
    0,//load_button_as_json_value,
    0,//load_checkbox_as_json_value,
    0,//load_dropdown_as_json_value,
    0,//load_image_as_json_value,
    load_label_as_json_value,
    0,//load_radio_button_as_json_value,
    0,//load_slider_as_json_value,
    0,//load_table_as_json_value,
    0,//load_text_input_as_djson_value
};

void* click_callbacks[ELEMENT_COUNT] =
{
    0,//click_button,
    0,//click_checkbox,
    0,//click_dropdown,
    0,//click_image,
    click_label,
    0,//click_radio_button,
    0,//click_slider,
    0,//click_table,
    0,//click_text_input
};

void* hover_callbacks[ELEMENT_COUNT] =
{
    0,//hover_button,
    0,//hover_checkbox,
    0,//hover_dropdown,
    0,//hover_image,
    hover_label,
    0,//hover_radio_button,
    0,//hover_slider,
    0,//hover_table,
    0,//hover_text_input
};

void* release_callbacks[ELEMENT_COUNT] =
{
    0,//release_button,
    0,//release_checkbox,
    0,//release_dropdown,
    0,//release_image,
    release_label,
    0,//release_radio_button,
    0,//release_slider,
    0,//release_table,
    0,//release_text_input
};

void* add_click_callbacks[ELEMENT_COUNT] =
{
    0,//add_click_callback_button,
    0,//add_click_callback_checkbox,
    0,//add_click_callback_dropdown,
    0,//add_click_callback_image,
    add_click_callback_label,
    0,//add_click_callback_radio_button,
    0,//add_click_callback_slider,
    0,//0,
    0,//add_click_callback_text_input
};

void* add_hover_callbacks[ELEMENT_COUNT] =
{
    0,//add_hover_callback_button,
    0,//add_hover_callback_checkbox,
    0,//add_hover_callback_dropdown,
    0,//add_hover_callback_image,
    add_hover_callback_label,
    0,//add_hover_callback_radio_button,
    0,//add_hover_callback_slider,
    0,//0,
    0,//add_hover_callback_text_input
};

void* add_release_callbacks[ELEMENT_COUNT] =
{
    0,//add_release_callback_button,
    0,//add_release_callback_checkbox,
    0,//add_release_callback_dropdown,
    0,//add_release_callback_image,
    add_release_callback_label,
    0,//add_release_callback_radio_button,
    0,//add_release_callback_slider,
    0,//0,
    0,//add_release_callback_text_input
};

void* draw_callback[ELEMENT_COUNT] =
{
    0,//draw_button,
    0,//draw_checkbox,
    0,//draw_dropdown,
    0,//draw_image,
    draw_label,
    0,//draw_radio_button,
    0,//draw_slider,
    0,//draw_table,
    0,//draw_text_input
};

void* destructor_callback[ELEMENT_COUNT] =
{
    0,//destroy_button,
    0,//destroy_checkbox,
    0,//destroy_dropdown,
    0,//destroy_image,
    destroy_label,
    0,//destroy_radio_button,
    0,//destroy_slider,
    0,//0,
    0,//destroy_text_input
};

void* bounds_callback[ELEMENT_COUNT] =
{
    0,//button_in_bounds,
    0,//checkbox_in_bounds,
    0,//dropdown_in_bounds,
    0,//image_in_bounds,
    label_in_bounds,
    0,//radio_button_in_bounds,
    0,//slider_in_bounds,
    0,//table_in_bounds,
    0,//text_input_in_bounds
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

int create_element ( UIElement_t **pp_element )
{
    // Argument check
    {
        #ifndef NDEBUG
            if (pp_element == (void *)0)
                goto no_element;
        #endif
    }

    // Initialized data
    UIElement_t *p_element = calloc(1, sizeof(UIElement_t));
    
    // Check memory
    {
        #ifndef NDEBUG
            if (p_element == (void*)0)
                goto out_of_memory;
        #endif
    }

    // Return
    *pp_element = p_element;

    // Success
    return 1;

    // Error checking
    {

        // Argument errors
        {
            no_element:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Element] Null pointer provided for \"element\" in call to function \"%s\"\n",__FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Standard library errors
        {
            out_of_memory:
                #ifndef NDEBUG
                    ui_print_error("[Standard library] Out of memory in call to function \"%s\"\n",__FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int load_element_as_json_value(UIElement_t **pp_element, JSONValue_t *p_value)
{
    
    // Argument check
    {
        #ifndef NDEBUG
            if(p_value == (void *)0)
                goto no_value;
        #endif  
    }

    // Initialized data
    dict        *dictionary   = 0;
    
    char        *type         = 0,
                *name         = 0;

    // Get properties from the dictionary
    if (p_value->type == JSONobject)
    {

        // Initialized data
        dict *p_dict = p_value->object;

        type = JSON_VALUE(((JSONValue_t *)dict_get(p_dict, "type")), JSONstring);
        name = JSON_VALUE(((JSONValue_t *)dict_get(p_dict, "name")), JSONstring);
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
        (*constructor)((void*) &p_value, p_value);

        // Construct the element
        construct_element(pp_element, name, type, p_value);

    }

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_value:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Element] Null pointer provided for \"p_value\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Standard library errors
        {
            out_of_memory:
                #ifndef NDEBUG
                    ui_print_error("[Standard library] Failed to allocate memory in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Interface errors
        {
            not_implemented:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Element] Failed to call constructor for type \"%s\" in call to function \"%s\"\n", type, __FUNCTION__);
                #endif

                // Error
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

    // Success
    return 1;

    // TODO: Error handling
}

int destroy_element(UIElement_t **pp_element)
{

    // Argument check
    {
        #ifndef NDEBUG
            if ( pp_element == (void *) 0 ) 
                goto no_element;
        #endif
    }
    
    // Initialized data
    UIElement_t *p_element = *pp_element;
    
    // Free the element
    free(p_element->label);
    free(p_element->name);
    free(p_element);

    // Success
    return 1;

    // Error handling
    {
        
        // Argument errors
        {
            no_element:
                #ifndef NDEBUG
                    printf("[UI] [Element] Null pointer provided for \"pp_element\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}
