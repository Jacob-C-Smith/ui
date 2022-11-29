#include <UI/UITable.h>

int           create_table               ( UITable_t  **pp_table )
{
	// Argument check
    {
        #ifndef NDEBUG
            if( pp_table == (void *) 0 )
                goto no_table;
        #endif
    }

    // Allocate for a table
    UITable_t *p_table = calloc(1, sizeof(UITable_t));

    // Check memory
    {
        #ifndef NDEBUG
            if(p_table == (void *)0)
                goto no_mem;
        #endif
    }

    *pp_table = p_table;

    return 0;

    // Error handling
    {

        // Argument errors
        {
            no_table:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Table] Null pointer provided for \"pp_table\" in call to function \"%s\"\n",__FUNCSIG__);
                #endif
                return -1;
        }

        // Standard library errors
        {
            no_mem:
                #ifndef NDEBUG
                    ui_print_error("[Standard library] Failed to allocate memory in call to function \"%s\"\n",__FUNCSIG__);
                #endif
                return -1;
        }
    }
}

int           load_table_as_dict         ( UITable_t  **pp_table, dict             *dictionary)
{

    // Argument errors
    {
        #ifndef NDEBUG
            if ( pp_table == (void *) 0 )
                goto no_table;
            if ( dictionary == (void *) 0 )
                goto no_dictionary;
        #endif
    }

    // Initialized data
    UITable_t  *p_table     = 0;
    char       *x           = 0,
               *y           = 0,
               *max_rows    = 0,
               *max_columns = 0,
               *file        = 0;

    // Parse the dictionary
    {

        // Initialized data
        JSONToken_t *token = 0;
        
        // Parse each property
        {
            token       = dict_get(dictionary, "x");
            x           = JSON_VALUE(token, JSONprimative);

            token       = dict_get(dictionary, "y");
            y           = JSON_VALUE(token, JSONprimative);

            token       = dict_get(dictionary, "max rows");
            max_rows    = JSON_VALUE(token, JSONprimative);

            token       = dict_get(dictionary, "max columns");
            max_columns = JSON_VALUE(token, JSONprimative);
            
            token       = dict_get(dictionary, "file");
            file        = JSON_VALUE(token, JSONstring);

        }
    }

    // Is there enough information to construct the table?
    {
        #ifndef NDEBUG
            if ( x == (void *) 0 )
                goto no_x;
            if ( y == (void *) 0 )
                goto no_y;
        #endif
    }

    // Allocate the table
    create_window(pp_table);

    // Return the table
    p_table = *pp_table;

    // Construct the table
    {

        // Set the tables position
        p_table->x           = atoi(x);
        p_table->y           = atoi(y);

    }

    if (file)
        goto csv_parse;

    p_table->max_rows      = atoi(max_rows);
    p_table->max_columns   = atoi(max_columns);

    csv_parse_done:
    p_table->data          = calloc(p_table->max_rows * p_table->max_columns, sizeof(void *) );
    p_table->column_widths = calloc(p_table->max_columns, sizeof(size_t));
    
    for (size_t i = 0; i < p_table->max_columns; i++)
        p_table->column_widths[i] = 1;

    set_table_cell(p_table, 0, 0, "Name");
    set_table_cell(p_table, 1, 0, "Atomic mass");
    set_table_cell(p_table, 2, 0, "Symbol");

    set_table_cell(p_table, 0, 1, "Hydrogen");
    set_table_cell(p_table, 1, 1, "1.008");
    set_table_cell(p_table, 2, 1, "H");

    set_table_cell(p_table, 0, 2, "Helium");
    set_table_cell(p_table, 1, 2, "4.003");
    set_table_cell(p_table, 2, 2, "He");

    set_table_cell(p_table, 0, 3, "Lithium");
    set_table_cell(p_table, 1, 3, "6.941");
    set_table_cell(p_table, 2, 3, "Li");

    set_table_cell(p_table, 0, 4, "Beryllium");
    set_table_cell(p_table, 1, 4, "9.012");
    set_table_cell(p_table, 2, 4, "Be");

    return 0;

    // Auxilary branches
    csv_parse:
    {

        // Initialized data
        size_t  len          = ui_load_file(file, 0, false),
                column_count = 0,
                row_count    = 0;
        char   *buf          = calloc(len+1, sizeof(u8)), 
               *z_buf        = 0;
        
        // Load the CSV file
        ui_load_file(file, buf, false);
        
        z_buf = buf;

        // Preparse
        {
            size_t i           = 0;
            size_t cols_in_row = 0;

            while (buf[++i] != '\0')
                if      (buf[i] == ',')  cols_in_row++;
                else if (buf[i] == '\n')
                {
                    if (buf[i + 1] == '\n') continue;
                    row_count   += 1,
                    column_count = (cols_in_row > column_count) ? cols_in_row : column_count;
                    cols_in_row  = 0;
                }
        }

        // Allocate 
        p_table->data = calloc(row_count * column_count, sizeof(void *));

        // Parse
        {
            size_t r = 0,
                   c = 0;

            char *i_val = 0;

            while (*++z_buf)
            {
                if (*z_buf == ',')  c++, *z_buf=0, z_buf+=2;
                if (*z_buf == '\n') r++, c = 0;

                i_val = "ASDF :)";

                p_table->data[c * row_count + r] = i_val;

            }
        }

        printf("\n");
        goto csv_parse_done;
    }
    // Error handling
    {

        // Argument errors
        {
            no_table:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Table] Null pointer provided for \"pp_table\" in call to function \"%s\"\n", __FUNCSIG__);
                #endif
                return -1;
            no_dictionary:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Table] Null pointer provided for \"dictionary\" in call to function \"%s\"\n", __FUNCSIG__);
                #endif
                return -1;
        }

        // Missing required construction parameters
        {
            no_label:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Table] No \"label\" property in \"dictionary\" in call to function \"%s\"\n", __FUNCSIG__);
                #endif
                return -1;
            no_x:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Table] No \"x\" property in \"dictionary\" in call to function \"%s\"\n", __FUNCSIG__);
                #endif
                return -1;
            no_y:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Table] No \"y\" property in \"dictionary\" in call to function \"%s\"\n", __FUNCSIG__);
                #endif
                return -1;
        }

        // Standard library errors
        {
            no_mem:
                #ifndef NDEBUG
                    ui_print_error("[Standard Library] Failed to allocate memory in call to funciton \"%s\"\n", __FUNCSIG__);
                #endif
                return -1;
        }
    }
}

