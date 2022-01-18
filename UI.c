#include <UI/UI.h>

u64 font[132] = {
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
    0x80C0E070371E1C08, 0x003C7E7E7E7E3C00, 0x040C1C3C3C1C0C04, 0x0000ff4224180000
};

char* default_config = "{\n\t\"name\"       : \"Default color theme\",\n\t\"primary\"    : [ 0, 0, 0 ],\n\t\"accent 1\"   : [ 128, 128, 128 ],\n\t\"accent 2\"   : [ 192, 192, 192 ],\n\t\"accent 3\"   : [ 0, 128, 255 ],\n\t\"background\" : [ 255, 255, 255 ]\n}\n";

UIInstance_t *ui_init           ( const char        *path )
{
    // TODO: Argument check
    // Uninitialized data
    FILE         *config_file;

    // Initialized data
    UIInstance_t *ret         = calloc(1, sizeof(UIInstance_t));

    // Search AppData for a config
    created_config_file:
    //config_file = fopen("%APPDATA%/ui_config.json", "r");

    // 
    //if (config_file == 0)
       // goto no_config_file;


    //printf(default_config);

    return ret;

    // Error handling
    {

        // User errors
        {

            // Create a config file 
            no_config_file:
            {

                // Create the file
                config_file = fopen("~/AppData/Roaming/ui_config.json", "w+");

                // Write the default config
                fwrite(default_config, 1, strlen(default_config), config_file);

                // Flush the stream and close the file
                fclose(default_config);

                // Try again
                goto created_config_file;
            }
        }

        // Standard library errors
        {

        }

        // Argument errors
        {

        }
    }
}

size_t        ui_load_file       ( const char        *path,   void* buffer)
{
    // Argument checking 
    {
        #ifndef NDEBUG
            if (path == 0)
                goto noPath;
        #endif
    }

    // Initialized data
    size_t  ret = 0;
    FILE   *f   = fopen(path, "r");

    // Check if file is valid
    if (f == NULL)
        goto invalidFile;

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
        noPath:
            #ifndef NDEBUG
                ui_print_error("[G10] Null path provided to funciton \"%s\\n", __FUNCSIG__);
            #endif
            return 0;

        invalidFile:
            #ifndef NDEBUG
                ui_print_error("[G10] Failed to load file \"%s\"\n", path);
            #endif
           return 0;
    }
}

int           ui_print_error     ( const char *const  format, ...)
{
    // We use the varadic argument list in vprintf
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
int           ui_print_warning   ( const char *const  format, ...)
{
    // We use the varadic argument list in vprintf
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
int           ui_print_log       ( const char *const  format, ...)
{
    // We use the varadic argument list in vprintf
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

int           ui_draw_format_text ( const char *const  format, UIWindow_t * window, int x, int y, int size, ...)
{
    // We use the varadic argument list in vprintf
    va_list aList;
    va_start(aList, format);

    // TODO: Dynamically allocate size
    char* buffer = calloc(1024, sizeof(u8));

    // TODO: Check memory

    vsprintf(buffer, format, aList);

    ui_draw_text(buffer, window, x, y, size);
    
    free(buffer);

    va_end(aList);

    return 0;
}
void          UIDrawChar       ( char               c     , UIWindow_t *window, int x, int y, int size)
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
int           ui_draw_text       ( const char *const  text  , UIWindow_t *window, int x, int y, int size)
{  
    size_t len = strlen(text);
    for (size_t i = 0; i < len; i++)
        UIDrawChar(text[i], window, y, x + (i * (8*size)), size);

    return 0;
}

int           ui_draw_circle(int radius, UIWindow_t* window, int x_center, int y_center)
{
    // TODO:
    return 0;
}

int           ui_exit           ( UIInstance_t      *instance )
{
    free(instance);
    
    return 0;
}
