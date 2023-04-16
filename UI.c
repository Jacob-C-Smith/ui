#include <UI/UI.h>

// Each u64 encodes an 8x8 glyph. ASCII values can be used to index characters. Add whatever you want so long as you keep the length under 255
u64 font[133] = {
    0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
    0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
    0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
    0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
    0x0000000000000000, 0x183C3C1818001800, 0x3636000000000000, 0x36367F367F363600, 0x0C3E031E301F0C00, 0x006333180C666300, 0x1C361C6E3B336E00, 0x0606030000000000,
    0x180C0606060C1800, 0x060C1818180C0600, 0x00663CFF3C660000, 0x000C0C3F0C0C0000, 0x00000000000C0C06, 0x0000003F00000000, 0x00000000000C0C00, 0x6030180C06030100,
    0x3E63737B6F673E00, 0x0C0E0C0C0C0C3F00, 0x1E33301C06333F00, 0x1E33301C30331E00, 0x383C36337F307800, 0x3F031F3030331E00, 0x1C06031F33331E00, 0x3F3330180C0C0C00,
    0x1E33331E33331E00, 0x1E33333E30180E00, 0x000C0C00000C0C00, 0x000C0C00000C0C06, 0x180C0603060C1800, 0x00003F00003F0000, 0x060C1830180C0600, 0x1E3330180C000C00,
    0x3E637B7B7B031E00, 0x0C1E33333F333300, 0x3F66663E66663F00, 0x3C66030303663C00, 0x1F36666666361F00, 0x7F46161E16467F00, 0x7F46161E16060F00, 0x3C66030373667C00,
    0x3333333F33333300, 0x1E0C0C0C0C0C1E00, 0x7830303033331E00, 0x6766361E36666700, 0x0F06060646667F00, 0x63777F7F6B636300, 0x63676F7B73636300, 0x1C36636363361C00,
    0x3F66663E06060F00, 0x1E3333333B1E3800, 0x3F66663E36666700, 0x1E33070E38331E00, 0x3F2D0C0C0C0C1E00, 0x3333333333333F00, 0x33333333331E0C00, 0x6363636B7F776300,
    0x6363361C1C366300, 0x3333331E0C0C1E00, 0x7F6331184C667F00, 0x1E06060606061E00, 0x03060C1830604000, 0x1E18181818181E00, 0x081C366300000000, 0x00000000000000FF,
    0x0C0C180000000000, 0x00001E303E336E00, 0x0706063E66663B00, 0x00001E3303331E00, 0x3830303e33336E00, 0x00001E333f031E00, 0x1C36060f06060F00, 0x00006E33333E301F,
    0x0706366E66666700, 0x0C000E0C0C0C1E00, 0x300030303033331E, 0x070666361E366700, 0x0E0C0C0C0C0C1E00, 0x0000337F7F6B6300, 0x00001F3333333300, 0x00001E3333331E00,
    0x00003B66663E060F, 0x00006E33333E3078, 0x00003B6E66060F00, 0x00003E031E301F00, 0x080C3E0C0C2C1800, 0x0000333333336E00, 0x00003333331E0C00, 0x0000636B7F7F3600,
    0x000063361C366300, 0x00003333333E301F, 0x00003F190C263F00, 0x380C0C070C0C3800, 0x1818180018181800, 0x070C0C380C0C0700, 0x6E3B000000000000, 0x0000000000000000,
    0x80C0E070371E1C08, 0x00001c3e3e3e1c00, 0x040C1C3C3C1C0C04, 0x0000ff4224180000, 0x7E7E7E7E7E7E3C18};

char *default_config = "{\n\t\"name\"       : \"Default color theme\",\n\t\"primary\"    : [ 0, 0, 0 ],\n\t\"accent 1\"   : [ 128, 128, 128 ],\n\t\"accent 2\"   : [ 192, 192, 192 ],\n\t\"accent 3\"   : [ 0, 128, 255 ],\n\t\"background\" : [ 255, 255, 255 ]\n}\n";
char *config_file_name = "/ui_config.json";
UIInstance_t *active_instance = 0;

