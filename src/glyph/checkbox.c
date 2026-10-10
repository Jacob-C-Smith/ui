#include <glyph/checkbox.h>

void checkbox_click ( rectangle *p_rectangle );

checkbox *checkbox_construct( const char *text )
{
    checkbox *p_checkbox = default_allocator(NULL, sizeof(checkbox));

    glyph *p_rectangle = (glyph *)rectangle_construct((rect){{0}, {30, 30}});
    p_rectangle->pfn_command_set(p_rectangle, (command *)checkbox_set_command_construct(p_checkbox, 0));
    p_rectangle->pfn_click = (fn_glyph_click *) checkbox_click;

    mono_glyph_construct
    (
        (mono_glyph *)p_checkbox, 
        (glyph *)row_from_arguments
        (
            2, 
            p_rectangle, 
            row_from_string(text, false, false, 30.0f)
        )
    );

    return p_checkbox;
}

void checkbox_click ( rectangle *p_rectangle )
{
    p_rectangle->fill = !p_rectangle->fill;
    if ( p_rectangle->_glyph.p_command ) p_rectangle->_glyph.p_command->pfn_execute(p_rectangle->_glyph.p_command);
}
