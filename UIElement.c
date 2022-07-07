#include <UI/UIElement.h>

dict *load_lut       = 0;
dict *click_lut      = 0;
dict *hover_lut      = 0;
dict *release_lut    = 0;
dict *draw_lut       = 0;
dict *destructor_lut = 0;
dict *bounds_lut     = 0;

int init_element ( void )
{
    // Construct a dictionary for each type of callback
    {
        dict_construct(&load_lut      , 16);
        dict_construct(&click_lut     , 16);
        dict_construct(&hover_lut     , 16);
        dict_construct(&release_lut   , 16);
        dict_construct(&draw_lut      , 16);
        dict_construct(&bounds_lut    , 16);
        dict_construct(&destructor_lut, 16);
    }

    // Populate callbacks
    {

        // Populate load callbacks
        {
            //dict_add(load_lut, "BUTTON"      , load_button_as_dict);
            //dict_add(load_lut, "CANVAS"      , load_canvas_as_dict);
            dict_add(load_lut, "CHECKBOX"    , load_checkbox_as_dict);
            //dict_add(load_lut, "DROPDOWN"    , load_dropdown_as_dict);
            //dict_add(load_lut, "IMAGE"       , load_image_as_dict);
            dict_add(load_lut, "LABEL", load_label_as_dict);/*
            dict_add(load_lut, "RADIO BUTTON", load_radio_button_as_dict);
            dict_add(load_lut, "SLIDER"      , load_slier_as_dict);
            dict_add(load_lut, "TEXT INPUT"  , load_text_input_as_dict);*/
        }

        // Populate click callbacks
        {
            //dict_add(click_lut, "BUTTON"      , click_button);
            //dict_add(click_lut, "CANVAS"      , click_canvas);
            dict_add(click_lut, "CHECKBOX"    , click_checkbox);
            //dict_add(click_lut, "DROPDOWN"    , click_dropdown);
            //dict_add(click_lut, "IMAGE"       , click_image);
            dict_add(click_lut, "LABEL", click_label);
            //dict_add(click_lut, "RADIO BUTTON", click_radio_button);
            //dict_add(click_lut, "SLIDER"      , click_slier);
            //dict_add(click_lut, "TEXT INPUT"  , click_text_input);
        }

        // Populate hover callbacks
        {
            //dict_add(hover_lut, "BUTTON"      , hover_button);
            //dict_add(hover_lut, "CANVAS"      , hover_canvas);
            dict_add(hover_lut, "CHECKBOX"    , hover_checkbox);
            //dict_add(hover_lut, "DROPDOWN"    , hover_dropdown);
            //dict_add(hover_lut, "IMAGE"       , hover_image);
            dict_add(hover_lut, "LABEL", hover_label);
            //dict_add(hover_lut, "RADIO BUTTON", hover_radio_button);
            //dict_add(hover_lut, "SLIDER"      , hover_slier);
            //dict_add(hover_lut, "TEXT INPUT"  , hover_text_input);
        }

        // Populate release callbacks
        {
            //dict_add(release_lut, "BUTTON"      , release_button);
            //dict_add(release_lut, "CANVAS"      , release_canvas);
            dict_add(release_lut, "CHECKBOX"    , release_checkbox);
            //dict_add(release_lut, "DROPDOWN"    , release_dropdown);
            //dict_add(release_lut, "IMAGE"       , release_image);
            dict_add(release_lut, "LABEL", release_label);
            //dict_add(release_lut, "RADIO BUTTON", release_radio_button);
            //dict_add(release_lut, "SLIDER"      , release_slier);
            //dict_add(release_lut, "TEXT INPUT"  , release_text_input);
        }
    
        // Populate draw callbacks
        {
            //dict_add(draw_lut, "BUTTON"      , draw_button);
            //dict_add(draw_lut, "CANVAS"      , draw_canvas);
            dict_add(draw_lut, "CHECKBOX"    , draw_checkbox);
            //dict_add(draw_lut, "DROPDOWN"    , draw_dropdown);
            //dict_add(draw_lut, "IMAGE"       , draw_image);
            dict_add(draw_lut, "LABEL", draw_label);
            //dict_add(draw_lut, "RADIO BUTTON", draw_radio_button);
            //dict_add(draw_lut, "SLIDER"      , draw_slier);
            //dict_add(draw_lut, "TEXT INPUT"  , draw_text_input);
        }

        // Populate destructor callbacks
        {
            /*dict_add(destructor_lut, "BUTTON"      , destroy_button);
            dict_add(destructor_lut, "CANVAS"      , destroy_canvas);*/
            dict_add(destructor_lut, "CHECKBOX"    , destroy_checkbox);
            /*dict_add(destructor_lut, "DROPDOWN"    , destroy_dropdown);
            dict_add(destructor_lut, "IMAGE"       , destroy_image);*/
            dict_add(destructor_lut, "LABEL"       , destroy_label);
            /*dict_add(destructor_lut, "RADIO BUTTON", destroy_radio_button);
            dict_add(destructor_lut, "SLIDER"      , destroy_slier);
            dict_add(destructor_lut, "TEXT INPUT"  , destroy_text_input);*/
        }
    
        // Populate bound callbacks
        {
        
          /*dict_add(bounds_lut, "BUTTON"      , destroy_button);
            dict_add(bounds_lut, "CANVAS"      , destroy_canvas);*/
            dict_add(bounds_lut, "CHECKBOX"    , checkbox_in_bounds);
            /*dict_add(bounds_lut, "DROPDOWN", destroy_dropdown);
            dict_add(bounds_lut, "IMAGE"       , destroy_image);*/
            dict_add(bounds_lut, "LABEL"       , label_in_bounds);
            /*dict_add(bounds_lut, "RADIO BUTTON", destroy_radio_button);
            dict_add(bounds_lut, "SLIDER"      , destroy_slier);
            dict_add(bounds_lut, "TEXT INPUT"  , destroy_text_input);*/
        }
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
                ui_print_error("[UI] [Element] Null pointer provided for \"element\" in call to function \"%s\"\n",__FUNCSIG__);
            #endif
            return 0;
        }

        // Standard library errors
        {
            out_of_memory:
                #ifndef NDEBUG
                    ui_print_error("[Standard library] Out of memory in call to function \"%s\"\n",__FUNCSIG__);
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
                        ui_print_error("[UI] [Element] No path provided to function \"%s\"\n", __FUNCSIG__);
                        return 0;     
                    no_element:
                        ui_print_error("[UI] [Element] Null pointer provided for \"element\" in call to function \"%s\"\n",__FUNCSIG__);
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
                ui_print_error("[UI] [Element] Null pointer provided for \"token_text\" in call to function \"%s\"\n", __FUNCSIG__);
                return 0;
        }

        // Standard library errors
        {
            out_of_memory:
                ui_print_error("[Standard library] Out of meory in call to function \"%s\"\n", __FUNCSIG__);
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

        i_element->element.label = (UIButton_t*)element_data;
                
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

int click_element(UIElement_t* element, mouse_state_t mouse_state)
{
    // Initialized data
    int (*click)(void*, mouse_state_t) = dict_get(click_lut, element->type);

    // Call the element constructor for the specific type
    (*click)((void*)element->element.label, mouse_state);

    return 0;
}

int hover_element(UIElement_t* element, mouse_state_t mouse_state)
{
    // Initialized data
    int (*hover)(void*, mouse_state_t) = dict_get(hover_lut, element->type);

    // Call the element constructor for the specific type
    (*hover)((void*)element->element.label, mouse_state);


    return 0;
}

int release_element(UIElement_t* element, mouse_state_t mouse_state)
{
    // TODO: Argument check

    // Initialized data
    bool (*release)(void*, mouse_state_t) = dict_get(release_lut, element->type);

    // Call the element constructor for the specific type
    return (*release)((void*)element->element.label, mouse_state);


    return 0;
}

int add_click_callback_element(UIElement_t* element, void(*callback)(UIElement_t*, mouse_state_t))
{
    //switch (element->type)
    //{
    //case UI_BUTTON:
    //    add_click_callback_button(element->element.button, callback);
    //    break;
    //case UI_CANVAS:
    //    // TODO: 
    //    break;
    //case UI_CHART:
    //    // TODO:
    //    break;
    //case UI_CHECKBOX:
    //    add_click_callback_checkbox(element->element.checkbox, callback);
    //    break;
    //case UI_DROPDOWN:
    //    add_click_callback_dropdown(element->element.dropdown, callback);
    //    break;
    //case UI_IMAGE:
    //    // TODO:
    //    break;
    //case UI_LABEL:
    //    add_click_callback_label(element->element.label, callback);
    //    break;
    //case UI_RADIOBUTTON:
    //    add_click_callback_radio_button(element->element.radio_button, callback);
    //    break;
    //case UI_SLIDER:
    //    add_click_callback_slider(element->element.slider, callback);
    //    break;
    //case UI_TEXTINPUT:
    //    add_click_callback_text_input(element->element.text_input, callback);
    //    break;
    //}

    return 0;
}

int add_hover_callback_element(UIElement_t* element, void(*callback)(UIElement_t*, mouse_state_t))
{
    //switch (element->type)
    //{
    //case UI_BUTTON:
    //    add_hover_callback_button(element->element.button, callback);
    //    break;
    //case UI_CANVAS:
    //    // TODO: 
    //    break;
    //case UI_CHART:
    //    // TODO:
    //    break;
    //case UI_CHECKBOX:
    //    add_hover_callback_checkbox(element->element.checkbox, callback);
    //    break;
    //case UI_DROPDOWN:
    //    add_hover_callback_dropdown(element->element.dropdown, callback);
    //    break;
    //case UI_IMAGE:
    //    // TODO:
    //    break;
    //case UI_LABEL:
    //    add_hover_callback_label(element->element.label, callback);
    //    break;
    //case UI_RADIOBUTTON:
    //    add_hover_callback_radio_button(element->element.radio_button, callback);
    //    break;
    //case UI_SLIDER:
    //    add_hover_callback_slider(element->element.slider, callback);
    //    break;
    //case UI_TEXTINPUT:
    //    add_hover_callback_text_input(element->element.text_input, callback);
    //    break;
    //}

    return 0;
}

int add_release_callback_element(UIElement_t* element, void(*callback)(UIElement_t*, mouse_state_t))
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

bool in_bounds ( UIElement_t* element, mouse_state_t mouse_state )
{

    // TODO: Argument check
    
    // Initialized data
    bool (*bounds)(void*, mouse_state_t) = dict_get(bounds_lut, element->type);

    // Call the element constructor for the specific type
    return (*bounds)((void*)element->element.label, mouse_state);

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
        (*drawer)((void*)window, element->element.label);

    }

    return 0;

    // TODO: Error handling
}

int destroy_element(UIElement_t* element)
{
    free(element->element.label);
    free(element->name);
    free(element);

    return 0;
}
