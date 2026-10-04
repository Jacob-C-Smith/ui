#include <glyph/label.h>

label *label_construct ( void )
{
    label *p_label = default_allocator(NULL, sizeof(label));

    mono_glyph_construct((mono_glyph *)p_label, (glyph *)row_construct());

    return p_label;
}
