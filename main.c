// Include the main UI header
#include <UI/UI.h>
#include <UI/UIFileSelector.h>

int click (UILabel_t *p_label, ui_mouse_state_t mouse_state)
{
    /*
    
    */
   return 1;
}

int fun ( UIWindow_t *p_window, char *path )
{

    printf("%s got %s", p_window->title, path);
    return 1;
}

// Entry point
int main ( int argc, const char **argv )
{
    
    // Initialized data
    UIInstance_t *p_ui_instance = 0;
    UIWindow_t   *p_ui_window   = 0;
    UIElement_t  *p_ui_element  = 0;

    // Initialize the UI library
    if ( ui_init(&p_ui_instance, "") == 0 )
        goto failed_to_init_ui;

    // Load a window from the filesystem
    if ( load_window(&p_ui_window, "window.json") == 0 )
        goto failed_to_load_window;

    // Add the window to the instance
    ui_append_window(p_ui_instance, p_ui_window);

    set_file_drop_operation(p_ui_window, &fun);

    // UI Loop
    while ( /* Specify your exit condition, for instance */ p_ui_instance->running )
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