int           hover_table                ( UITable_t   *p_table , ui_mouse_state_t  mouse_state)
{

    // Argument check
    {
        #ifndef NDEBUG
            if ( p_table == (void *) 0 )
                goto no_table;
        #endif  
    }

    // Iterate through hover callbacks
    for (size_t i = 0; i < p_table->on_hover_count; i++)
    {

        // Define the callback function
        void (*callback)(UITable_t *, ui_mouse_state_t) = p_table->on_hover[i];

        // Call the callback function
        if (callback)
            (*callback)(p_table, mouse_state);

    }

    return 0;

    // Error handling
    {

        // Argument errors
        {
            no_table:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Table] Null pointer provided for \"table\" in call to function \"%s\"\n", __FUNCSIG__);
                #endif
                return 0;
        }
    }
}
 
int           click_table                ( UITable_t   *p_table , ui_mouse_state_t  mouse_state)
{

    // Iterate through callbacks
    for (size_t i = 0; i < p_table->on_click_count; i++)
    {
        // Define the callback function
        void (*callback)(UITable_t*, ui_mouse_state_t) = p_table->on_click[i];

        // Call the callback function
        if(callback)            
            (*callback)(p_table, mouse_state);

    }

    return 0;
}

int           release_table              ( UITable_t   *p_table, ui_mouse_state_t mouse_state )
{

    // Iterate through callbacks
    for (size_t i = 0; i < p_table->on_release_count; i++)
    {
        // Define the callback function
        void (*callback)(UITable_t*, ui_mouse_state_t) = p_table->on_release[i];


        // Call the callback function
        if (callback)
            (*callback)(p_table, mouse_state);

    }
    return 0;
}

