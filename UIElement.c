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
    load_button_as_json_value,
    load_checkbox_as_json_value,
    load_dropdown_as_json_value,
    load_image_as_json_value,
    load_label_as_json_value,
    load_radio_button_as_json_value,
    load_slider_as_json_value,
    0,//load_table_as_json_value,
    load_text_input_as_json_value
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
    0,//click_table,
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
    0,//hover_table,
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
    0,//release_table,
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
    0,//add_click_callback_table,
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
    0,//add_hover_callback_table,
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
    0,//add_release_callback_table,
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
    0,//draw_table,
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
    0,//destroy_table,
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
    0,//table_in_bounds,
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
    JSONValue_t *p_type = 0,
                *p_name = 0;

    // Get properties from the dictionary
    if ( p_value->type == JSONobject )
    {

        // Initialized data
        dict *p_dict = p_value->object;

        p_type = dict_get(p_dict, "type");
        p_name = dict_get(p_dict, "name");

        // Check for missing properties
        if ( ! ( p_type && p_name ) )
            goto missing_properties;
    }

    // Construct the element
    if ( p_type->type == JSONstring )
    {
        
        // Initialized data
        int (*constructor)(void*, void*) = dict_get(load_lut, p_type->string);

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
        construct_element(pp_element, p_name->string, p_type->string, p_value);
    }

    // Success
    return 1;

    missing_properties:
        return 0;

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
                    ui_print_error("[UI] [Element] Failed to call constructor for type \"%s\" in call to function \"%s\"\n", p_type->string, __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        no_name:
        no_type:
            return 0;
    }
}

int construct_element(UIElement_t **pp_element, char *p_name, char *p_type, void* element_data)
{
    
    // Argument check
    {
        #ifndef NDEBUG
            if ( element_data == (void *) 0 ) goto no_element_data;
        #endif
    }

    // Initialized data
    UIElement_t *p_element = 0;
    
    // Allocate memory for an element
    if ( create_element(pp_element) == 0 )
        goto failed_to_allocate_element;
    
    // Get a pointer to the element memory
    p_element = *pp_element;

    // Construct the element
    {

        // Initialized data
        char *name = 0,
             *type = 0;
               
        // Set the name
        {

            // Initialized data
            size_t len = strlen(p_name);

            // Allocate memory for the name
            name = calloc(len + 1, sizeof(u8));

            // Error handling
            if ( name == (void *) 0 )
                goto no_mem;

            // Copy the name
            strncpy(name, p_name, len);
        }

        // Set the type
        {

            // Initialized data
            size_t len = strlen(p_type);
            
            // Allocate memory for the name
            type = calloc(len + 1, sizeof(u8));

            // Error handling
            if ( type == (void *) 0 )
                goto no_mem;

            // Copy the type
            strncpy(type, p_type, len);
        }

        // Populate the element
        *p_element = (UIElement_t)
        {
            .name = name,
            .type = type,
            .draw = true,

            // Not really a button. Rather, a pointer to the element 
            .button = element_data
        };
    }

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_element_data:
            invalid_type:
            failed_to_allocate_element:
            no_mem:
                return 0;
        }
    }
}

int click_element(UIElement_t* element, ui_mouse_state_t mouse_state)
{
    UIInstance_t *instnace = ui_get_active_instance();
    
    // Initialized data
    int (*click)(void*, ui_mouse_state_t) = dict_get(click_lut, element->type);

    (*click)((void*)element->label, mouse_state); // Call the element constructor for the specific type
    
    // Set last
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
    int (*add_click_callback)(void*, void(*callback)(UIElement_t*, ui_mouse_state_t)) = dict_get(add_click_lut, element->type);

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

}

int draw_element( UIWindow_t *window, UIElement_t* element )
{
    // TODO: Argument check

    // Construct the element
    if ( element->draw )
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
