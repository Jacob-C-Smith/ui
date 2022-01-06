#include <UI/UIDropdown.h>

UIDropdown_t *createDropdown()
{
	UIDropdown_t *ret = calloc(1, sizeof(UIDropdown_t));
	// TODO: Check memory

	return ret;
	// TODO: Error handling
}
 
int hoverDropdown(UIDropdown_t* dropdown, mouse_state_t mouse_state)
{
	if ( dropdown->collapsed == false )
	{
		s32 x = mouse_state.x - dropdown->x,
			y = mouse_state.y - dropdown->y-12;

		if (y >= 0)
		{
			dropdown->hover_index = y / 11;
			if (dropdown->hover_index >= dropdown->options_len)
				dropdown->hover_index = dropdown->options_len-1;
			dropdown->index = dropdown->hover_index;
		}
		else
		{
			dropdown->hover_index = -1;
		}
	}
	else
	{
		printf("-\n");
		if (mouse_state.button == UI_SWDOWN)
			printf("--\n");
			

	}

	// Iterate through callbacks
	for (size_t i = 0; i < dropdown->on_hover_count; i++)
	{
		// Define the callback function
		void (*callback)(UIDropdown_t*, mouse_state_t) = dropdown->on_hover;

		// Call the callback function
		(*callback)(dropdown, mouse_state);

	}
	return 0;

}

int clickDropdown ( UIDropdown_t *dropdown, mouse_state_t mouse_state )
{
	// Toggle dropdown
	dropdown->collapsed = (dropdown->collapsed ) ? false : true;

	// Iterate through callbacks
	for (size_t i = 0; i < dropdown->on_click_count; i++)
	{
		// Define the callback function
		void (*callback)(UIDropdown_t *, mouse_state_t) = dropdown->on_click;

		// Call the callback function
		(*callback)(dropdown, mouse_state);

	}
	return 0;
}

int drawDropdown(UIWindow_t* window, UIDropdown_t* dropdown)
{
	// TODO: Argument check

	// Initialized data
	size_t   longest_option_len = 0,
		     current_len        = 0;

	SDL_Rect r                  = { 0, 0, 0, 0 };

	// Determine which dropdown option is the longest
	for ( size_t i = 0; i < dropdown->options_len; i++ )

		if ( dropdown->options[i] )
		{
			current_len = strlen(dropdown->options[i]);
			
			if ( longest_option_len < current_len )
				longest_option_len = current_len;
		}

	// 16 pixels of box drawings plus the string
	r.x = dropdown->x,
	r.y = dropdown->y,
	r.w = (longest_option_len*8)+16,
	r.h = 12;

	dropdown->width  = r.w,
	dropdown->height = r.h;

	SDL_SetRenderDrawColor(window->renderer, 0x00, 0x00, 0x00, 0xff);

	SDL_RenderDrawRect(window->renderer, &r);

	UIDrawText(dropdown->options[dropdown->index], window, r.x + 3, r.y + 1, 1);
	SDL_RenderDrawLine(window->renderer, r.x + r.w - 12, r.y + 2, r.x + r.w - 12, r.y + r.h - 3);

	if ( dropdown->collapsed == false )
	{
		SDL_SetRenderDrawColor(window->renderer, 0x00, 0x00, 0x00, 0xff);
		UIDrawText("\203", window, r.x + r.w - 10, r.y + 1, 1);
		for(size_t i = 0; i < dropdown->options_len; i++ )
		{
			if (i == dropdown->hover_index)
			{
				SDL_Rect s = { r.x + 2, 1 + r.y + (11 * (i + 1)), r.w - 2, 11 };
				SDL_SetRenderDrawColor(window->renderer, 0x00, 0x80, 0xff, 0xff);
				SDL_RenderFillRect(window->renderer, &s);
			}

			SDL_SetRenderDrawColor(window->renderer, 0x00, 0x00, 0x00, 0xff);
			UIDrawText(dropdown->options[i], window, r.x + 5, 1 + r.y + (11 * (i + 1)),1);
			SDL_SetRenderDrawColor(window->renderer, 0x80, 0x80, 0x80, 0xff);
			SDL_RenderDrawLine(window->renderer, r.x + 1, r.y + (11 * (i + 2)), r.x + r.w, r.y + (11 * (i + 2)));
			dropdown->height += 12;
		}
		SDL_RenderDrawLine(window->renderer, r.x + 1, r.y + r.h, r.x + 1, r.y + r.h + (12 * dropdown->options_len) - (dropdown->options_len + 1));
		SDL_RenderDrawLine(window->renderer, r.x + r.w , r.y + 1, r.x + r.w, r.y + r.h + (12 * dropdown->options_len) - (dropdown->options_len + 1));
		
	}
	else
	{
		UIDrawText("\202", window, r.x + r.w - 10, r.y + 1, 1);
	}
	return 0;
}
