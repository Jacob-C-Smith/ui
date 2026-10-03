#include <glyph/row.h>

point row_adjust_child ( row *p_row, glyph *p_child, point cursor );

row *row_construct ( void )
{
    row *p_row = default_allocator(NULL, sizeof(row));
    
    composition_construct((composition *)p_row);
    
    p_row->_composition._glyph.pfn_adjust_child = (fn_glyph_adjust_child *) row_adjust_child;

    return p_row;
}

point row_adjust_child ( row *p_row, glyph *p_child, point cursor )
{
    (void)p_row;
    return (point)
    {
        cursor.x + p_child->_bounds.extent.x,
        cursor.y
    };
}