//
//int           add_click_callback_button   ( UIButton_t  *p_button, void(*callback)(UIButton_t*, ui_mouse_state_t))
//{
//    // TODO: Argument check
//
//    // If this is the first callback, set the max to 1 and 
//    if (p_button->on_click_max == 0)
//    {
//        p_button->on_click_max = 1;
//        p_button->on_click = calloc(1, sizeof(void*));
//    }
//
//    // Simple heuristic that doubles callbacks lists length when there is no space to store the callback pointer
//    if (p_button->on_click_count + 1 > p_button->on_click_max)
//    {
//        // Double the max
//        p_button->on_click_max *= 2;
//
//        realloc(p_button->on_click, p_button->on_click_max);
//    }
//
//    // Increment the callback counter and install the new callback
//    p_button->on_click[p_button->on_click_count++] = callback;
//
//    return 0;
//
//    // TODO: Error handling
//}
//
//int           add_hover_callback_button   ( UIButton_t  *button, void(*callback)(UIButton_t*, ui_mouse_state_t))
//{
//    // TODO: Argument check
//
//    // If this is the first callback, set the max to 1 and 
//    if (button->on_hover_max == 0)
//    {
//        button->on_hover_max = 1;
//        button->on_hover     = calloc(1, sizeof(void*));
//    }
//
//
//    // Simple heuristic that doubles callbacks lists length if there is no space to 
//    // store the callback pointer
//    if (button->on_hover_count + 1 > button->on_hover_max)
//    {
//        // Double the max
//        button->on_hover_max *= 2;
//
//        // Allocate the maximum number of callbacks
//        void **callbacks = calloc(button->on_hover_max, sizeof(void*)),
//              *t         = button->on_hover;
//
//        // Copy all the callbacks from the button to the new callback list
//        memcpy(callbacks, button->on_hover, button->on_hover_count * sizeof(void *));
//
//        // Set the hover callback list pointer to the new list
//        button->on_hover = callbacks;
//
//        // Free the old callback list
//        free(t);
//    }
//
//    // Increment the callback counter and install the new callback
//    button->on_hover[button->on_hover_count++] = callback;
//
//    return 0;
//
//    // TODO: Error handling
//}
//
//int           add_release_callback_button ( UIButton_t  *button, void(*callback)(UIButton_t*, ui_mouse_state_t))
//{
//    // TODO: Argument check
//
//    // If this is the first callback, set the max to 1 and 
//    if (button->on_release_max == 0)
//    {
//        button->on_release_max = 1;
//        button->on_release = calloc(1, sizeof(void*));
//    }
//
//
//    // Simple heuristic that doubles callbacks lists length if there is no space to 
//    // store the callback pointer
//    if (button->on_release_count + 1 > button->on_release_max)
//    {
//        // Double the max
//        button->on_release_max *= 2;
//
//        // Allocate the maximum number of callbacks
//        void** callbacks = calloc(button->on_release_max, sizeof(void*)),
//            * t = button->on_release;
//
//        // Copy all the callbacks from the button to the new callback list
//        memcpy(callbacks, button->on_release, button->on_release_count * sizeof(void*));
//
//        // Set the release callback list pointer to the new list
//        button->on_release = callbacks;
//
//        // Free the old callback list
//        free(t);
//    }
//
//    // Increment the callback counter and install the new callback
//    button->on_release[button->on_release_count++] = callback;
//
//    return 0;
//
//    // TODO: Error handling
//}

char *get_table_cell(UITable_t* p_table, size_t x, size_t y)
{

    return p_table->data[y*p_table->max_columns+x];
}

