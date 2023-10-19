#include <UI/image.h>

int create_image ( ui_image **pp_image )
{
	
	// Argument check
	if ( pp_image == (void *) 0 ) goto no_image;

	// Initialized data
	ui_image *p_image = calloc(1, sizeof(ui_image));

	// Error checking
	if ( p_image == (void *) 0 ) goto no_mem;

	// Return a pointer to the caller
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

int load_image_as_json_value (ui_image** pp_image, json_value* p_value)
{
	
	// Argument check
	if ( pp_image == (void *) 0 ) goto no_image;
	if ( p_value  == (void *) 0 ) goto no_value;

	// Initialized data
	ui_image  *p_image  = 0;
	json_value *p_x      = 0,
		       *p_y      = 0,
		       *p_width  = 0,
		       *p_height = 0,
	           *p_path   = 0;

	// Parse JSON
	if ( p_value->type == JSON_VALUE_OBJECT )
	{

		// Initialized data
		dict *p_dict = p_value->object;

		// Get values for constructing the ui image
		p_x      = dict_get(p_dict, "x");
		p_y      = dict_get(p_dict, "y");
		p_width  = dict_get(p_dict, "width");
		p_height = dict_get(p_dict, "height");
		p_path   = dict_get(p_dict, "path");

		// TODO: Error check
	}

	// Construct the UI image
	{

		// Initialized data
		ui_instance *p_instance = ui_get_active_instance();
        SDL_Texture  *t          = IMG_LoadTexture(p_instance->load_window->renderer, p_path->string);

		// Error check
		if(t == 0)
		{
			
		}

		// Allocate memory for the UI image
		if ( create_image(&p_image) == 0 ) goto faield_to_allocate_image;
		
		// Set the image data

		// Set the x
		if ( p_x->type == JSON_VALUE_INTEGER)
        	p_image->x = p_x->integer;
		// Default
		else
			goto wrong_x_type;

		// Set the y
		if ( p_y->type == JSON_VALUE_INTEGER)
        	p_image->y = p_y->integer;
		// Default
		else
			goto wrong_y_type;
			
		// Set the width
		if ( p_width->type == JSON_VALUE_INTEGER)
        	p_image->width = p_width->integer;
		// Default
		else
			goto wrong_width_type;

		// Set the height
		if ( p_height->type == JSON_VALUE_INTEGER)
        	p_image->height = p_height->integer;
		// Default
		else
			goto wrong_height_type;

		// Store the texture in the image struct
        p_image->texture = t;
	}
	
	// Return a pointer to the caller
	*pp_image = p_image;

	// Success
	return 1;

	// TODO: 
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

int click_image(ui_image* p_image, ui_mouse_state_t mouse_state)
{

	// TODO: Argument check
	//

	// TODO: 

	return 0;

	// TODO: Error handling
	{

	}
}

int release_image(ui_image* p_image, ui_mouse_state_t mouse_state)
{

	// TODO: Argument check
	//

	// TODO: 

	return 0;

	// TODO: Error handling
	{
		
	}
}

int add_click_callback_image(ui_image* p_image, void(*callback)(ui_image*, ui_mouse_state_t))
{

	// TODO: Argument check
	//

	// TODO: 

	return 0;

	// TODO: Error handling
	{
		
	}
}

int add_hover_callback_image(ui_image* p_image, void(*callback)(ui_image*, ui_mouse_state_t))
{

	// TODO: Argument check
	//

	// TODO: 

	return 0;

	// TODO: Error handling
	{
		
	}
}

int add_release_callback_image(ui_image* p_image, void(*callback)(ui_image*, ui_mouse_state_t))
{

	// TODO: Argument check
	//

	// TODO: 

	return 0;

	// TODO: Error handling
	{
		
	}
}

int hover_image(ui_image* p_image, ui_mouse_state_t mouse_state)
{

	// TODO: Argument check
	//

	// TODO: 

	return 0;

	// TODO: Error handling
	{
		
	}
}

int draw_image ( ui_window *p_window, ui_image *p_image )
{
	
	// Argument check
	if ( p_window == (void *) 0 ) goto no_window;
	if ( p_image  == (void *) 0 ) goto no_image;

	// Initialzed data
	SDL_Rect texr = 
	{
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

bool image_in_bounds(ui_image* p_image, ui_mouse_state_t mouse_state)
{

	// TODO: Argument check
	//

	// Initialized data
	i32  x = p_image->x,
		 y = p_image->y,
		 w = p_image->width,
		 h = p_image->height;
	
	// Check for bounds
	if (mouse_state.x >= x && mouse_state.y >= y && mouse_state.x <= x + w && mouse_state.y <= y + h)

		// In bounds
		return true;
	
	// Out of bounds
	return false;

	// TODO: Error handling
	{

	}
}

int destroy_image(ui_image **pp_image)
{
	
	// Argument check
	if ( pp_image == (void *) 0 ) goto no_image;

	// Initialized data
	ui_image *p_image = *pp_image;

	// TODO: Handle the error
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
