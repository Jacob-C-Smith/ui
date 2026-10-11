#pragma once

#include <ui/ui.h>

textbox    *textbox_construct         ( const char *text );
void        textbox_text_set          ( textbox *p_textbox, const char *text );
const char *textbox_text_get          ( textbox *p_textbox );
float       textbox_cursor_x_get      ( textbox *p_textbox );
void        textbox_cursor_set_from_x ( textbox *p_textbox, float x );
