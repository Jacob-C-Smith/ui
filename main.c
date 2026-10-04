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
#include <factory/gui_factory.h>

int main ( int argc, const char *argv[] )
{
    (void) argc;
    (void) argv;
    window _window = { 0 };
    gui_factory *p_gui_factory = gui_factory_instance();

    application_window_construct((application_window *)&_window, "ui");

    glyph *l = p_gui_factory->pfn_label_construct(p_gui_factory);
    glyph *b = p_gui_factory->pfn_button_construct(p_gui_factory);
    
    l->pfn_insert(l, (glyph *)row_from_string("pq"), 0);
    b->pfn_insert(b, (glyph *)row_from_string("PQ"), 0);

    glyph *p_border = (glyph *)row_from_arguments(
        1,
        (glyph *)border_construct(
            (glyph *)scroller_construct(
                (glyph *)column_from_arguments
                (
                    3,
                    row_from_arguments(
                        4,
                        character_construct('a'),
                        rectangle_construct((rect){.origin={0,0},.extent={50,100}}),
                        column_from_arguments(
                            3,
                            character_construct('X'),
                            l,
                            character_construct('Z')
                        ),
                        character_construct('b')
                    ),
                    row_from_arguments(
                        3,
                        character_construct('x'),
                        rectangle_construct((rect){.origin={0,0},.extent={100,50}}),
                        character_construct('y')
                    ),
                    b
                ), 
                32
            ),
        8)
    );

    _window.pfn_set_contents(&_window, p_border);
    _window.pfn_redraw(&_window);
    
    return 0;
}