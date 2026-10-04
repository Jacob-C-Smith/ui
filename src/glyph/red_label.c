#include <glyph/red_label.h>

void red_label_draw ( red_label *p_red_label, window *p_window )
{
    rect b = p_red_label->_label._mono_glyph._composition._glyph._bounds;

    p_window->pfn_draw_label(
        p_window, 
        b.origin.x,
        b.origin.y, 
        b.extent.x, 
        b.extent.y, 
        "red"
    );

    composition_draw((composition *)p_red_label, p_window);
}