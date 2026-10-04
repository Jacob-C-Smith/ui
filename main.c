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
#include <command/print_command.h>

key_map *setup_key_map ( void );

int main ( int argc, const char *argv[] )
{
    (void) argc;
    (void) argv;

    application_window *p_window      = application_window_construct(" UI ");
    gui_factory        *p_gui_factory = gui_factory_instance();
    label  *l = p_gui_factory->pfn_label_construct(p_gui_factory, "pq");
    button *b = p_gui_factory->pfn_button_construct(p_gui_factory, "PQ");

    p_window->p_key_map = setup_key_map();

    b->pfn_command_set(b, (command *) print_command_construct("hi"));

    p_window->_window.pfn_set_contents
    (
        (window *) p_window, 
        (glyph *) column_from_arguments
        (
            1,
            (glyph *)border_construct
            (
                (glyph *)scroller_construct
                (
                    (glyph *)column_from_arguments
                    (
                        3,
                        row_from_arguments
                        (
                            4,
                            character_construct('a'),
                            rectangle_construct((rect){.origin={0,0},.extent={25,50}}),
                            column_from_arguments
                            (
                                3,
                                character_construct('X'),
                                (glyph *) l,
                                character_construct('Z')
                            ),
                            character_construct('b')
                        ),
                        row_from_arguments
                        (
                            3,
                            character_construct('x'),
                            rectangle_construct((rect){.origin={0,0},.extent={50,25}}),
                            character_construct('y')
                        ),
                        (glyph *) b
                    ), 
                    32
                ),
            8)
        )
    );

    p_window->_window.pfn_redraw((window *)p_window);
    
    return EXIT_SUCCESS;
}

key_map *setup_key_map ( void )
{
    key_map *p_key_map = key_map_construct();

    key_map_put(p_key_map, 'h', (command *) print_command_construct("hello"));
    key_map_put(p_key_map, 'i', (command *) print_command_construct("howdy"));

    return p_key_map;
}
