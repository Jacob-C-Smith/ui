#include <glyph/green_checkbox_group.h>

void green_checkbox_group_draw ( green_checkbox_group *p_green_checkbox_group, window *p_window )
{
    rect b = p_green_checkbox_group->_checkbox_group._composition._glyph._bounds;

    p_window->pfn_draw_label(
        p_window, 
        b.origin.x,
        b.origin.y, 
        b.extent.x, 
        b.extent.y,
        "green"
    );

    composition_draw((composition *)p_green_checkbox_group, p_window);
}
