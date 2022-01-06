#include <stdio.h>

#include <UI/UItypedef.h>
#include <UI/UI.h>
#include <UI/UIWindow.h>

void a(UIButton_t* button, mouse_state_t mouse)
{
    printf("Button Callback                \n");
}

int main( int argc, const char *argv[] )
{
	SDL_Event     e;
	UIInstance_t *instance = UIInit("UI/UI default config.json");
	UIWindow_t   *window   = loadWindowAsJSON("");
	UILabel_t    *label    = createLabel();
	UIButton_t   *button   = createButton();
	UIDropdown_t *dropdown = createDropdown();

    instance->windows = window;

	SDL_ShowWindow(instance->windows->window);
    window->is_open = true;
	{
		label->text  = "Label";
		label->x     = 16;
		label->y     = 16;
		
		button->text = "Button";
		button->x    = 16;
		button->y    = 32;

        button->on_click = calloc(1, sizeof(void*));
        button->on_click[0] = &a;
        button->on_click_count = 1;

		dropdown->options_len = 3;
		dropdown->options = calloc(3, sizeof(char*));
		
		for ( size_t i = 0; i < 3; i++ )
			dropdown->options[i] = calloc(1, 11);

		dropdown->index      = 0;

		dropdown->options[0] = "Option 1";
		dropdown->options[1] = "Option 2";
		dropdown->options[2] = "Option 3";

		dropdown->collapsed = true;

		dropdown->x = 16;
		dropdown->y = 48;
	}

	while (window->is_open)
	{
        // Process input
        {
            // Process events
            while (SDL_PollEvent(&e)) {
                switch (e.type)
                {
                case SDL_QUIT:
                {
                    window->is_open = false;
                    
                }
                break;
                case SDL_KEYDOWN:
                {
                    const  u8* keyboardState = SDL_GetKeyboardState(NULL);
                    
                    if (keyboardState[SDL_SCANCODE_F]);

                    if (keyboardState[SDL_SCANCODE_ESCAPE])
                        window->is_open = 0;

                }
                break;

                case SDL_MOUSEBUTTONUP:
                {
                    mouse_state_t mouse_state = { 0,0,0 };

                    if (e.button.button == SDL_BUTTON_LEFT)
                        mouse_state.button |= UI_M1;
                    if (e.button.button == SDL_BUTTON_MIDDLE)
                        mouse_state.button |= UI_M3;
                    if (e.button.button == SDL_BUTTON_RIGHT)
                        mouse_state.button |= UI_M2;
                    if (e.wheel.y > 0)
                    {
                        mouse_state.button |= UI_SWUP;
                    }
                    if (e.wheel.y < 0)
                    {
                        mouse_state.button |= UI_SWDOWN;
                    }
                    mouse_state.x = e.button.x;
                    mouse_state.y = e.button.y;

                    if (mouse_state.x >= button->x)
                        if (mouse_state.x <= (button->x + button->width))
                            if (mouse_state.y >= button->y)
                                if (mouse_state.y <= (button->y + button->height))
                                    releaseButton(button, mouse_state);
                }
                break;
                case SDL_MOUSEBUTTONDOWN:
                {
                    mouse_state_t mouse_state = { 0,0,0 };

                    if (e.button.button == SDL_BUTTON_LEFT)
                        mouse_state.button |= UI_M1;
                    if (e.button.button == SDL_BUTTON_MIDDLE)
                        mouse_state.button |= UI_M3;
                    if (e.button.button == SDL_BUTTON_RIGHT)
                        mouse_state.button |= UI_M2;
                    if (e.wheel.y > 0)
                    {
                        mouse_state.button |= UI_SWUP;
                    }
                    if (e.wheel.y < 0)
                    {
                        mouse_state.button |= UI_SWDOWN;
                    }
                    mouse_state.x = e.button.x;
                    mouse_state.y = e.button.y;

                    if (mouse_state.x >= dropdown->x)
                        if (mouse_state.x <= (dropdown->x + dropdown->width))
                            if (mouse_state.y >= dropdown->y)
                                if (mouse_state.y <= (dropdown->y + dropdown->height))
                                    clickDropdown(dropdown, mouse_state);
                    if (mouse_state.x >= button->x)
                        if (mouse_state.x <= (button->x + button->width))
                            if (mouse_state.y >= button->y)
                                if (mouse_state.y <= (button->y + button->height))
                                    clickButton(button, mouse_state);

                }
                break;

                case SDL_MOUSEMOTION:
                case SDL_MOUSEWHEEL:
                {
                    mouse_state_t mouse_state = {0,0,0};

                    if (e.button.button == SDL_BUTTON_LEFT)
                        mouse_state.button |= UI_M1;
                    if (e.button.button == SDL_BUTTON_RIGHT)
                        mouse_state.button |= UI_M2;
                    if (e.button.button == SDL_BUTTON_MIDDLE)
                        mouse_state.button |= UI_M3;
                    
                    if (e.type == SDL_MOUSEWHEEL)
                    {
                        if (e.wheel.y > 0)
                            mouse_state.button |= UI_SWUP;
                        else if (e.wheel.y < 0)
                            mouse_state.button |= UI_SWDOWN;
                        else;
                    }

                    mouse_state.x = e.button.x;
                    mouse_state.y = e.button.y;
                    printf(" < %d, %d, %x > \r", e.button.x, e.button.y, mouse_state.button);

                    if (mouse_state.x >= dropdown->x)
                        if (mouse_state.x <= (dropdown->x + dropdown->width))
                            if (mouse_state.y >= dropdown->y)
                                if (mouse_state.y <= (dropdown->y + dropdown->height))
                                    hoverDropdown(dropdown, mouse_state);
                }
                break;


                case SDL_WINDOWEVENT:
                    break;
                default:
                    break;
                }
            }
        }


		drawWindow(window);

		drawLabel(window, label);
		drawButton(window, button);
		drawDropdown(window, dropdown);

        

		SDL_RenderPresent(window->renderer);
	}

	UIExit(instance);
}