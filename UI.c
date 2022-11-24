#include <UI/UI.h>

// Each u64 encodes an 8x8 glyph. ASCII values can be used to index characters. Add whatever you want so long as you keep the length under 255
u64 font[133] = {
    0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,
    0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,
    0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,
    0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,
    0x0000000000000000,	0x183C3C1818001800,	0x3636000000000000,	0x36367F367F363600,	0x0C3E031E301F0C00,	0x006333180C666300,	0x1C361C6E3B336E00,	0x0606030000000000,
    0x180C0606060C1800,	0x060C1818180C0600,	0x00663CFF3C660000,	0x000C0C3F0C0C0000,	0x00000000000C0C06,	0x0000003F00000000,	0x00000000000C0C00,	0x6030180C06030100,
    0x3E63737B6F673E00,	0x0C0E0C0C0C0C3F00,	0x1E33301C06333F00,	0x1E33301C30331E00,	0x383C36337F307800,	0x3F031F3030331E00,	0x1C06031F33331E00,	0x3F3330180C0C0C00,
    0x1E33331E33331E00,	0x1E33333E30180E00,	0x000C0C00000C0C00,	0x000C0C00000C0C06,	0x180C0603060C1800,	0x00003F00003F0000,	0x060C1830180C0600,	0x1E3330180C000C00,
    0x3E637B7B7B031E00,	0x0C1E33333F333300,	0x3F66663E66663F00,	0x3C66030303663C00,	0x1F36666666361F00,	0x7F46161E16467F00,	0x7F46161E16060F00,	0x3C66030373667C00,
    0x3333333F33333300,	0x1E0C0C0C0C0C1E00,	0x7830303033331E00,	0x6766361E36666700,	0x0F06060646667F00,	0x63777F7F6B636300,	0x63676F7B73636300,	0x1C36636363361C00,
    0x3F66663E06060F00,	0x1E3333333B1E3800,	0x3F66663E36666700,	0x1E33070E38331E00,	0x3F2D0C0C0C0C1E00,	0x3333333333333F00,	0x33333333331E0C00,	0x6363636B7F776300,
    0x6363361C1C366300,	0x3333331E0C0C1E00,	0x7F6331184C667F00,	0x1E06060606061E00,	0x03060C1830604000,	0x1E18181818181E00,	0x081C366300000000,	0x00000000000000FF,
    0x0C0C180000000000,	0x00001E303E336E00,	0x0706063E66663B00,	0x00001E3303331E00,	0x3830303e33336E00,	0x00001E333f031E00,	0x1C36060f06060F00,	0x00006E33333E301F,
    0x0706366E66666700,	0x0C000E0C0C0C1E00,	0x300030303033331E,	0x070666361E366700,	0x0E0C0C0C0C0C1E00,	0x0000337F7F6B6300,	0x00001F3333333300,	0x00001E3333331E00,
    0x00003B66663E060F,	0x00006E33333E3078,	0x00003B6E66060F00,	0x00003E031E301F00,	0x080C3E0C0C2C1800,	0x0000333333336E00,	0x00003333331E0C00,	0x0000636B7F7F3600,
    0x000063361C366300,	0x00003333333E301F,	0x00003F190C263F00,	0x380C0C070C0C3800,	0x1818180018181800,	0x070C0C380C0C0700,	0x6E3B000000000000,	0x0000000000000000,
    0x80C0E070371E1C08, 0x00001c3e3e3e1c00, 0x040C1C3C3C1C0C04, 0x0000ff4224180000, 0x7E7E7E7E7E7E3C18
};

char         *default_config   = "{\n\t\"name\"       : \"Default color theme\",\n\t\"primary\"    : [ 0, 0, 0 ],\n\t\"accent 1\"   : [ 128, 128, 128 ],\n\t\"accent 2\"   : [ 192, 192, 192 ],\n\t\"accent 3\"   : [ 0, 128, 255 ],\n\t\"background\" : [ 255, 255, 255 ]\n}\n";
char         *config_file_name = "\\ui_config.json";
UIInstance_t *active_instance  = 0;

