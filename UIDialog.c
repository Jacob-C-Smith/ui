#include <UI\UIDialog.h>

UIWindow_t* construct_dialog_box(char* title, char* prompt, char** options, size_t options_count)
{
	// Argument check
	{
		#ifndef NDEBUG
			if ( title == (void *)0 )
				goto no_title;
			if ( prompt == (void *)0 )
				goto no_prompt;
		#endif
	}

	// Uninitialized data
	UIElement_t *e;

	// Initialized data
	UIWindow_t  *ret        = construct_window(title, 0, 0);
	size_t       title_len  = strlen(title),
		         prompt_len = strlen(prompt),
		         x          = 16,
		         z          = 0;
	UILabel_t   *label      = create_label();
	UIButton_t  *button     = 0;
	
	// Allocate and copy the name of the window
	{
		ret->name = calloc(title_len + 1, sizeof(u8));

		resize_window(ret);

		strncpy(ret->name, title, title_len);
	}

	// Construct and append the label
	{
		label->x              = 16,
		label->y              = 16;
		label->text           = calloc(prompt_len + 1, sizeof(u8));
		strncpy(label->text, prompt, prompt_len);
		z = 32 + (prompt_len * 8);

		// Construct and append the element
		{
			e                = create_element();
			e->name          = label,
			e->type          = UI_LABEL,
			e->element.label = label;
	
			append_element_to_window(ret, e);
		}
	}

	// Construct each option as a button
	for (size_t i = 0; i < options_count; i++)
	{
		// Construct and append the button
		{
			size_t option_len      = strlen(options[i]);

			button                 = create_button();
			button->x              = x,
			button->y              = 32;
			button->text           = calloc(option_len + 1, sizeof(u8));
			strncpy(button->text, options[i], option_len);

			x += (option_len + 2) * 8;

			// Construct and append the element
			{

				// Allocate the element
				e                 = create_element();

				// Set the type and the element
				e->type           = UI_BUTTON,
				e->element.button = button;

				// Set the name
				e->name           = calloc(2,sizeof(u8));
				sprintf(e->name, "%lld", i);
				
				// Append the element to the window
				append_element_to_window(ret, e);
			}
		}
	}
	
	ret->width  = (x > z) ? x : z;
	ret->height = 56;

	resize_window(ret);

	return ret;

	// Error handling
	{
		no_title:
		no_prompt:
		no_options:
		no_option_count:
			return 0;
	}
}

int dialog_box ( char* title, char* prompt, char** options, size_t options_count )
{
	UIWindow_t* window = construct_dialog_box(title, prompt, options, options_count);
		


	return 0;
}
