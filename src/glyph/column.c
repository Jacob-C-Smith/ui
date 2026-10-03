#include <glyph/column.h>

point column_adjust_child ( column *p_column, glyph *p_child, point cursor );

column *column_construct ( void )
{
    column *p_column = default_allocator(NULL, sizeof(column));
    
    composition_construct((composition *)p_column);
    
    p_column->_composition._glyph.pfn_adjust_child = (fn_glyph_adjust_child *) column_adjust_child;

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
