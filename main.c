/** !
 *  UI library example
 * 
 *  @author Jacob Smith
 * 
 *  @file main.c
*/
#include <UI/UI.h>

// Entry point
int main ( int argc, const char **argv )
{
    
    // Initialized data
    ui_instance *p_ui_instance = 0;
    ui_window   *p_ui_window   = 0;
    ui_element  *p_ui_element  = 0;

    // Initialize the UI library
    if ( ui_init(&p_ui_instance, "") == 0 ) goto failed_to_init_ui;

    // Load a window from the filesystem
    if ( load_window(&p_ui_window, "window.json") == 0 ) goto failed_to_load_window;

    // Add the window to the instance
    ui_append_window(p_ui_instance, p_ui_window);

    // UI Loop
    while ( p_ui_instance->running )
    {
        
        // Process input
        ui_process_input(p_ui_instance);

        // Draw windows
        ui_draw(p_ui_instance);
    }

    // Exit the UI library
    ui_exit(p_ui_instance);

    // Success
    return EXIT_SUCCESS;

    // Error handling
    {
        
        // UI Errors
        {
            failed_to_init_ui:
                ui_print_error("[UI] Failed to initialize UI\n");
                return 0;
            failed_to_load_window:
                ui_print_error("[UI] Failed load \"window.json\".\n");
                ui_exit(p_ui_instance);
                return 0;
        }
    }
}