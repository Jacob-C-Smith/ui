#include <stdio.h>
#include <stdlib.h>

#include <core/interfaces.h>
#include <core/log.h>
#include <core/stream.h>

#include <data/array.h>
#include <data/dict.h>

#include <window/window.h>
#include <window/application_window.h>
#include <glyph/rectangle.h>
#include <glyph/character.h>
#include <glyph/row.h>
#include <glyph/column.h>

#include <SDL3/SDL.h>

int main ( int argc, const char *argv[] )
{
    (void) argc;
    (void) argv;
    window _window = { 0 };

    glyph *p_1 = (glyph *)column_construct();
        glyph *p_2 = (glyph *)row_construct();
            glyph *p_3 = (glyph *)character_construct('a');
            glyph *p_4 = (glyph *)rectangle_construct((rect){.origin={0,0},.extent={50,100}});
            glyph *p_5 = (glyph *)column_construct();
                glyph *p_6 = (glyph *)character_construct('X');
                glyph *p_7 = (glyph *)character_construct('Y');
                glyph *p_8 = (glyph *)character_construct('Z');
            glyph *p_9 = (glyph *)character_construct('b');
        glyph *p_10 = (glyph *)row_construct();
            glyph *p_11 = (glyph *)character_construct('x');
            glyph *p_12 = (glyph *)rectangle_construct((rect){.origin={0,0},.extent={100,50}});
            glyph *p_13 = (glyph *)character_construct('y');

    p_5->pfn_insert(p_5, p_6, 0);
    p_5->pfn_insert(p_5, p_7, 1);
    p_5->pfn_insert(p_5, p_8, 2);

    p_2->pfn_insert(p_2, p_3, 0);
    p_2->pfn_insert(p_2, p_4, 1);
    p_2->pfn_insert(p_2, p_5, 2);
    p_2->pfn_insert(p_2, p_9, 3);

    p_10->pfn_insert(p_10, p_11, 0);
    p_10->pfn_insert(p_10, p_12, 0);
    p_10->pfn_insert(p_10, p_13, 0);
    

    p_1->pfn_insert(p_1, p_2, 0);
    p_1->pfn_insert(p_1, p_10, 0);
    
    application_window_construct((application_window *)&_window, "ui");

    _window.pfn_set_contents(&_window, p_1);
    _window.pfn_redraw(&_window);
    
    return 0;
}