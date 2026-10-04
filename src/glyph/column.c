#include <glyph/column.h>

point column_adjust_child ( column *p_column, glyph *p_child, point cursor );

column *column_construct ( void )
{
    column *p_column = default_allocator(NULL, sizeof(column));
    
    composition_construct((composition *)p_column);
    
    p_column->_composition._glyph.pfn_adjust_child = (fn_glyph_adjust_child *) column_adjust_child;

    return p_column;
}
column *column_from_strings ( int count, const char *string[] )
{
    column *p_column = column_construct();

    for (int i = 0; i < count; i++)
        p_column->_composition._glyph.pfn_insert(
            (glyph *)p_column, 
            (glyph *)row_from_string(string[i]),
            i
        );
    
    return p_column;
}

column *column_from_arguments ( size_t count, ... )
{
    va_list list;
    column *p_column = column_construct();

    va_start(list, count);

    for (size_t i = 0; i < count; i++)
        p_column->_composition._glyph.pfn_insert(
            (glyph *)p_column, 
            (glyph *)va_arg(list, void *),
            i
        );

    va_end(list);

    return p_column;
}

point column_adjust_child ( column *p_column, glyph *p_child, point cursor )
{
    (void)p_column;
    return (point)
    {
        cursor.x,
        cursor.y + p_child->_bounds.extent.y,
    };
}
