#include <glyph/menu.h>

extern point column_adjust_child ( column *p_column, glyph *p_child, point cursor );
extern rect composition_bounds_get (composition *p_composition);

rect menu_bounds_get ( menu *p_menu )
{
    if ( p_menu->_open )
    {
        return composition_bounds_get((composition *)p_menu);
    }
    else
    {
        glyph *p_first = p_menu->_column._composition._glyph.pfn_child((glyph *)p_menu, 0);
        if ( p_first )
        {
            return p_first->pfn_bounds_get(p_first);
        }
        return (rect){ {0,0}, {0,0} };
    }
}

void menu_adjust ( menu *p_menu, point cursor )
{
    rect b = menu_bounds_get(p_menu);
    float w = cursor.x - p_menu->_column._composition._position.x;
    float h = cursor.y - p_menu->_column._composition._position.y;
    p_menu->_column._composition._size = (rect)
    {
        .origin = p_menu->_column._composition._position,
        .extent = {
            b.extent.x > w ? b.extent.x : w,
            b.extent.y > h ? b.extent.y : h
        }
    };
    p_menu->_column._composition._glyph._bounds = p_menu->_column._composition._size;
}

extern bool composition_intersects ( composition *p_composition, point p );
extern glyph *composition_find ( composition *p_composition, point p );

bool menu_intersects ( menu *p_menu, point p )
{
    if ( p_menu->_open )
    {
        return composition_intersects((composition *)p_menu, p);
    }
    else
    {
        glyph *p_first = p_menu->_column._composition._glyph.pfn_child((glyph *)p_menu, 0);
        if ( p_first )
        {
            return p_first->pfn_intersects(p_first, p);
        }
        return false;
    }
}

glyph *menu_find ( menu *p_menu, point p )
{
    if ( p_menu->_open )
    {
        return composition_find((composition *)p_menu, p);
    }
    else
    {
        if ( menu_intersects(p_menu, p) )
        {
            glyph *p_first = p_menu->_column._composition._glyph.pfn_child((glyph *)p_menu, 0);
            if ( p_first )
            {
                glyph *p_found = p_first->pfn_find(p_first, p);
                if ( p_found ) return p_found;
            }
            return (glyph *)p_menu;
        }
        return NULL;
    }
}

void menu_draw ( menu *p_menu, window *p_window )
{
    if ( p_menu->_open )
        composition_draw((composition *)p_menu, p_window);
    else
    {
        glyph *p_first = p_menu->_column._composition._glyph.pfn_child((glyph *)p_menu, 0);
        if ( p_first )
            p_first->pfn_draw(p_first, p_window);
    }
}

menu *menu_construct ( void )
{
    menu *p_menu = default_allocator(NULL, sizeof(menu));
    
    composition_construct((composition *)p_menu);
    p_menu->_column._composition._glyph.pfn_adjust_child = (fn_glyph_adjust_child *) column_adjust_child;
    
    p_menu->_column._composition._glyph.pfn_draw = (fn_glyph_draw *) menu_draw;
    p_menu->_column._composition._glyph.pfn_bounds_get = (fn_glyph_bounds_get *) menu_bounds_get;
    p_menu->_column._composition._glyph.pfn_adjust = (fn_glyph_adjust *) menu_adjust;
    p_menu->_column._composition._glyph.pfn_intersects = (fn_glyph_intersects *) menu_intersects;
    p_menu->_column._composition._glyph.pfn_find = (fn_glyph_find *) menu_find;
    
    p_menu->_open = false;

    return p_menu;
}
