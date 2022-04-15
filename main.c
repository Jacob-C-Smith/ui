#include <UI/UItypedef.h>
#include <UI/UI.h>
#include <UI/UIDialog.h>

// This will remove the console window on release versions. 
#ifdef NDEBUG
	#define main WinMain
#endif

int main ( int argc, const char *argv[] )
{
	// Blank instance
	UIInstance_t *instance = ui_init(0);

	UIWindow_t   *window   = load_window("UI/UI-Window.json");

	// Load a window
	ui_append_window(instance, window);

	instance->windows->is_open = true;

	// Window loop
	while (instance->windows)
	{
        // Process input
		ui_process_input(instance);

        // Draw the windows
		ui_draw(instance);
	}
	
	// Close everything
	ui_exit(instance);

    return 0;
}