#include <glyph/label.h>

label *label_construct ( const char *text )
{
    label *p_label = default_allocator(NULL, sizeof(label));

    mono_glyph_construct((mono_glyph *)p_label, (glyph *)row_from_string(text, false, false, 30.0));

    return p_label;
}
