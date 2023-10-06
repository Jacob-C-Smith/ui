#include <UI/UISlider.h>

int create_slider ( UISlider_t  **pp_slider )
{

    // Argument check
    if ( pp_slider == (void *) 0 ) goto no_slider;

    // Initialized data
    UISlider_t* p_slider = calloc(1, sizeof(UISlider_t));

    // Error check
    if ( p_slider == (void *) 0 ) goto no_mem;

    // Return a pointer to the caller
    *pp_slider = p_slider;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_slider:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Slider] Null pointer provided for \"pp_slider\" in call to function \"%s\"\n",__FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Standard library errors
        {
            no_mem:
                #ifndef NDEBUG
                    ui_print_error("[Standard library] Failed to allocate memory in call to function \"%s\"\n",__FUNCTION__);
                #endif
                
                // Error
                return 0;
        }
    }
}

int load_slider_as_json_value ( UISlider_t **pp_slider, json_value *p_value )
{

    // Argument errors
    if ( pp_slider == (void *) 0 ) goto no_slider;
    if ( p_value   == (void *) 0 ) goto no_value;

    // Initialized data
    UISlider_t *p_slider = 0;
    signed      x        = 0,
                y        = 0;

    // Parse the slider
    {        
        
        // Initialized data
        dict *p_dict = p_value->object;

        // TODO: Fix
        //x = JSON_VALUE(((json_value *)dict_get(p_dict, "x")), JSON_VALUE_INTEGER);
        //y = JSON_VALUE(((json_value *)dict_get(p_dict, "y")), JSON_VALUE_INTEGER);
    }

    // Is there enough information to construct the slider?
    if ( x == (void *) 0 ) goto no_x;
    if ( y == (void *) 0 ) goto no_y;

    // Allocate the slider
    if ( create_slider(&p_slider) == 0 ) goto failed_to_allocate_slider;
    
    // Construct the slider
    {

        // Set the slider position
        p_slider->x = x;
        p_slider->y = y;
        p_slider->pre = 2;
        p_slider->post = 3;
        p_slider->value = 0;
        p_slider->max = 10.0;
        p_slider->min = 0.0;
    }

    // Return a pointer to the caller
    *pp_slider = p_slider;
    
    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_slider:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Slider] Null pointer provided for \"pp_slider\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_value:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Slider] Null pointer provided for \"p_value\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Missing required construction parameters
        {
            no_label:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Slider] No \"label\" property in \"dictionary\" in call to function \"%s\"\n", __FUNCTION__);
                #endif
                
                // Error
                return 0;
            no_x:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Slider] No \"x\" property in \"dictionary\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_y:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Slider] No \"y\" property in \"dictionary\" in call to function \"%s\"\n", __FUNCTION__);
                #endif
                
                // Error
                return 0;
        }

        // Standard library errors
        {
            no_mem:
                #ifndef NDEBUG
                    ui_print_error("[Standard Library] Failed to allocate memory in call to funciton \"%s\"\n", __FUNCTION__);
                #endif
                
                // Error
                return 0;
        }

        // UI errors
        {
            failed_to_allocate_slider:
                return 0;
        }
    }
}

int hover_slider ( UISlider_t *p_slider, ui_mouse_state_t mouse_state )
{

    // TODO: Argument check
	//

    if ( p_slider->sliding )
        p_slider->value += 1.f;

    // Success
    return 1;

    // TODO: Error handling
}

int click_slider ( UISlider_t *p_slider, ui_mouse_state_t mouse_state )
{

    // TODO: Argument check
	//

    p_slider->sliding = true;

    // Success
    return 1;

    // TOOD: Error handling
}

int release_slider ( UISlider_t *p_slider, ui_mouse_state_t mouse_state )
{

    // TODO: Argument check
	//
    
    p_slider->sliding = false;

    // Success
    return 1;

    // TODO: Error handling

}

int add_click_callback_slider ( UISlider_t *p_slider , void (*callback) ( UISlider_t*, ui_mouse_state_t ) )
{

    // TODO: Argument check
	//

    // TODO:

    // Success
    return 1;
    
    // TODO: Error handling
}

int add_hover_callback_slider ( UISlider_t *p_slider , void (*callback) ( UISlider_t*, ui_mouse_state_t ) )
{

    // TODO: Argument check
	//

    // TODO:

    // Success
    return 1;
    
    // TODO: Error handling
}

int add_release_callback_slider ( UISlider_t *p_slider , void (*callback) ( UISlider_t*, ui_mouse_state_t ) )
{

    // TODO: Argument check
	//

    // TODO:

    // Success
    return 1;
    
    // TODO: Error handling
}

int draw_slider ( UIWindow_t *window, UISlider_t *p_slider )
{

    // TODO: Argument check
	//

    // Initialized data
    UIInstance_t *instance = ui_get_active_instance();
    SDL_Rect      r        = { p_slider->x+1, p_slider->y+1, (8 * 8) + 5, 12 };
    
    p_slider->w = r.w,
    p_slider->h = r.h;

    SDL_SetRenderDrawColor(window->renderer, (u8)instance->primary, (u8)(instance->primary >> 8), (u8)(instance->primary >> 16), 0xff);
    SDL_RenderDrawLine(window->renderer, p_slider->x, p_slider->y+9, p_slider->x+64, p_slider->y+9);

    if(p_slider->sliding)
        ui_draw_format_text("%c%*.*f",window, p_slider->x-4, p_slider->y, 1, (unsigned char)132, p_slider->pre+p_slider->post, p_slider->pre, p_slider->value);
    else
        ui_draw_format_text("%c", window, p_slider->x-4, p_slider->y, 1, (unsigned char)132);

    // Success
    return 1;

    // TODO: Error handling
}

bool slider_in_bounds ( UISlider_t *p_slider , ui_mouse_state_t mouse_state )
{

    // TODO: Argument check
	//

    // Initialized data
	i32  x = p_slider->x,
		 y = p_slider->y,
		 w = p_slider->w,
		 h = p_slider->h;
	
	// Check for bounds
	if ( mouse_state.x >= x && mouse_state.y >= y && mouse_state.x <= x + w && mouse_state.y <= y + h )

        // In bounds
		return true;

    // Update state
    p_slider->sliding = false;

    // Out of bounds
	return false;
}

int destroy_slider ( UISlider_t *p_slider )
{

    // TODO: Argument check
	//

    // Success
    return 1;

    // TODO: Error handling
}