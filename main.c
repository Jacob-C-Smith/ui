#include <stdio.h>
#include <stdlib.h>

#include <core/log.h>

#include <ui/ui.h>
#include <window/window.h>
#include <window/application_window.h>
#include <glyph/rectangle.h>
#include <glyph/character.h>
#include <glyph/row.h>
#include <glyph/column.h>
#include <glyph/mono_glyph.h>
#include <glyph/border.h>
#include <glyph/scroller.h>

int main ( int argc, const char *argv[] )
{
    (void) argc;
    (void) argv;
    window _window = { 0 };

    application_window_construct((application_window *)&_window, "ui");

    // glyph *p_glyph = ;
    glyph *p_border = (glyph *)row_from_arguments(
        1,
        (glyph *)border_construct(
            (glyph *)scroller_construct(
                (glyph *)column_from_arguments
                (
                    2,
                    row_from_arguments(
                        4,
                        character_construct('a'),
                        rectangle_construct((rect){.origin={0,0},.extent={50,100}}),
                        column_from_arguments(
                            3,
                            character_construct('X'),
                            character_construct('Y'),
                            character_construct('Z')
                        ),
                        character_construct('b')
                    ),
                    row_from_arguments(
                        3,
                        character_construct('x'),
                        rectangle_construct((rect){.origin={0,0},.extent={100,50}}),
                        character_construct('y')
                    )
                ), 
                32
            ),
        8)
    );

    _window.pfn_set_contents(&_window, p_border);
    _window.pfn_redraw(&_window);
    
    return 0;
}