int           ui_init                ( UIInstance_t **pp_instance, const char       *path )
{

    // Argument check
    {
        #ifndef NDEBUG
            if ( pp_instance == (void *) 0 )
                goto no_instance;
            if ( path == (void *) 0 )
                goto no_path;
        #endif
    }

    // Uninitialized data
    FILE         *config_file;

    // Initialized data
    UIInstance_t *ret              = calloc(1, sizeof(UIInstance_t));

    char         *appdata          = getenv("APPDATA");
    size_t        appdata_len      = strlen(appdata) + strlen(config_file_name);

    char         *config_path      = calloc(appdata_len + 1, sizeof(u8)),
                 *config_file_data = 0,
                **primary          = 0,
                **accent_1         = 0,
                **accent_2         = 0,
                **accent_3         = 0,
                **background       = 0;
    dict         *config_file_json = 0;
    size_t        config_file_len  = 0;

    if (!appdata)
        goto no_app_data;

    // Search AppData for a config
    strcat(config_path, appdata);
    strcat(config_path, config_file_name);

    created_config_file:
    
    // Load the config file
    {
        config_file_len  = ui_load_file(config_path, 0, false);
        if (config_file_len == 0)
            goto no_config_file;
        config_file_data = calloc(config_file_len, sizeof(u8));
        ui_load_file(config_path, config_file_data, false);
    }

    // Parse the config file into a dictionary
    parse_json(config_file_data, config_file_len, &config_file_json);

    // Get properties from the dictionary
    {

        // Initialized data
        JSONToken_t* token = 0;

        token      = dict_get(config_file_json, "primary");
        primary    = JSON_VALUE(token, JSONarray);

        token      = dict_get(config_file_json, "accent 1");
        accent_1   = JSON_VALUE(token, JSONarray);

        token      = dict_get(config_file_json, "accent 2");
        accent_2   = JSON_VALUE(token, JSONarray);

        token      = dict_get(config_file_json, "accent 3");
        accent_3   = JSON_VALUE(token, JSONarray);

        token      = dict_get(config_file_json, "background");
        background = JSON_VALUE(token, JSONarray);
    }

    // Construct the instance
    {

        // Set the theme colors
        {
            ret->primary    = atoi(primary[0])    | (atoi(primary[1])    << 8) | (atoi(primary[2])    << 16) | (0xff << 24);
            ret->accent_1   = atoi(accent_1[0])   | (atoi(accent_1[1])   << 8) | (atoi(accent_1[2])   << 16) | (0xff << 24);
            ret->accent_2   = atoi(accent_2[0])   | (atoi(accent_2[1])   << 8) | (atoi(accent_2[2])   << 16) | (0xff << 24);
            ret->accent_3   = atoi(accent_3[0])   | (atoi(accent_3[1])   << 8) | (atoi(accent_3[2])   << 16) | (0xff << 24);
            ret->background = atoi(background[0]) | (atoi(background[1]) << 8) | (atoi(background[2]) << 16) | (0xff << 24);
        }

        // Construct a hash table
        dict_construct(&ret->windows, 16);

        // Allocate a list of windows
        ret->windows_list = calloc(16, sizeof(UIWindow_t *));
    }

    // Start up SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS );

    // Construct element function lookup tables
    extern int init_element( void );
    
    // Initialize element function lookup tables
    init_element();
    
    // Set the active instance
    active_instance = ret;
    
    // Return
    *pp_instance    = ret;

    free(config_path);

    return ret;

    // Error handling
    {

        // User errors
        {

            // Create a config file 
            no_config_file:
            {

                // Create the file
                config_file = fopen(config_path, "w+");

                // Write the default config
                fwrite(default_config, 1, strlen(default_config), config_file);

                // Flush the stream and close the file
                fclose(config_file);

                // Try again
                goto created_config_file;
            }
        }

        // Standard library errors
        {
            no_app_data:
                return 0;
        }

        // JSON type errors
        {
            primary_type_error:
            accent_1_type_error:
            accent_2_type_error:
            accent_3_type_error:
            background_type_error:
                return 0;
        }

        // Argument errors
        {
            no_instance:
            no_path:
            ;
        }
    }
}

