#include <glyph/green_checkbox.h>

void green_checkbox_draw ( green_checkbox *p_green_checkbox, window *p_window )
{
    rect b = p_green_checkbox->_checkbox._mono_glyph._composition._glyph._bounds;

    composition_draw((composition *)p_green_checkbox, p_window);
    
    p_window->pfn_draw_label(
        p_window, 
        b.origin.x,
        b.origin.y, 
        b.extent.x, 
        b.extent.y, 
        "green"
    );
}