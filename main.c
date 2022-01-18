#include <stdio.h>

#include <UI/UItypedef.h>
#include <UI/UI.h>
#include <UI/UIWindow.h>
#include <UI/UICheckbox.h>

void a(UIButton_t* button, mouse_state_t mouse)
{
    static int i = 0;
    printf("Button Callback %d              \n",++i);

}

int main( int argc, const char *argv[] )
{
	SDL_Event     e;
	UIInstance_t *instance = ui_init("UI/UI default config.json");
	UIWindow_t   *window   = load_window("UI/UI Window.json");

    instance->windows = window;

	SDL_ShowWindow(instance->windows->window);
    window->is_open = true;

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
                    
                    if (keyboardState[SDL_SCANCODE_F2])
                    {
                        destroy_window(window);
                        window = load_window("UI/UI Window.json");
                        instance->windows = window;
                        window->is_open = true;
                    }
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
                }
                break;

                case SDL_MOUSEBUTTONDOWN:
                {
                    mouse_state_t mouse_state = { 0,0,0 };

                    // Create the mouse_state struct
                    {
                        if (e.button.button == SDL_BUTTON_LEFT)
                            mouse_state.button |= UI_M1;
                        if (e.button.button == SDL_BUTTON_MIDDLE)
                            mouse_state.button |= UI_M3;
                        if (e.button.button == SDL_BUTTON_RIGHT)
                            mouse_state.button |= UI_M2;
                        if (e.wheel.y > 0)
                            mouse_state.button |= UI_SWUP;
                        if (e.wheel.y < 0)
                            mouse_state.button |= UI_SWDOWN;
                        mouse_state.x = e.button.x;
                        mouse_state.y = e.button.y;
                    }

                    click_window(instance->windows, mouse_state);
               }
                break;

                case SDL_MOUSEMOTION:
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

                    hover_window(instance->windows, mouse_state);
                }
                break;

                case SDL_WINDOWEVENT:
                    break;
                default:
                    break;
                }
            }
        }

        // Draw the window
		draw_window(window);

        // Present the window
		SDL_RenderPresent(window->renderer);
	}


    destroy_window(window);

	ui_exit(instance);

    return 0;
}