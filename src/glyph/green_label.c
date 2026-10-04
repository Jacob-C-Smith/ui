#include <glyph/green_label.h>

void green_label_draw ( green_label *p_green_label, window *p_window )
{
    rect b = p_green_label->_label._mono_glyph._composition._glyph._bounds;

    p_window->pfn_draw_label(
        p_window, 
        b.origin.x,
        b.origin.y, 
        b.extent.x, 
        b.extent.y, 
        "green"
    );

    composition_draw((composition *)p_green_label, p_window);
}