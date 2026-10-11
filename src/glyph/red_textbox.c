#include <glyph/red_textbox.h>
#include <glyph/textbox.h>
#include <glyph/mono_glyph.h>

void red_textbox_draw ( red_textbox *p_red_textbox, window *p_window )
{
    textbox *p_tb = (textbox *)p_red_textbox;
    rect b = p_tb->_mono_glyph._composition._glyph._bounds;

    p_window->pfn_draw_textbox(
        p_window,
        (int)b.origin.x,
        (int)b.origin.y,
        (int)b.extent.x,
        (int)b.extent.y,
        "red",
        p_tb->is_focused
    );

    composition_draw((composition *)p_red_textbox, p_window);

    if ( p_tb->is_focused )
        p_window->pfn_fill_rect
        (
            p_window, 
            (int)textbox_cursor_x_get(p_tb), 
            (int)b.origin.y + 6.0f, 
            2, 
            (int)b.extent.y - 12.0f
        );
}
