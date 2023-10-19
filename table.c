#include <ui/table.h>

int create_table ( ui_table **pp_table )
{
	// Argument check
    {
        #ifndef NDEBUG
            if( pp_table == (void *) 0 )
                goto no_table;
        #endif
    }

    // Allocate for a table
    ui_table *p_table = calloc(1, sizeof(ui_table));

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
                    ui_print_error("[UI] [Table] Null pointer provided for \"pp_table\" in call to function \"%s\"\n",__FUNCTION__);
                #endif
                
                // Error
                return 0;
        }

        // Standard library errors
        {
            no_mem:
                #ifndef NDEBUG
                    ui_print_error("[Standard library] Failed to allocate memory in call to function \"%s\"\n",__FUNCTION__);
                #endif
                
                // Error
                return 0;
        }
    }
}

int load_table_as_json_value ( ui_table **pp_table, json_value *p_value )
{

    // Argument errors
    {
        #ifndef NDEBUG
            if ( pp_table == (void *) 0 )
                goto no_table;
            if ( p_value == (void *) 0 )
                goto no_value;
        #endif
    }

    // Initialized data
    ui_table   *p_table       = 0;
    json_value *p_x           = 0,
                *p_y           = 0,
                *p_max_rows    = 0,
                *p_max_columns = 0,
                *p_file        = 0;

	// Get properties from the json value
    if (p_value->type == JSON_VALUE_OBJECT)
    {

        // Initialized data
        dict *p_dict = p_value->object;

        p_x           = dict_get(p_dict, "x");
        p_y           = dict_get(p_dict, "y");
        p_max_rows    = dict_get(p_dict, "max rows");
		p_max_columns = dict_get(p_dict, "max columns");
        p_file        = dict_get(p_dict, "file");
        
        // Check for missing properties
        if ( ! ( p_x  && p_y ) )
            goto missing_properties;
    }

    // Construct the table
    {
        // Allocate the table
        create_table(pp_table);

        // Return the table
        p_table = *pp_table;

        // Set the x
        if ( p_x->type == JSON_VALUE_INTEGER)
            p_table->x = p_x->integer;
        // Default
        else
            goto wrong_x_type;
        
        // Set the y
        if ( p_y->type == JSON_VALUE_INTEGER)
            p_table->y = p_y->integer;
        // Default
        else
            goto wrong_y_type;
        
        if ( p_file )
            goto csv_parse;

        // Set the max rows
        if ( p_max_rows->type == JSON_VALUE_INTEGER)
            p_table->max_rows = p_max_rows->integer;
        // Default
        else
            goto wrong_max_rows_type;
        
        // Set the max columns
        if ( p_max_columns->type == JSON_VALUE_INTEGER)
            p_table->max_columns = p_max_columns->integer;
        // Default
        else
            goto wrong_max_columns_type;

        csv_parse_done:
        p_table->data          = calloc(p_table->max_rows * p_table->max_columns, sizeof(void *) );
        p_table->column_widths = calloc(p_table->max_columns, sizeof(size_t));

        // Iterate over each column
        for (size_t i = 0; i < p_table->max_columns; i++)

            // Set the column width
            p_table->column_widths[i] = 1;
    }
    // Succses
    return 1;

    // Auxilary branches
    csv_parse:
    {

        // Initialized data
        size_t  len          = ui_load_file(p_file->string, 0, false),
                column_count = 0,
                row_count    = 0;
        char   *buf          = calloc(len+1, sizeof(u8)), 
               *z_buf        = 0;
        
        // Load the CSV file
        ui_load_file(p_file->string, buf, false);
        
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

    wrong_x_type:
    wrong_y_type:
    wrong_max_rows_type:
    wrong_max_columns_type:
    missing_properties:
        return 0;

    // Error handling
    {

        // Argument errors
        {
            no_table:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Table] Null pointer provided for \"pp_table\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_value:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Table] Null pointer provided for \"p_value\" in call to function \"%s\"\n", __FUNCTION__);
                #endif
                
                // Error
                return 0;
        }

        // Missing required construction parameters
        {
            no_label:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Table] No \"label\" property in \"dictionary\" in call to function \"%s\"\n", __FUNCTION__);
                #endif
                
                // Error
                return 0;
            no_x:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Table] No \"x\" property in \"dictionary\" in call to function \"%s\"\n", __FUNCTION__);
                #endif
                
                // Error
                return 0;
            no_y:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Table] No \"y\" property in \"dictionary\" in call to function \"%s\"\n", __FUNCTION__);
                #endif
                
                // Error
                return 0;
        }

        // Standard library errors
        {
            no_mem:
                #ifndef NDEBUG
                    ui_print_error("[Standard Library] Failed to allocate memory in call to funciton \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int hover_table ( ui_table   *p_table , ui_mouse_state  mouse_state)
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
        void (*callback)(ui_table *, ui_mouse_state) = p_table->on_hover[i];

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
                    ui_print_error("[UI] [Table] Null pointer provided for \"table\" in call to function \"%s\"\n", __FUNCTION__);
                #endif
                return 0;
        }
    }
}
 