int ui_init(UIInstance_t **pp_instance, const char *path)
{

    // Argument check
    {
        #ifndef NDEBUG
            if (pp_instance == (void *)0)
                goto no_instance;
            if (path == (void *)0)
                goto no_path;
        #endif
    }

    // Uninitialized data
    FILE *config_file;

    // Initialized data
    UIInstance_t *p_instance       = 0;
    char         *appdata          = 0;
    size_t        appdata_len      = 0;
    char         *config_path      = 0,
                 *config_file_data = 0;
    array        *primary          = 0,
                 *accent_1         = 0,
                 *accent_2         = 0,
                 *accent_3         = 0,
                 *background       = 0;
    dict         *config_file_json = 0;
    size_t        config_file_len  = 0;
    JSONValue_t  *p_value          = 0;

    // Find a directory for the config file
    {

        // Find a directoroy using environment variables
        #ifdef _WIN64
            appdata = getenv("APPDATA");
        #else
            appdata = getenv("HOME");
        #endif

        // Compute the length of the path
        appdata_len = strlen(appdata) + strlen(config_file_name);

        // Allocate memory for the path
        config_path = calloc(appdata_len + 1, sizeof(u8));
    }

    // Error checking
    {
        if (appdata == 0)
            goto no_app_data;
    }

    // Construct the path to the config file
    sprintf(config_path, "%s/%s", appdata, config_file_name);

    created_config_file:
    // Load the config file
    {
        config_file_len = ui_load_file(config_path, 0, false);

        // Error checking
        {
            if (config_file_len == 0)
                goto no_config_file;
        }

        config_file_data = calloc(config_file_len, sizeof(u8));
        ui_load_file(config_path, config_file_data, false);
    }

    // Parse the config file into a dictionary
    if (parse_json_value(config_file_data, 0, &p_value) == 0)
        goto failed_to_parse_json;

    // Get properties from the dictionary
    if (p_value->type == JSONobject)
    {

        // Initialized data
        dict *p_dict = p_value->object;

        primary    = JSON_VALUE(((JSONValue_t *)dict_get(p_dict, "primary"))   , JSONarray);
        accent_1   = JSON_VALUE(((JSONValue_t *)dict_get(p_dict, "accent 1"))  , JSONarray);
        accent_2   = JSON_VALUE(((JSONValue_t *)dict_get(p_dict, "accent 2"))  , JSONarray);
        accent_3   = JSON_VALUE(((JSONValue_t *)dict_get(p_dict, "accent 3"))  , JSONarray);
        background = JSON_VALUE(((JSONValue_t *)dict_get(p_dict, "background")), JSONarray);
    }

    // Construct the instance
    {

        // Allocate memory for the instance
        p_instance = calloc(1, sizeof(UIInstance_t));

        // Error check
        {
            #ifndef NDEBUG
                if (p_instance == (void *)0)
                    goto no_mem;
            #endif
        }

        // Initialize SDL
        {
            // Fixes blurry rendering on Mac OS
            #ifdef __APPLE__
                SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
            #endif

            // Initialize SDL
            SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        }

        // Set the theme colors
        {

            // Set the primary color
            {

                // Initialized data
                size_t array_len = 0;
                JSONValue_t *pp_array[3] = {0, 0, 0};

                // Get the length of the array
                array_get(primary, 0, &array_len);

                // Check for a valid array length
                if (array_len != 3)
                    goto failed_primary;

                // Get the R, G, and B values
                array_get(primary, pp_array, &array_len);

                // Iterate over each color
                for (size_t i = 0; i < array_len; i++)
                {

                    // Set the color
                    p_instance->primary |= pp_array[i]->integer << (i * 8);
                }

                // Opaque
                p_instance->primary |= 0xff000000;
            }

            // Set accent color 1
            {

                // Initialized data
                size_t array_len = 0;
                JSONValue_t *pp_array[3] = {0, 0, 0};

                // Get the length of the array
                array_get(accent_1, 0, &array_len);

                // Check for a valid array length
                if (array_len != 3)
                    goto failed_accent_1;

                // Get the R, G, and B values
                array_get(accent_1, pp_array, &array_len);

                // Iterate over each color
                for (size_t i = 0; i < array_len; i++)
                {

                    // Set the color
                    p_instance->accent_1 |= pp_array[i]->integer << (i * 8);
                }

                // Opaque
                p_instance->accent_1 |= 0xff000000;
            }

            // Set accent color 2
            {

                // Initialized data
                size_t array_len = 0;
                JSONValue_t *pp_array[3] = {0, 0, 0};

                // Get the length of the array
                array_get(accent_2, 0, &array_len);

                // Check for a valid array length
                if (array_len != 3)
                    goto failed_accent_2;

                // Get the R, G, and B values
                array_get(accent_2, pp_array, &array_len);

                // Iterate over each color
                for (size_t i = 0; i < array_len; i++)
                {

                    // Set the color
                    p_instance->accent_2 |= pp_array[i]->integer << (i * 8);
                }

                // Opaque
                p_instance->accent_2 |= 0xff000000;
            }

            // Set accent color 3
            {

                // Initialized data
                size_t array_len = 0;
                JSONValue_t *pp_array[3] = {0, 0, 0};

                // Get the length of the array
                array_get(accent_3, 0, &array_len);

                // Check for a valid array length
                if (array_len != 3)
                    goto failed_accent_3;

                // Get the R, G, and B values
                array_get(accent_3, pp_array, &array_len);

                // Iterate over each color
                for (size_t i = 0; i < array_len; i++)
                {

                    // Set the color
                    p_instance->accent_3 |= pp_array[i]->integer << (i * 8);
                }

                // Opaque
                p_instance->accent_3 |= 0xff000000;
            }

            // Set background
            {

                // Initialized data
                size_t array_len = 0;
                JSONValue_t *pp_array[3] = {0, 0, 0};

                // Get the length of the array
                array_get(background, 0, &array_len);

                // Check for a valid array length
                if (array_len != 3)
                    goto failed_background;

                // Get the R, G, and B values
                array_get(background, pp_array, &array_len);

                // Iterate over each color
                for (size_t i = 0; i < array_len; i++)
                {

                    // Set the color
                    p_instance->background |= pp_array[i]->integer << (i * 8);
                }

                // Opaque
                p_instance->background |= 0xff000000;
            }
        }

        // Set the running flag
        p_instance->running = true;
    }

    // Initialize UI subsystems
    {

        // Initialize the window system
        {

            // Construct a dictionary for windows
            dict_construct(&p_instance->windows, MAX_WINDOW_COUNT);

            // Allocate a list of windows
            p_instance->windows_list = calloc(MAX_WINDOW_COUNT, sizeof(UIWindow_t *));
        }

        // Initialize the element system
        {
            extern int init_element( void );
            init_element();
        }
    }

    // Set the active instance
    active_instance = p_instance;

    // Return
    *pp_instance = p_instance;

    // Clean up
    free_json_value(p_value);

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_instance:
                #ifndef NDEBUG
                    ui_print_error("[UI] Null pointer provided for \"pp_instance\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_path:
                #ifndef NDEBUG
                    ui_print_error("[UI] Null pointer provided for \"path\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // User errors
        // Create a config file
        no_config_file:
        {

            // Open the file
            config_file = fopen(config_path, "w+");

            // Write the default config
            fwrite(default_config, 1, strlen(default_config), config_file);

            // Flush the stream and close the file
            fclose(config_file);

            // Try again
            goto created_config_file;
        }

        // UI Errors
        {
            no_app_data:
                #ifndef NDEBUG
                    ui_print_error("[UI] Failed to find a suitable directory for config file in call to function \"%s\"\n", __FUNCTION__);
                #endif

            // Error
            return 0;
        }

        // Standard library errors
        {
            no_mem:
                #ifndef NDEBUG
                    ui_print_error("[Standard Library] Failed to allocate memory in call to function \"%s\"\n", __FUNCTION__);
                #endif

            // Error
            return 0;
        }

        // JSON Errors
        {
            failed_to_parse_json:
                #ifndef NDEBUG
                    ui_print_error("[UI] Failed to parse JSON config file \"%s\" in call to function \"%s\"\n", config_path, __FUNCTION__);
                #endif

                // Error
                return 0;

            failed_primary:
                #ifndef NDEBUG
                    ui_print_error("[UI] Failed to parse primary color from config file \"%s\" in call to function \"%s\"\n", config_path, __FUNCTION__);
                #endif

                // Error
                return 0;

            failed_accent_1:
                #ifndef NDEBUG
                    ui_print_error("[UI] Failed to parse accent color 1 from config file \"%s\" in call to function \"%s\"\n", config_path, __FUNCTION__);
                #endif

                // Error
                return 0;

            failed_accent_2:
                #ifndef NDEBUG
                    ui_print_error("[UI] Failed to parse accent color 2 from config file \"%s\" in call to function \"%s\"\n", config_path, __FUNCTION__);
                #endif

                // Error
                return 0;

            failed_accent_3:
                #ifndef NDEBUG
                    ui_print_error("[UI] Failed to parse accent color 3 from config file \"%s\" in call to function \"%s\"\n", config_path, __FUNCTION__);
                #endif

                // Error
                return 0;

            failed_background:
                #ifndef NDEBUG
                    ui_print_error("[UI] Failed to parse background from config file \"%s\" in call to function \"%s\"\n", config_path, __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

size_t ui_load_file(const char *path, void *buffer, bool binary)
{
    
    // Argument checking
    {
        #ifndef NDEBUG
            if (path == 0)
                goto no_path;
        #endif
    }

    // Initialized data
    size_t ret = 0;
    FILE *f = fopen(path, (binary) ? "rb" : "r");

    // Check if file is valid
    if (f == NULL)
        goto invalid_file;

    // Find file size and prep for read
    fseek(f, 0, SEEK_END);
    ret = ftell(f);
    fseek(f, 0, SEEK_SET);

    // Read to data
    if (buffer)
        ret = fread(buffer, 1, ret, f);

    // We no longer need the file
    fclose(f);

    return ret;

    // Error handling
    {

        // Argument errors
        {
            no_path:
                #ifndef NDEBUG
                    ui_print_error("[Standard library] Null path provided to funciton \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Standard library errors
        {
            invalid_file:
                #ifndef NDEBUG
                    ui_print_error("[Standard library] Failed to load file \"%s\"\n", path);
                #endif

                // Error
                return 0;
        }
    }
}

int ui_print_error(const char *const format, ...)
{
    
    // Argument check
    {
        #ifndef NDEBUG
            if ( format == (void *) 0 )
                goto no_format;
        #endif
    }

    // Varadic argument list for vprintf
    va_list aList;
    va_start(aList, format);

    // Uses ANSI terminal escapes to set the color to red,
    // print the message, and restore the color.
    {
        printf("\033[91m");
        vprintf(format, aList);
        printf("\033[0m");
    }

    va_end(aList);

    // Success
    return 1;

    // Error handling
    {
        
        // Argument errors
        {
            no_format:
                #ifndef NDEBUG
                    printf("Null pointer provided for parameter \"format\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int ui_print_warning(const char *const format, ...)
{

    // Argument check
    {
        #ifndef NDEBUG
            if ( format == (void *) 0 )
                goto no_format;
        #endif
    }

    // Varadic argument list for vprintf
    va_list aList;
    va_start(aList, format);

    // Uses ANSI terminal escapes to set the color to yellow,
    // print the message, and restore the color.
    printf("\033[93m");
    vprintf(format, aList);
    printf("\033[0m");

    va_end(aList);

    // Success
    return 1;

    // Error handling
    {
        
        // Argument errors
        {
            no_format:
                #ifndef NDEBUG
                    printf("Null pointer provided for parameter \"format\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int ui_print_log(const char *const format, ...)
{

    // Argument check
    {
        #ifndef NDEBUG
            if ( format == (void *) 0 )
                goto no_format;
        #endif
    }

    // Varadic argument list for vprintf
    va_list aList;
    va_start(aList, format);

    // Uses ANSI terminal escapes to set the color to light blue,
    // print the message, and restore the color.
    printf("\033[94m");
    vprintf(format, aList);
    printf("\033[0m");

    va_end(aList);

    // Success
    return 1;

    // Error handling
    {
        
        // Argument errors
        {
            no_format:
                #ifndef NDEBUG
                    printf("Null pointer provided for parameter \"format\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int ui_append_window(UIInstance_t *p_instance, UIWindow_t *p_window)
{

    // Argument check
    {
        #ifndef NDEBUG
            if (p_instance == (void *)0)
                goto no_instance;
            if (p_window == (void *)0)
                goto no_window;
        #endif
    }

    // Add the window to the dictionary
    dict_add(p_instance->windows, p_window->name, p_window);
    dict_values(p_instance->windows, p_instance->windows_list);

    // Update the active window
    p_instance->active_window = p_window;

    // There hasn't been a last element yet
    p_instance->active_window->last = 0;

    // Success
    return 1;

    // Error handling
    {
        no_instance:
            #ifndef NDEBUG
                printf("[UI] Null pointer provided for \"p_instance\" in call to function \"%s\"\n", __FUNCTION__);
            #endif

            // Error
            return 0;

        no_window:
            #ifndef NDEBUG
                printf("[UI] Null pointer provided for \"p_window\" in call to function \"%s\"\n", __FUNCTION__);
            #endif

            // Error
            return 0;
    }
}

UIWindow_t *ui_remove_window(UIInstance_t *p_instance, const char *name)
{

    // Argument check
    {
        #ifndef NDEBUG
            if (p_instance == (void *)0)
                goto no_instance;
            if (name == (void *)0)
                goto no_name;
            if (strlen(name) == 0)
                goto empty_name;
        #endif
    }

    // Initialized data
    size_t      window_count = dict_values(p_instance->windows, 0);
    UIWindow_t *ret          = 0;

    // Remove the specified window
    dict_pop(p_instance->windows, name, &ret);
    memset( p_instance->windows_list,0,window_count*sizeof(void *));
    dict_values(p_instance->windows, p_instance->windows_list);

    p_instance->active_window = 0;

    if (window_count)
        p_instance->running = false;

    // Return the window (for deallocation)
    return ret;

    // Error handling
    {
    no_instance:
    no_name:
    empty_name:
    empty_window_name:
        return 0;
    }
}

int ui_process_input ( UIInstance_t *p_instance )
{

    // Argument check
    {
        #ifndef NDEBUG
            if (p_instance == (void *)0)
                goto no_instance;
        #endif
    }

    // Initialized data
    size_t window_count = dict_values(p_instance->windows, 0);
    
    // Iterate over each window
    for (size_t i = 0; i < window_count; i++)
    {

        // Check for a window
        if (p_instance->windows_list[i])
        {

            // Check if the window should close
            if (p_instance->windows_list[i]->is_open == false)
            {
                UIWindow_t *w = ui_remove_window(p_instance, p_instance->windows_list[i]->name);
                if (w)
                    ; // destroy_window(w);
                if (dict_values(p_instance->windows, 0))
                {
                    p_instance->active_window = p_instance->windows_list[dict_values(p_instance->windows, 0) - 1];
                    SDL_ShowWindow(p_instance->active_window->window);

                    SDL_RaiseWindow(p_instance->active_window->window);
                }
                continue;
            }
            
            // Focus
            if (SDL_GetWindowFlags(p_instance->windows_list[i]->window) & SDL_WINDOW_INPUT_FOCUS)
            {
                p_instance->active_window = p_instance->windows_list[i];
            }

            // Process the input
            process_window_input(p_instance->active_window);
        }
    }

    // Success
    return 1;

    // Error handling
    {
        no_instance:
            #ifndef NDEBUG
                ui_print_error("[UI] Null pointer provided for \"p_instance\" in call to function \"%s\"\n", __FUNCTION__);
            #endif
            
            // Error 
            return 0;
    }
}

int ui_draw ( UIInstance_t *p_instance )
{

    // Argument check
    {
        #ifndef NDEBUG
            if (p_instance == (void *)0)
                goto no_instance;
        #endif
    }

    // Allocate for a list of element pointers
    size_t window_count = dict_values(p_instance->windows, 0);

    // Iterate over each window
    for (size_t i = 0; i < window_count; i++)
    {

        // Draw the window
        draw_window(p_instance->windows_list[i]);
    }

    // Success
    return 1;

    // Error handling
    {
        no_instance:
            #ifndef NDEBUG
                ui_print_error("[UI] Null pointer provided for \"p_instance\" in call to function \"%s\"\n", __FUNCTION__);
            #endif
            
            // Error 
            return 0;
    }
}

UIInstance_t *ui_get_active_instance ( void )
{

    // Success
    return active_instance;
}

int ui_draw_format_text ( const char *const format, UIWindow_t *p_window, int x, int y, int size, ... )
{

    // Argument check
    {
        #ifndef NDEBUG
            if ( p_window == (void *) 0 )
                goto no_window;
            if ( format == (void *) 0 )
                goto no_format; 
        #endif
    }

    // We use the varadic argument list in vprintf
    va_list aList;
    va_start(aList, format);

    // TODO: Dynamically allocate size
    char *buffer = calloc(2048, sizeof(u8));

    // TODO: Check memory

    vsprintf(buffer, format, aList);

    ui_draw_text(buffer, p_window, x, y, size);

    free(buffer);

    va_end(aList);

    // Success
    return 1;

    // Error handling
    {
        
        // Argument errors
        {
            no_window:
                #ifndef NDEBUG
                    printf("[UI] Null pointer provided for \"p_window\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
            
            no_format:
                #ifndef NDEBUG
                    printf("[UI] Null pointer provided for \"format\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

void ui_draw_char(char c, UIWindow_t *p_window, int x, int y, int size)
{
    // Argument check
    {
        #ifndef NDEBUG
            if ( p_window == (void *) 0 )
                goto no_window;
        #endif
    }

    // Initialized data
    u64 glyph = font[(u8)c];

    // Iterate over the width and the height of the glyph
    for (s32 h = (x + (8 * size)); h > x; h -= size)
        for (s32 w = y; w < (y + (8 * size)); w += size)
        {

            // Draw a pixel in the glyph
            if (glyph & 1)

                // Of a specified size
                for (s32 i = 0; i < size; i++)
                    for (s32 j = 0; j < size; j++)

                        // Draw the pixel
                        SDL_RenderDrawPoint(p_window->renderer, w + i, h + j);

            // Draw the next part of the glyph
            glyph >>= 1;
        }

    // Return
    return;

    // Error handling
    {
        
        // Argument errors
        {
            no_window:
                #ifndef NDEBUG
                    printf("[UI] Null pointer provided for \"p_window\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return;
        }
    }
}

int ui_draw_text(const char *const text, UIWindow_t *p_window, int x, int y, int size)
{

    // Argument check
    {
        #ifndef NDEBUG
            if ( p_window == (void *) 0 )
                goto no_window;
        #endif
    }

    size_t len = strlen(text);

    int lx = x,
        ly = y;

    for (size_t i = 0; i < len; i++)
        ui_draw_char(text[i], p_window, ly, lx + (i * (8 * size)), size);

    // Success
    return 1;

    // Error handling
    {
        
        // Argument errors
        {
            no_window:
                #ifndef NDEBUG
                    printf("[UI] Null pointer provided for \"p_window\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int ui_draw_circle(int radius, UIWindow_t *p_window, int x_center, int y_center)
{

    // Argument check
    {
        #ifndef NDEBUG
            if ( p_window == (void *) 0 )
                goto no_window;
        #endif
    }
    
    // Initialized data
    i32 diameter = (radius * 2),
        x        = (radius - 1),
        y        = 0,
        tx       = 1,
        ty       = 1,
        error    = (tx - diameter);

    // Draw the circle
    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(p_window->renderer, x_center + x, y_center - y);
        SDL_RenderDrawPoint(p_window->renderer, x_center + x, y_center + y);
        SDL_RenderDrawPoint(p_window->renderer, x_center - x, y_center - y);
        SDL_RenderDrawPoint(p_window->renderer, x_center - x, y_center + y);
        SDL_RenderDrawPoint(p_window->renderer, x_center + y, y_center - x);
        SDL_RenderDrawPoint(p_window->renderer, x_center + y, y_center + x);
        SDL_RenderDrawPoint(p_window->renderer, x_center - y, y_center - x);
        SDL_RenderDrawPoint(p_window->renderer, x_center - y, y_center + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }

    // Success
    return 1;

    // Error handling
    {
        
        // Argument errors
        {
            no_window:
                #ifndef NDEBUG
                    printf("[UI] Null pointer provided for \"p_window\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int ui_exit ( UIInstance_t **pp_instance )
{

    // Argument check
    {
        #ifndef NDEBUG
            if ( pp_instance == (void *)0 )
                goto no_instance;
        #endif
    }

    // Initialized data
    UIInstance_t *p_instance = *pp_instance;

    // Destroy the windows
    dict_free_clear(p_instance->windows, destroy_window);
    dict_destroy(&p_instance->windows);

    // Free the instance
    free(p_instance);

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_instance:
                #ifndef NDEBUG
                    printf("[UI] Null pointer provided for \"pp_instance\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}
