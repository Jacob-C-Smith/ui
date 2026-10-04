#include <glyph/blue_label.h>

void blue_label_draw ( blue_label *p_blue_label, window *p_window )
{
    rect b = p_blue_label->_label._mono_glyph._composition._glyph._bounds;

    p_window->pfn_draw_label(
        p_window, 
        b.origin.x,
        b.origin.y, 
        b.extent.x, 
        b.extent.y, 
        "blue"
    );

    composition_draw((composition *)p_blue_label, p_window);
}