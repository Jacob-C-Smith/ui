#include <glyph/blue_checkbox.h>

void blue_checkbox_draw ( blue_checkbox *p_blue_checkbox, window *p_window )
{
    rect b = p_blue_checkbox->_checkbox._mono_glyph._composition._glyph._bounds;

    composition_draw((composition *)p_blue_checkbox, p_window);

    p_window->pfn_draw_label(
        p_window, 
        b.origin.x,
        b.origin.y, 
        b.extent.x, 
        b.extent.y, 
        "blue"
    );
}