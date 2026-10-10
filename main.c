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
#include <glyph/margin.h>
#include <glyph/border.h>
#include <glyph/padding.h>
#include <glyph/scroller.h>
#include <glyph/overlay.h>
#include <glyph/menu.h>
#include <glyph/menu_item.h>
#include <factory/gui_factory.h>
#include <command/print_command.h>
#include <command/menu_toggle.h>
#include <glyph/checkbox.h>
#include <glyph/radio_button.h>

key_map *setup_key_map ( void );
glyph   *setup_menu_bar ( void );

int main ( int argc, const char *argv[] )
{
    (void) argc;
    (void) argv;

    char _text[128] = { 'p', 'q', '\0' };
    char *p_text = _text;

    application_window *p_window      = application_window_construct(" UI ");
    gui_factory        *p_gui_factory = gui_factory_instance();
    label              *l             = p_gui_factory->pfn_label_construct(p_gui_factory, "pq");
    button             *b             = p_gui_factory->pfn_button_construct(p_gui_factory, "PQ");
    radio_button_group *r             = p_gui_factory->pfn_radio_button_group_construct(p_gui_factory);
    checkbox_group     *c             = p_gui_factory->pfn_checkbox_group_construct(p_gui_factory);

    p_window->p_key_map = setup_key_map();
    
    b->_mono_glyph._composition._glyph.pfn_command_set(b, (command *) print_command_construct("hi"));

    r->_composition._glyph.pfn_insert
    (
        (glyph *)r,
        row_from_arguments
        (
            3,
            p_gui_factory->pfn_radio_button_construct(p_gui_factory, r, " ABC "),
            p_gui_factory->pfn_radio_button_construct(p_gui_factory, r, " IJK "),
            p_gui_factory->pfn_radio_button_construct(p_gui_factory, r, " XYZ ")
        ),
        0
    );

    c->_composition._glyph.pfn_insert
    (
        (glyph *)c,
        column_from_arguments
        (
            3,
            p_gui_factory->pfn_checkbox_construct(p_gui_factory, " 123 "),
            p_gui_factory->pfn_checkbox_construct(p_gui_factory, " 456 "),
            p_gui_factory->pfn_checkbox_construct(p_gui_factory, " 789 ")
        ),
        0
    );

    glyph *main_doc = (glyph *)column_from_arguments
        (
            1,
            (glyph *)margin_construct
            (
                (glyph *)border_construct
                (
                    (glyph *)scroller_construct
                    (
                        (glyph *)padding_construct
                        (
                            (glyph *)column_from_arguments
                            (
                                5,
                                (glyph *)row_from_arguments
                                (
                                    4,
                                    character_construct('a', false, false, 30.0),
                                    rectangle_construct((rect){.origin={0,0},.extent={25,50}}),
                                    column_from_arguments
                                    (
                                        3,
                                        character_construct('X', false, false, 30.0),
                                        (glyph *) l,
                                        character_construct('Z', false, false, 30.0)
                                    ),
                                    character_construct('b', false, false, 30.0)
                                ),
                                (glyph *)row_from_arguments
                                (
                                    3,
                                    character_construct('x', false, false, 30.0),
                                    rectangle_construct((rect){.origin={0,0},.extent={50,25}}),
                                    character_construct('y', false, false, 30.0)
                                ),
                                (glyph *)b,
                                (glyph *)r,
                                (glyph *)c
                            ), 
                        128),
                    32),
                8),
            64)
        );

    glyph *p_root = (glyph *)overlay_from_arguments(
        2,
        main_doc,
        setup_menu_bar()
    );

    p_window->_window.pfn_set_contents(
        (window *) p_window, 
        p_root
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

glyph *setup_menu_bar ( void )
{
    gui_factory *p_gui_factory = gui_factory_instance();

    glyph *p_file_menu  = p_gui_factory->pfn_menu_construct(p_gui_factory);
    {
        glyph *p_file_title = (glyph *) p_gui_factory->pfn_menu_item_construct(p_gui_factory, "   File   ");
        glyph *p_file_new   = (glyph *) p_gui_factory->pfn_menu_item_construct(p_gui_factory, " New ");
        glyph *p_file_open  = (glyph *) p_gui_factory->pfn_menu_item_construct(p_gui_factory, " Open ");
        glyph *p_file_save  = (glyph *) p_gui_factory->pfn_menu_item_construct(p_gui_factory, " Save ");
        glyph *p_file_close = (glyph *) p_gui_factory->pfn_menu_item_construct(p_gui_factory, " Close ");
        
        p_file_new->pfn_command_set(p_file_new,     (command *) print_command_construct("File > New"));
        p_file_open->pfn_command_set(p_file_open,   (command *) print_command_construct("File > Open"));
        p_file_save->pfn_command_set(p_file_save,   (command *) print_command_construct("File > Save"));
        p_file_close->pfn_command_set(p_file_close, (command *) print_command_construct("File > Close"));

        p_file_menu->pfn_insert(p_file_menu, p_file_title, 0);
        p_file_menu->pfn_insert(p_file_menu, p_file_new  , 1);
        p_file_menu->pfn_insert(p_file_menu, p_file_open , 2);
        p_file_menu->pfn_insert(p_file_menu, p_file_save , 3);
        p_file_menu->pfn_insert(p_file_menu, p_file_close, 4);

        p_file_title->pfn_command_set(p_file_title, (command *)menu_toggle_construct(p_file_menu));
    }

    glyph *p_edit_menu  = p_gui_factory->pfn_menu_construct(p_gui_factory);
    {
        glyph *p_edit_title = (glyph *) p_gui_factory->pfn_menu_item_construct(p_gui_factory, "   Edit   ");
        glyph *p_edit_undo  = (glyph *) p_gui_factory->pfn_menu_item_construct(p_gui_factory, " Undo ");
        glyph *p_edit_redo  = (glyph *) p_gui_factory->pfn_menu_item_construct(p_gui_factory, " Redo ");
        glyph *p_edit_cut   = (glyph *) p_gui_factory->pfn_menu_item_construct(p_gui_factory, " Cut ");
        glyph *p_edit_copy  = (glyph *) p_gui_factory->pfn_menu_item_construct(p_gui_factory, " Copy ");
        glyph *p_edit_paste = (glyph *) p_gui_factory->pfn_menu_item_construct(p_gui_factory, " Paste ");
        
        p_edit_undo->pfn_command_set(p_edit_undo,   (command *) print_command_construct("Edit > Undo"));
        p_edit_redo->pfn_command_set(p_edit_redo,   (command *) print_command_construct("Edit > Redo"));
        p_edit_cut->pfn_command_set(p_edit_cut,     (command *) print_command_construct("Edit > Cut"));
        p_edit_copy->pfn_command_set(p_edit_copy,   (command *) print_command_construct("Edit > Copy"));
        p_edit_paste->pfn_command_set(p_edit_paste, (command *) print_command_construct("Edit > Paste"));
        
        p_edit_menu->pfn_insert(p_edit_menu, p_edit_title, 0);
        p_edit_menu->pfn_insert(p_edit_menu, p_edit_undo , 1);
        p_edit_menu->pfn_insert(p_edit_menu, p_edit_redo , 2);
        p_edit_menu->pfn_insert(p_edit_menu, p_edit_cut  , 3);
        p_edit_menu->pfn_insert(p_edit_menu, p_edit_copy , 4);
        p_edit_menu->pfn_insert(p_edit_menu, p_edit_paste, 5);

        p_edit_title->pfn_command_set(p_edit_title, (command *)menu_toggle_construct(p_edit_menu));
    }

    return (glyph *) row_from_arguments(2,
            p_file_menu,
            p_edit_menu
    );
}