#include <glyph/row.h>

point row_adjust_child ( row *p_row, glyph *p_child, point cursor );

row *row_construct ( void )
{
    row *p_row = default_allocator(NULL, sizeof(row));
    
    composition_construct((composition *)p_row);
    
    p_row->_composition._glyph.pfn_adjust_child = (fn_glyph_adjust_child *) row_adjust_child;

    return p_row;
}

row *row_from_string ( const char *string )
{
    row *p_row = row_construct();

    for (size_t i = 0; i < strlen(string); i++)
        p_row->_composition._glyph.pfn_insert(
            (glyph *)p_row, 
            (glyph *)character_construct(string[i]),
            i
        );
    
    return p_row;
}

row *row_from_arguments ( size_t count, ... )
{
    va_list list;
    row *p_row = row_construct();

    va_start(list, count);

    for (size_t i = 0; i < count; i++)
        p_row->_composition._glyph.pfn_insert(
            (glyph *)p_row, 
            (glyph *)va_arg(list, void *),
            i
        );

    va_end(list);

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