size_t        ui_load_file           ( const char       *path    ,   void    *buffer, bool binary )
{
    // Argument checking 
    {
        #ifndef NDEBUG
            if (path == 0)
                goto no_path;
        #endif
    }

    // Initialized data
    size_t  ret = 0;
    FILE   *f   = fopen(path, (binary) ? "rb" : "r");

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
                    ui_print_error("[G10] Null path provided to funciton \"%s\\n", __FUNCSIG__);
                #endif
                return 0;
        }
        invalid_file:
        {
           #ifndef NDEBUG
                ui_print_error("[G10] Failed to load file \"%s\"\n", path);
           #endif
           return 0;
        }
    }
}

int           ui_print_error         ( const char *const format  , ... )
{
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

    return 0;
}

int           ui_print_warning       ( const char *const format  , ... )
{
    // Varadic argument list for vprintf
    va_list aList;
    va_start(aList, format);

    // Uses ANSI terminal escapes to set the color to yellow, 
    // print the message, and restore the color.
    printf("\033[93m");
    vprintf(format, aList);
    printf("\033[0m");

    va_end(aList);

    return 0;
}

int           ui_print_log           ( const char *const format  , ... )
{
    // Varadic argument list for vprintf
    va_list aList;
    va_start(aList, format);

    // Uses ANSI terminal escapes to set the color to light blue, 
    // print the message, and restore the color.
    printf("\033[94m");
    vprintf(format, aList);
    printf("\033[0m");

    va_end(aList);

    return 0;
}

int           ui_append_window       ( UIInstance_t     *instance, UIWindow_t *window )
{
    // Argument check
    {
        #ifndef NDEBUG
            if (instance == (void *)0)
                goto no_instance;
            if (window == (void*)0)
                goto no_window;
        #endif
    }

    // Add the window to the list
    instance->windows_list[dict_values(instance->windows, 0)] = window;

    // Add the window to the dictionary
    dict_add(instance->windows, window->name, window);

    // Update the active window
    instance->active_window       = window;
    instance->active_window->last = 0;

    SDL_ShowWindow(instance->active_window->window);
    SDL_RaiseWindow(instance->active_window->window);

    return 1;

    // Error handling
    {
        no_instance:
            return 0;
        no_window:
            return 0;
    }
}