int click_table ( ui_table   *p_table , ui_mouse_state  mouse_state)
{

    if (mouse_state.button & UI_M1 )
    {

        size_t last_x = 0,
               last_y = 0;

        size_t abs_mY = mouse_state.y - p_table->y,
               abs_mX = mouse_state.x - p_table->x,
               a      = 0;

        p_table->last_y = abs_mY / 12;

        for (size_t i = 0; i < p_table->max_columns; i++)
        {
            if (a <= abs_mX && abs_mX <= a + (8 * p_table->column_widths[i]) + 7)
                p_table->last_x = i;

            a += (8 * p_table->column_widths[i] + 7);
        }

        // Iterate through callbacks
        for (size_t i = 0; i < p_table->on_click_count; i++)
        {
            // Define the callback function
            int (*callback)(ui_table*, ui_mouse_state) = p_table->on_click[i];

            // Call the callback function
            if (callback)
                (*callback)(p_table, mouse_state);

        }

        if (mouse_state.button & UI_M2)
        {
            SDL_SetClipboardText(p_table->data[(p_table->last_y * p_table->max_columns + p_table->last_x)]);
        }
    }
    else if (mouse_state.button & UI_M2 )
    {
        if ( p_table->last_x != -1 && p_table->last_y != -1)
        {
            SDL_SetClipboardText(get_table_cell(p_table, p_table->last_x, p_table->last_y));
            p_table->last_x = -1;
            p_table->last_y = -1;
        }

    }
    return 0;
}

int           release_table              ( ui_table   *p_table, ui_mouse_state mouse_state )
{

    // Iterate through callbacks
    for (size_t i = 0; i < p_table->on_release_count; i++)
    {
        // Define the callback function
        void (*callback)(ui_table*, ui_mouse_state) = p_table->on_release[i];


        // Call the callback function
        if (callback)
            (*callback)(p_table, mouse_state);

    }
    return 0;
}

int add_click_callback_table   ( ui_table  *p_table, void(*callback)(ui_table*, ui_mouse_state))
{
    // TODO: Argument check

    // If this is the first callback, set the max to 1 and 
    if (p_table->on_click_max == 0)
    {
        p_table->on_click_max = 1;
        p_table->on_click = calloc(1, sizeof(void*));
    }

    // Simple heuristic that doubles callbacks lists length when there is no space to store the callback pointer
    if (p_table->on_click_count + 1 > p_table->on_click_max)
    {
        // Double the max
        p_table->on_click_max *= 2;

        realloc(p_table->on_click, p_table->on_click_max);
    }

    // Increment the callback counter and install the new callback
    p_table->on_click[p_table->on_click_count++] = callback;

    return 1;

    // TODO: Error handling
}

int add_hover_callback_table   ( ui_table  *p_table, void(*callback)(ui_table*, ui_mouse_state))
{
    // TODO: Argument check
   
    return 1;

    // TODO: Error handling
}

int           add_release_callback_table ( ui_table  *p_table, void(*callback)(ui_table*, ui_mouse_state))
{
    // TODO: Argument check

    // If this is the first callback, set the max to 1 and 
    if (p_table->on_release_max == 0)
    {
        p_table->on_release_max = 1;
        p_table->on_release = calloc(1, sizeof(void*));
    }

    // Simple heuristic that doubles callbacks lists length when there is no space to store the callback pointer
    if (p_table->on_release_count + 1 > p_table->on_release_max)
    {
        // Double the max
        p_table->on_release_max *= 2;

        realloc(p_table->on_release, p_table->on_release_max);
    }

    // Increment the callback counter and install the new callback
    p_table->on_release[p_table->on_release_count++] = callback;

    return 1;

    // TODO: Error handling
}

char *get_table_cell(ui_table* p_table, size_t x, size_t y)
{

    return p_table->data[y*p_table->max_columns+x];
}

int set_table_cell(ui_table* p_table, size_t x, size_t y, char* cell_text)
{
    p_table->data[y * p_table->max_columns + x] = cell_text;

    size_t b = strlen(cell_text);

    if ( p_table->column_widths[x] < b )
        p_table->column_widths[x] = b;

    return 1;
}

int draw_table ( ui_window  *window, ui_table *table )
{
    ui_instance *instance = ui_get_active_instance();
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

            if (table->last_x == j && table->last_y == i)
            {
                SDL_SetRenderDrawColor(window->renderer, (u8)instance->accent_3, (u8) (instance->accent_3 >> 8), (u8)(instance->accent_3 >> 16), 0xff);
                SDL_RenderFillRect(window->renderer, &r);
            }

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

bool          table_in_bounds            ( ui_table  *table, ui_mouse_state mouse_state )
{
    // Initialized data
	i32  x = table->x,
		 y = table->y,
		 w = 0,
		 h = table->max_rows*12;
	
	// Check for bounds
    for (size_t i = 0; i < table->max_columns; i++)
        w += (table->column_widths[i] * 8) + 7;

    table->w = w;

	if (mouse_state.x >= x && mouse_state.y >= y && mouse_state.x <= x + w && mouse_state.y <= y + h)
		return true;

	return false;

}

int           destroy_table              ( ui_table  *p_button )
{

    // Argument check
    {
        if (p_button == (void*)0)
            goto no_button;
    }
    
    return 0;

    // Error handling
    {

        // Argument errors
        {
            no_button:
                #ifndef NDEBUG
                    ui_print_error("[UI] [Button] Null pointer provided for \"p_button\" in call to function \"%s\"\n", __FUNCTION__);
                #endif
                
                // Error
                return 0;
        }
    }
}
