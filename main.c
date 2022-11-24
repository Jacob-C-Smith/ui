#include <stdio.h>

#include <UI/UI.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main ( int argc, const char **argv )
{
    // Initialized data
    UIInstance_t *p_ui_instance = 0;
    UIWindow_t   *p_ui_window   = 0;

    // Initialize the UI library
    ui_init(&p_ui_instance, "");

    // Load a window from the filesystem
    load_window(&p_ui_window, "window.json");

    // Add the window to the instance
    ui_append_window(p_ui_instance, p_ui_window);

    load_window(&p_ui_window, "instance inspector.json");

    // Add the window to the instance
    ui_append_window(p_ui_instance, p_ui_window);

    // Add some callbacks

    // Start running
    p_ui_instance->running = true;

    // Loop
    while (p_ui_instance->running)
    {
        
        // Process input
        ui_process_input(p_ui_instance);

        // Draw windows
        ui_draw(p_ui_instance);
    }

    // Exit the UI library
    ui_exit(p_ui_instance);

    return 1;
}