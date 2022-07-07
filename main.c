#include <stdio.h>

#include <UI/UI.h>

int main(int argc, const char** argv)
{
    // Initialized data
    UIInstance_t *ui_instance = 0;
    UIWindow_t   *ui_window   = 0;

    // Initialize the UI library
    ui_init(&ui_instance, "");

    // Load a window from the filesystem
    load_window(&ui_window, "window.json");

    // Add the window to the instance
    ui_append_window(ui_instance, ui_window);

    // Start running
    ui_instance->running = true;

    // Loop
    while (ui_instance->running)
    {

        // Process input
        ui_process_input(ui_instance);

        // Draw windows
        ui_draw(ui_instance);
    }

    // Exit the UI library
    ui_exit(ui_instance);

    return 1;
}