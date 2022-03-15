#include <stdio.h>

#include <UI/UItypedef.h>
#include <UI/UI.h>
#include <UI/UIWindow.h>

#define main WinMain

int main( int argc, const char *argv[] )
{
	UIInstance_t *instance = ui_init("");
	UIWindow_t   *window   = load_window("UI/UI Window.json");

    instance->windows      = window;

	// Set callbacks
	{
		
	}

	// Window loop
	while (window->is_open)
	{
        // Process input
        process_window_input(window);
       
        // Draw the window
		draw_window(window);
	}

    destroy_window(window);

	ui_exit(instance);

    return 0;
}