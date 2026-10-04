#include <glyph/button.h>

button *button_construct ( void )
{
    button *p_button = default_allocator(NULL, sizeof(button));

    mono_glyph_construct((mono_glyph *)p_button, (glyph *)row_construct());

    return p_button;
}
