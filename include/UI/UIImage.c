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
	// TODO: Argument check

	// Initialzed data
	UIImage_t *ret = create_image();

	// Loop through tokens pulling out relevent information
	for (size_t j = 0; j < token_count; j++)
	{
		if      (strcmp(tokens[j].key, "type")      == 0)
		{
			if (tokens[j].type == JSONstring)
			{
				if (strcmp("IMAGE", tokens[j].value.n_where))
					goto notADropdown;
			}
		}
		else if (strcmp("name", tokens[j].key) == 0)
			continue;
		else if (strcmp(tokens[j].key, "x")         == 0)
		{
			ret->x = 0;
		}
		else if (strcmp(tokens[j].key, "y")         == 0)
		{

		}
		else if (strcmp(tokens[j].key, "width")   == 0)
		{


		}
		else if (strcmp(tokens[j].key, "height")     == 0)
		{

		}
		else if (strcmp(tokens[j].key, "path") == 0)
		{

		}
		else
			ui_print_warning("[UI] [Image] Unknown token encountered when parsing image, token %d / %d\n", j + 1, token_count);
	}

	return ret;

	// TODO: Error handling
	notADropdown:
		ui_print_error("[UI] [Image] NOT AN IMAGE\n");
		return 0;
}

int draw_image(UIImage_t* image)
{
	// TODO: Argument check

	// Initialzed data
	
	return 0;
}

int destroy_image(UIImage_t* image)
{
	return 0;
}