UIWindow_t   *ui_remove_window       ( UIInstance_t     *instance, const char *name )
{

    // Argument check
    {
        #ifndef NDEBUG
            if(instance == (void *)0)
                goto no_instance;
            if (name == (void*)0)
                goto no_name;
            if (strlen(name) == 0)
                goto empty_name;
        #endif  
    }

    size_t window_count = dict_values(instance->windows, 0);

    // Remove the window from the instance
    UIWindow_t *ret = dict_pop(instance->windows, name);   

    // Iterate over each window in the list
    for (size_t i = 0; i < window_count; i++)

        // Matching window?
        if (instance->windows_list[i] == ret)
        {

            // 
            instance->windows_list[i]                = instance->windows_list[window_count - 1];
            instance->windows_list[window_count - 1] = 0;
        }

    instance->active_window = 0;

    if (instance->windows->n_entries == 0)
        instance->running = false;

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

int           ui_process_input       ( UIInstance_t     *instance )
{
    size_t       window_count = dict_values(instance->windows, 0);

    for (size_t i = 0; i < window_count; i++)
    {
        if (instance->windows_list[i])
        {
            if (instance->windows_list[i]->is_open == false)
            {
                UIWindow_t* w = ui_remove_window(instance, instance->windows_list[i]->name);
                destroy_window(w);
                if (instance->windows->n_entries)
                {
                    instance->active_window = instance->windows_list[instance->windows->n_entries - 1];
                    SDL_ShowWindow(instance->active_window->window);

                    SDL_RaiseWindow(instance->active_window->window);

                }
                continue;
            }
            if (instance->windows_list[i])
                if (SDL_GetWindowFlags(instance->windows_list[i]->window) & SDL_WINDOW_INPUT_FOCUS)
                {
                    instance->active_window = instance->windows_list[i];
                }
            // Iterate over windows
            process_window_input(instance->active_window);
        }
    }
    


    return 0;
}

int           ui_draw                ( UIInstance_t     *instance )
{

    // Argument check
    {
        #ifndef NDEBUG
            if(instance == (void *)0)
                goto no_instance;
        #endif
    }

    // Allocate for a list of element pointers
    size_t window_count = dict_values(instance->windows, 0);

    // Populate element pointer list

    for (size_t i = 0; i < window_count; i++)
    {

        // Draw the window
        draw_window(instance->windows_list[i]);
    }


    return 0;

    // Error handling
    {
        no_instance:
            return 0;
    }
}

UIInstance_t *ui_get_active_instance ( void )
{
    return active_instance;
}

int           ui_draw_format_text    ( const char *const format  , UIWindow_t *window, int  x       , int y       , int size, ... )
{
    // We use the varadic argument list in vprintf
    va_list aList;
    va_start(aList, format);

    // TODO: Dynamically allocate size
    char* buffer = calloc(2048, sizeof(u8));

    // TODO: Check memory

    vsprintf(buffer, format, aList);

    ui_draw_text(buffer, window, x, y, size);
    
    free(buffer);

    va_end(aList);

    return 0;
}

void          UIDrawChar             ( char              c       , UIWindow_t *window, int  x       , int y       , int size )
{
    u64 bmc = font[(u8)c];
    for ( u32 h = ( x + ( 8 * size ) ); h > x; h -= size )
        for ( u32 w = y; w < ( y + ( 8 * size ) ); w += size )
        {
            if ( bmc & 1 )
                for( u32 i = 0; i < size; i++ )
                    for ( u32 j = 0; j < size; j++ )
                        SDL_RenderDrawPoint(window->renderer, w+i, h+j);
                bmc >>= 1;
        }

}

int           ui_draw_text           ( const char *const text    , UIWindow_t *window, int  x       , int y       , int size )
{  
    size_t len = strlen(text);

    int lx = x,
        ly = y;

    for (size_t i = 0; i < len; i++)
        UIDrawChar(text[i], window, ly, lx + (i * (8 * size)), size);

    return 0;
}

int           ui_draw_circle         ( int               radius  , UIWindow_t *window, int  x_center, int y_center )
{
    i32 diameter = (radius * 2),
        x        = (radius - 1),
        y        = 0,
        tx       = 1,
        ty       = 1,
        error    = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(window->renderer, x_center + x, y_center - y);
        SDL_RenderDrawPoint(window->renderer, x_center + x, y_center + y);
        SDL_RenderDrawPoint(window->renderer, x_center - x, y_center - y);
        SDL_RenderDrawPoint(window->renderer, x_center - x, y_center + y);
        SDL_RenderDrawPoint(window->renderer, x_center + y, y_center - x);
        SDL_RenderDrawPoint(window->renderer, x_center + y, y_center + x);
        SDL_RenderDrawPoint(window->renderer, x_center - y, y_center - x);
        SDL_RenderDrawPoint(window->renderer, x_center - y, y_center + x);

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
    return 0;
}
 
int           ui_exit                ( UIInstance_t     *instance )
{
    dict_destroy(instance->windows);
    free(instance);
    
    return 0;
}
