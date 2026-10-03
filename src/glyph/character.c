#include <glyph/character.h>

void character_draw ( character *p_character, window *p_window );
void character_size ( character *p_character, window *p_window );

character *character_construct ( char c )
{
    character *p_character = default_allocator(NULL, sizeof(character));
    
    glyph_construct((glyph *)p_character);

    p_character->_glyph.pfn_draw = (fn_glyph_draw *) character_draw;
    p_character->_glyph.pfn_size = (fn_glyph_size *) character_size;
    p_character->_c = c;
    
    return p_character;
}

void character_draw ( character *p_character, window *p_window )
{
    p_window->pfn_draw_char(
        p_window,
        p_character->_c,
        p_character->_glyph._bounds.origin.x,
        p_character->_glyph._bounds.origin.y        
    );
}

void character_size ( character *p_character, window *p_window )
{
    if ( p_window )
    {
        p_character->_glyph.pfn_bounds_set(
            (glyph *)p_character,
            (rect)
            {
                p_character->_glyph._bounds.origin,
                (point)
                {
                    (float)p_window->pfn_char_width(p_window, p_character->_c),
                    (float)p_window->pfn_char_height(p_window, p_character->_c)
                }
            }
        );
    }
}