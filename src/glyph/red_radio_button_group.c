#include <glyph/red_radio_button_group.h>

void red_radio_button_group_draw ( red_radio_button_group *p_red_radio_button_group, window *p_window )
{
    rect b = p_red_radio_button_group->_group._composition._glyph._bounds;

    p_window->pfn_draw_label(
        p_window, 
        b.origin.x,
        b.origin.y, 
        b.extent.x, 
        b.extent.y,
        "red"
    );

    composition_draw((composition *)p_red_radio_button_group, p_window);
}
