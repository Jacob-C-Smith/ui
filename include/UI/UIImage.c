#include <UI/UIImage.h>

UIImage_t* create_image(void)
{
	// Allocate for the image
	UIImage_t* ret = calloc(1, sizeof(UIImage_t));

	// Check memory
	return ret;

	// Error handling
	{

		// Standard library errors
		{

			// Out of memory
			out_of_memory:
				ui_print_error("[UI] [Image] Failed to allocate memory for \"UIImage\" in call to function \"%s\"\n",__FUNCSIG__);
				return 0;
		}
	}
}

UIImage_t* load_image(const char path[])
{
	UIImage_t *ret        = 0;
	char      *token_text = 0;

	//ret = load_image_as_json_tokens(token_text);

	return ret;
}

UIImage_t* load_image_as_json_tokens(JSONToken_t* tokens, size_t token_count)
{

	return 0;
}

int draw_image(UIImage_t* image)
{
	return 0;
}

int destroy_image(UIImage_t* image)
{
	return 0;
}
