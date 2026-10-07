#include <glyph/red_checkbox.h>

void red_checkbox_draw ( red_checkbox *p_red_checkbox, window *p_window )
{
    rect b = p_red_checkbox->_checkbox._mono_glyph._composition._glyph._bounds;

    composition_draw((composition *)p_red_checkbox, p_window);
    
    p_window->pfn_draw_label(
        p_window, 
        b.origin.x,
        b.origin.y, 
        b.extent.x, 
        b.extent.y, 
        "red"
    );
}