int set_table_cell(UITable_t* p_table, size_t x, size_t y, char* cell_text)
{
    char **a = &p_table->data[y * p_table->max_columns + x];

    if (*a == (void*)0)
        ;// goto copy_cell_text;

    size_t b = strlen(cell_text);

    if ( p_table->column_widths[x] < b )
        p_table->column_widths[x] = b;

    //free(a);

    copy_cell_text:
        *a=cell_text;

    return 1;
}

int           draw_table                 ( UIWindow_t  *window, UITable_t *table )
{
    UIInstance_t *instance = ui_get_active_instance();
    SDL_Rect      r        = { table->x, table->y, 0, 13 };

    for (size_t i = 0; i < table->max_rows; i++)
    {
        r.w = 0;

        for (size_t j = 0; j < table->max_columns; j++)
        {

            color c = (i & 0x1) ? instance->accent_1 : instance->background;

            r.w = ( table->column_widths[j] + 1 ) * 8;

            SDL_SetRenderDrawColor(window->renderer, (u8)instance->primary, (u8)(instance->primary >> 8), (u8)(instance->primary >> 16), 0xff);
            SDL_RenderDrawRect(window->renderer, &r);

            SDL_SetRenderDrawColor(window->renderer, (u8)c, (u8)(c >> 8), (u8)(c >> 16), 0xff);
            
            r.x++, r.y += 1, r.w -= 2, r.h -= 2;
            
            SDL_RenderFillRect(window->renderer, &r);

            if (table->data[i * table->max_columns + j])
            {
                SDL_SetRenderDrawColor(window->renderer, (u8)instance->primary, (u8)(instance->primary >> 8), (u8)(instance->primary >> 16), 0xff);

                ui_draw_text(table->data[i * table->max_columns + j], window, r.x + 4, r.y + 1, 1);
            }

            r.x--, r.y -= 1, r.w += 2, r.h += 2;
            
            r.x += r.w - 1;
        }

        r.y += 12;
        r.w++;
        r.x = table->x;
    }

    //if (button->depressed==false)
    //{
    //    SDL_SetRenderDrawColor(window->renderer, (u8)instance->accent_2, (u8)(instance->accent_2 >> 8), (u8)(instance->accent_2 >> 16), 0xff);
    //    SDL_RenderDrawLine(window->renderer, r.x + r.w - 1, r.y, r.x + r.w - 1, r.y + r.h - 1);
    //    SDL_RenderDrawLine(window->renderer, r.x, r.y + r.h - 1, r.x + r.w - 1, r.y + r.h - 1);
    //    r.x--, r.y--;
    //}

    //SDL_SetRenderDrawColor(window->renderer, (u8)instance->accent_1, (u8)(instance->accent_1 >> 8), (u8)(instance->accent_1 >> 16), 0xff);
    //SDL_RenderFillRect(window->renderer, &r);
    //SDL_SetRenderDrawColor(window->renderer, (u8)instance->primary, (u8)(instance->primary >> 8), (u8)(instance->primary >> 16), 0xff);
    //
    //
    //ui_draw_text(button->label, window, r.x + 3, r.y + 1, 1);

    return 0;
}

bool          table_in_bounds            ( UIButton_t  *button, ui_mouse_state_t mouse_state )
{
    // Initialized data
	//i32  x = button->x,
	//	 y = button->y,
	//	 w = button->w,
	//	 h = button->h;
	//
	//// Check for bounds
	//if (mouse_state.x >= x && mouse_state.y >= y && mouse_state.x <= x + w && mouse_state.y <= y + h)
	//	return true;

	return false;

}

int           destroy_table              ( UIButton_t  *p_button )
{

    // Argument check
    {
        if (p_button == (void*)0)
            goto no_button;
    }
        
    // Free label string
    free(p_button->label);

    // Free callbacks
    {
        free(p_button->on_click);
        free(p_button->on_hover);
        free(p_button->on_release);
    }

    // Free the button memory
    free(p_button);

    return 0;

    // Error handling
    {

        // Argument errors
        {
            no_button:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Button] Null pointer provided for \"p_button\" in call to function \"%s\"\n", __FUNCSIG__);
                #endif
                return -1;
        }
    }
}