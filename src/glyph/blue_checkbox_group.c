#include <glyph/blue_checkbox_group.h>

void blue_checkbox_group_draw ( blue_checkbox_group *p_blue_checkbox_group, window *p_window )
{
    rect b = p_blue_checkbox_group->_checkbox_group._composition._glyph._bounds;

    p_window->pfn_draw_label(
        p_window, 
        b.origin.x,
        b.origin.y, 
        b.extent.x, 
        b.extent.y, 
        "blue"
    );
    
    composition_draw((composition *)p_blue_checkbox_group, p_window);
}
