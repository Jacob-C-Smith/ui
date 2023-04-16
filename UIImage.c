#include <UI/UIImage.h>

int create_image ( UIImage_t **pp_image )
{

	// Argument check
	{
		#ifndef NDEBUG
			if ( pp_image == (void *) 0 )
				goto no_image;
		#endif
	}

	// Initialized data
	UIImage_t *p_image = calloc(1, sizeof(UIImage_t));

	// Error checking
	{
		#ifndef NDEBUG
			if (p_image == (void*)0)
				goto no_mem;
		#endif
	}

	// Return
	*pp_image = p_image;

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_image:
				#ifndef NDEBUG
					ui_print_error("[UI] [Image] Null pointer provided for \"pp_image\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error 
				return 0;
		}

		// Standard Library errors
		{
			no_mem:
				#ifndef NDEBUG
					ui_print_error("[Standard Library] Failed to allocate memory in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error 
				return 0;
		}
	}
}

int load_image_as_json_value (UIImage_t** pp_image, JSONValue_t* p_value)
{

	// Argument check
	{
		#ifndef NDEBUG
			if(pp_image == (void *)0)
				goto no_image;
			if (p_value == (void*)0)
				goto no_value;
		#endif
	}

	// Initialized data
	UIImage_t *p_image = 0;
	signed    *x       = 0,
		      *y       = 0,
		      *width   = 0,
		      *height  = 0;
	char      *path    = 0;

	// Parse JSON
	if ( p_value->type == JSONobject ){

		// Initialized data
		dict *p_dict = p_value->object;

		// Get values for constructing the ui image
		x      = JSON_VALUE(dict_get(p_dict, "x")     , JSONinteger);
		y      = JSON_VALUE(dict_get(p_dict, "y")     , JSONinteger);
		width  = JSON_VALUE(dict_get(p_dict, "width") , JSONinteger);
		height = JSON_VALUE(dict_get(p_dict, "height"), JSONinteger);
		path   = JSON_VALUE(dict_get(p_dict, "path")  , JSONstring);

	}

	// Construct the UI image
	{

		// Initialized data
		UIInstance_t *p_instance = ui_get_active_instance();
        SDL_Texture  *t          = IMG_LoadTexture(p_instance->load_window->renderer, path);

		// Error check
		if(t == 0)
		{
			
		}

		// Allocate memory for the UI image
		if ( create_image(&p_image) == 0 )
			goto faield_to_allocate_image;
		
		// Set the image data
        p_image->x       = x,
        p_image->y       = y,
        p_image->width   = width,
        p_image->height  = height;
        p_image->texture = t;
	}
	
	// Return
	*pp_image = p_image;

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_image:
				#ifndef NDEBUG
					ui_print_error("[UI] [Image] Null pointer provided for \"pp_image\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
			no_value:
				#ifndef NDEBUG
					ui_print_error("[UI] [Image] Null pointer provided for \"p_value\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}

		// TODO:
		faield_to_allocate_image:

		// Insufficent data error
		{
			// TODO: 
			no_text:
			no_x:
			no_y:
				return 0;
		}
	}
}

int click_image(UIImage_t* p_image, ui_mouse_state_t mouse_state)
{
	return 0;
}

int release_image(UIImage_t* p_image, ui_mouse_state_t mouse_state)
{
	return 0;
}

int add_click_callback_image(UIImage_t* p_image, void(*callback)(UIImage_t*, ui_mouse_state_t))
{
	return 0;
}

int add_hover_callback_image(UIImage_t* p_image, void(*callback)(UIImage_t*, ui_mouse_state_t))
{
	return 0;
}

int add_release_callback_image(UIImage_t* p_image, void(*callback)(UIImage_t*, ui_mouse_state_t))
{
	return 0;
}

int hover_image(UIImage_t* p_image, ui_mouse_state_t mouse_state)
{
	return 0;
}

int draw_image ( UIWindow_t *p_window, UIImage_t *p_image )
{

	// Argument check
	{
		#ifndef NDEBUG
			if ( p_window == (void *) 0 )
				goto no_window;
			if ( p_image == (void *) 0 )
				goto no_image;
		#endif
	}

	// Initialzed data
	SDL_Rect texr = {
		              .x = p_image->x,
	                  .y = p_image->y,
					  .w = p_image->width,
					  .h = p_image->height
					};

	// Copy the texture to the window with the renderer
	SDL_RenderCopy(p_window->renderer, p_image->texture, NULL, &texr);

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_window:
				#ifndef NDEBUG
					ui_print_error("[UI] [Image] Null pointer provided for parameter \"p_window\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
			no_image:
				#ifndef NDEBUG
					ui_print_error("[UI] [Image] Null pointer provided for parameter \"p_image\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}

bool image_in_bounds(UIImage_t* p_image, ui_mouse_state_t mouse_state)
{
	// Initialized data
	i32  x = p_image->x,
		 y = p_image->y,
		 w = p_image->width,
		 h = p_image->height;
	
	// Check for bounds
	if (mouse_state.x >= x && mouse_state.y >= y && mouse_state.x <= x + w && mouse_state.y <= y + h)
		return true;

	return false;
}

int destroy_image(UIImage_t **pp_image)
{
	
	// Argument check
	{
		#ifndef NDEBUG
			if ( pp_image == (void *) 0 )
				goto no_image;
		#endif
	}

	// Initialized data
	UIImage_t *p_image = *pp_image;

	// Just exit if p_image is null 
	if ( p_image == (void *) 0 )

		// Error
		return 0;




	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_image:
				#ifndef NDEBUG
					ui_print_error("[UI] [Image] Null pointer provided for parameter \"pp_image\" in call to function \"%s\"\n", __FUNCTION__);
				#endif
				
				// Error
				return 0;
		}
	}
}
