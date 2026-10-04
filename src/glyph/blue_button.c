#include <glyph/blue_button.h>

void blue_button_draw ( blue_button *p_blue_button, window *p_window )
{
    rect b = p_blue_button->_button._mono_glyph._composition._glyph._bounds;

    p_window->pfn_draw_button(
        p_window, 
        b.origin.x,
        b.origin.y, 
        b.extent.x, 
        b.extent.y, 
        "blue"
    );

    composition_draw((composition *)p_blue_button, p_window);
}