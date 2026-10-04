#include <glyph/green_button.h>

void green_button_draw ( green_button *p_green_button, window *p_window )
{
    rect b = p_green_button->_button._mono_glyph._composition._glyph._bounds;

    p_window->pfn_draw_button(
        p_window, 
        b.origin.x,
        b.origin.y, 
        b.extent.x, 
        b.extent.y, 
        "green"
    );

    composition_draw((composition *)p_green_button, p_window);
}