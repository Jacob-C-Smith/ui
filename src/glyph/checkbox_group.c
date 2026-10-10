#include <glyph/checkbox_group.h>

checkbox_group *checkbox_group_construct ( void )
{
    checkbox_group *p_group = default_allocator(NULL, sizeof(checkbox_group));
    composition_construct((composition *)p_group);
    return p_group;
}
