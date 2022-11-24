#include <UI/UIImage.h>

int create_image ( UIImage_t **pp_image )
{
	// Allocate for the image
	UIImage_t* ret = calloc(1, sizeof(UIImage_t));

	*pp_image = ret;

	// Check memory
	return 0;

	// Error handling
	{

		// Standard library errors
		{
			no_mem:
				#ifndef NDEBUG
					ui_print_error("[Standard Library] Failed to allocate memory in call to function \"%s\"\n",__FUNCSIG__);
				#endif
				return 0;
		}
	}
}

int load_image_as_dict(UIImage_t** pp_image, dict* dictioanry)
{
	UIInstance_t *instance = ui_get_active_instance();
	UIImage_t    *image    = 0;

	char         *x        = 0,
		         *y        = 0,
		         *width    = 0,
		         *height   = 0,
		         *path     = 0;

	// Parse JSON
	{
		JSONToken_t *token = 0;

		token  = dict_get(dictioanry, "x");
		x      = JSON_VALUE(token, JSONprimative);

		token  = dict_get(dictioanry, "y");
		y      = JSON_VALUE(token, JSONprimative);

		token  = dict_get(dictioanry, "width");
		width  = JSON_VALUE(token, JSONprimative);

		token  = dict_get(dictioanry, "height");
		height = JSON_VALUE(token, JSONprimative);

		token  = dict_get(dictioanry, "path");
		path   = JSON_VALUE(token, JSONstring);

	}

	create_image(pp_image);
	image = *pp_image;

	// Construct the UI image
	{
        SDL_Texture *t = IMG_LoadTexture(instance->load_window->renderer, path);

        image->x       = atoi(x),
        image->y       = atoi(y),
        image->width   = atoi(width),
        image->height  = atoi(height);
        image->texture = t;
	}

	return 0;
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


int draw_image(UIWindow_t* window, UIImage_t* image)
{
	// TODO: Argument check

	// Initialzed data
	SDL_Rect texr; texr.x = image->x; texr.y = image->y; texr.w = image->width; texr.h = image->height;

	SDL_RenderCopy(window->renderer, image->texture, NULL, &texr);

	return 0;
}

bool image_in_bounds(UIWindow_t* window, ui_mouse_state_t mouse_state)
{
	return 0;
}

int destroy_image(UIImage_t* image)
{
	return 0;
}
