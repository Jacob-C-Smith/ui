#include <glyph/blue_radio_button.h>

void blue_radio_button_draw ( blue_radio_button *p_blue_radio_button, window *p_window )
{
    rect b = p_blue_radio_button->_radio_button._mono_glyph._composition._glyph._bounds;

    composition_draw((composition *)p_blue_radio_button, p_window);

    p_window->pfn_draw_label(
        p_window, 
        b.origin.x,
        b.origin.y, 
        b.extent.x, 
        b.extent.y, 
        "blue"
    );
}