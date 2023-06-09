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
	UIImage_t   *p_image  = 0;
	JSONValue_t *p_x      = 0,
		        *p_y      = 0,
		        *p_width  = 0,
		        *p_height = 0,
	            *p_path   = 0;

	// Parse JSON
	if ( p_value->type == JSONobject ){

		// Initialized data
		dict *p_dict = p_value->object;

		// Get values for constructing the ui image
		p_x      = dict_get(p_dict, "x");
		p_y      = dict_get(p_dict, "y");
		p_width  = dict_get(p_dict, "width");
		p_height = dict_get(p_dict, "height");
		p_path   = dict_get(p_dict, "path");

	}

	// Construct the UI image
	{

		// Initialized data
		UIInstance_t *p_instance = ui_get_active_instance();
        SDL_Texture  *t          = IMG_LoadTexture(p_instance->load_window->renderer, p_path->string);

		// Error check
		if(t == 0)
		{
			
		}

		// Allocate memory for the UI image
		if ( create_image(&p_image) == 0 )
			goto faield_to_allocate_image;
		
		// Set the image data

		// Set the x
		if ( p_x->type == JSONinteger)
        	p_image->x = p_x->integer;
		// Default
		else
			goto wrong_x_type;

		// Set the y
		if ( p_y->type == JSONinteger)
        	p_image->y = p_y->integer;
		// Default
		else
			goto wrong_y_type;
			
		// Set the width
		if ( p_width->type == JSONinteger)
        	p_image->width = p_width->integer;
		// Default
		else
			goto wrong_width_type;

		// Set the height
		if ( p_height->type == JSONinteger)
        	p_image->height = p_height->integer;
		// Default
		else
			goto wrong_height_type;

        p_image->texture = t;
	}
	
	// Return
	*pp_image = p_image;

	// Success
	return 1;
	wrong_x_type:
	wrong_y_type:
	wrong_width_type:
	wrong_height_type:
		return 0;
		
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
