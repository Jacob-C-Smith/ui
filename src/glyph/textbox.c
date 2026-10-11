#include <glyph/textbox.h>
#include <glyph/row.h>
#include <glyph/mono_glyph.h>
#include <string.h>

void  textbox_click        ( textbox *p_textbox );
void  textbox_key          ( textbox *p_textbox, char c );
void  textbox_focus        ( textbox *p_textbox, bool focused );
rect  textbox_bounds_get   ( textbox *p_textbox );
void  textbox_position_set ( textbox *p_textbox, point _point );
void  textbox_compose      ( textbox *p_textbox );
void  textbox_size         ( textbox *p_textbox, window *p_window );
bool  textbox_intersects   ( textbox *p_textbox, point p );
glyph *textbox_find        ( textbox *p_textbox, point p );
void  textbox_draw         ( textbox *p_textbox, window *p_window );

static void textbox_rebuild_text ( textbox *p_textbox )
{
    row *p_new_row = row_from_string(p_textbox->text, false, false, p_textbox->font_size);
    glyph *p_new_glyph = (glyph *)p_new_row;
    window *p_window = NULL;

    p_new_glyph->pfn_parent_set(p_new_glyph, (glyph *)p_textbox);

    array_set(p_textbox->_mono_glyph._composition.p_array, 0, p_new_glyph);

    p_window = p_textbox->_mono_glyph._composition._glyph.pfn_window_get((glyph *)p_textbox);
    p_textbox->_mono_glyph._composition._glyph.pfn_compose((glyph *)p_textbox);
    if ( p_window )
        p_textbox->_mono_glyph._composition._glyph.pfn_size((glyph *)p_textbox, p_window);
}

textbox *textbox_construct ( const char *text )
{
    textbox *p_textbox = default_allocator(NULL, sizeof(textbox));

    if ( NULL == text ) text = "";
    strncpy(p_textbox->text, text, sizeof(p_textbox->text) - 1);
    p_textbox->text[sizeof(p_textbox->text) - 1] = '\0';
    p_textbox->length = strlen(p_textbox->text);
    p_textbox->cursor_index = p_textbox->length;
    p_textbox->last_click_x = -1.0f;
    p_textbox->is_focused = false;
    p_textbox->font_size = 30.0f;
    p_textbox->min_width = 160.0f;
    p_textbox->min_height = 38.0f;

    mono_glyph_construct((mono_glyph *)p_textbox, (glyph *)row_from_string(p_textbox->text, false, false, p_textbox->font_size));

    p_textbox->_mono_glyph._composition._glyph.pfn_click        = (fn_glyph_click *)        textbox_click;
    p_textbox->_mono_glyph._composition._glyph.pfn_key          = (fn_glyph_key *)          textbox_key;
    p_textbox->_mono_glyph._composition._glyph.pfn_focus        = (fn_glyph_focus *)        textbox_focus;
    p_textbox->_mono_glyph._composition._glyph.pfn_bounds_get   = (fn_glyph_bounds_get *)   textbox_bounds_get;
    p_textbox->_mono_glyph._composition._glyph.pfn_position_set = (fn_glyph_position_set *) textbox_position_set;
    p_textbox->_mono_glyph._composition._glyph.pfn_compose      = (fn_glyph_compose *)      textbox_compose;
    p_textbox->_mono_glyph._composition._glyph.pfn_size         = (fn_glyph_size *)         textbox_size;
    p_textbox->_mono_glyph._composition._glyph.pfn_intersects   = (fn_glyph_intersects *)   textbox_intersects;
    p_textbox->_mono_glyph._composition._glyph.pfn_find         = (fn_glyph_find *)         textbox_find;
    p_textbox->_mono_glyph._composition._glyph.pfn_draw         = (fn_glyph_draw *)         textbox_draw;

    return p_textbox;
}

void textbox_click ( textbox *p_textbox )
{
    p_textbox->is_focused = true;
    if ( p_textbox->last_click_x >= 0.0f )
    {
        textbox_cursor_set_from_x(p_textbox, p_textbox->last_click_x);
        p_textbox->last_click_x = -1.0f;
    }
    if ( p_textbox->_mono_glyph._composition._glyph.p_command )
        p_textbox->_mono_glyph._composition._glyph.p_command->pfn_execute(p_textbox->_mono_glyph._composition._glyph.p_command);
}

void textbox_focus ( textbox *p_textbox, bool focused )
{
    p_textbox->is_focused = focused;
}

void textbox_key ( textbox *p_textbox, char c )
{
    if ( !p_textbox->is_focused ) return;

    if ( c == (char)UI_KEY_LEFT )
    {
        if ( p_textbox->cursor_index > 0 )
            p_textbox->cursor_index--;
    }
    else if ( c == (char)UI_KEY_RIGHT )
    {
        if ( p_textbox->cursor_index < p_textbox->length )
            p_textbox->cursor_index++;
    }
    else if ( c == (char)UI_KEY_HOME ) p_textbox->cursor_index = 0;
    else if ( c == (char)UI_KEY_END ) p_textbox->cursor_index = p_textbox->length;
    else if ( c == (char)UI_KEY_BACKSPACE )
    {
        if ( p_textbox->cursor_index > 0 )
        {
            memmove(
                &p_textbox->text[p_textbox->cursor_index - 1],
                &p_textbox->text[p_textbox->cursor_index],
                p_textbox->length - p_textbox->cursor_index + 1
            );
            p_textbox->length--;
            p_textbox->cursor_index--;
            textbox_rebuild_text(p_textbox);
        }
    }
    else if ( c == (char)UI_KEY_DELETE )
    {
        if ( p_textbox->cursor_index < p_textbox->length )
        {
            memmove(
                &p_textbox->text[p_textbox->cursor_index],
                &p_textbox->text[p_textbox->cursor_index + 1],
                p_textbox->length - p_textbox->cursor_index
            );
            p_textbox->length--;
            textbox_rebuild_text(p_textbox);
        }
    }
    else if ( (unsigned char)c >= 32 && (unsigned char)c <= 126 )
    {
        if ( p_textbox->length < sizeof(p_textbox->text) - 1 )
        {
            memmove(
                &p_textbox->text[p_textbox->cursor_index + 1],
                &p_textbox->text[p_textbox->cursor_index],
                p_textbox->length - p_textbox->cursor_index + 1
            );
            p_textbox->text[p_textbox->cursor_index] = c;
            p_textbox->length++;
            p_textbox->cursor_index++;
            textbox_rebuild_text(p_textbox);
        }
    }
}

rect textbox_bounds_get ( textbox *p_textbox )
{
    return p_textbox->_mono_glyph._composition._glyph._bounds;
}

void textbox_position_set ( textbox *p_textbox, point _point )
{
    glyph *p_child = NULL;

    p_textbox->_mono_glyph._composition._position = _point;
    p_textbox->_mono_glyph._composition._glyph._bounds.origin = _point;

    p_child = composition_child((composition *)p_textbox, 0);
    if ( p_child )
        p_child->pfn_position_set(p_child, (point){ _point.x + 10.0f, _point.y + 6.0f });
}

void textbox_compose ( textbox *p_textbox )
{
    glyph *p_child = composition_child((composition *)p_textbox, 0);
    if ( p_child )
    {
        p_child->pfn_position_set(p_child, (point){ p_textbox->_mono_glyph._composition._position.x + 10.0f, p_textbox->_mono_glyph._composition._position.y + 6.0f });
        p_child->pfn_compose(p_child);
    }
}

void textbox_size ( textbox *p_textbox, window *p_window )
{
    glyph *p_child = NULL;
    rect cb = { 0 };
    float padding_x = 10.0f;
    float padding_y = 6.0f;
    float min_width = 0.0f;
    float min_height = 0.0f;
    float w = 0.0f; 
    float h = 0.0f; 

    mono_glyph_size((mono_glyph *)p_textbox, p_window);

    p_child = composition_child((composition *)p_textbox, 0);

    if ( p_child )
        cb = p_child->pfn_bounds_get(p_child);

    min_width = p_textbox->min_width > 0 ? p_textbox->min_width : 160.0f;
    min_height = p_textbox->min_height > 0 ? p_textbox->min_height : 38.0f;

    w = cb.extent.x + padding_x * 2.0f;
    if ( w < min_width ) w = min_width;

    h = cb.extent.y + padding_y * 2.0f;
    if ( h < min_height ) h = min_height;

    p_textbox->_mono_glyph._composition._glyph._bounds = (rect)
    {
        .origin = p_textbox->_mono_glyph._composition._position,
        .extent = { w, h }
    };
}

bool textbox_intersects ( textbox *p_textbox, point p )
{
    rect b = p_textbox->_mono_glyph._composition._glyph._bounds;
    return ( b.origin.x <= p.x && (b.origin.x + b.extent.x) >= p.x &&
             b.origin.y <= p.y && (b.origin.y + b.extent.y) >= p.y );
}

glyph *textbox_find ( textbox *p_textbox, point p )
{
    if ( textbox_intersects(p_textbox, p) )
    {
        p_textbox->last_click_x = p.x;
        return (glyph *)p_textbox;
    }
    return NULL;
}

float textbox_cursor_x_get ( textbox *p_textbox )
{
    rect b = p_textbox->_mono_glyph._composition._glyph._bounds;
    float start_x = b.origin.x + 10.0f;
    glyph *p_row = composition_child((composition *)p_textbox, 0);
    glyph *p_char = NULL;

    if ( !p_row || p_textbox->length == 0 || p_textbox->cursor_index == 0 )
        return start_x;

    if ( p_textbox->cursor_index >= p_textbox->length )
    {
        rect row_b = p_row->pfn_bounds_get(p_row);
        return row_b.origin.x + row_b.extent.x;
    }

    p_char = composition_child((composition *)p_row, (int)p_textbox->cursor_index);
    if ( p_char )
    {
        rect char_b = p_char->pfn_bounds_get(p_char);
        return char_b.origin.x;
    }

    return start_x;
}

void textbox_cursor_set_from_x ( textbox *p_textbox, float x )
{
    glyph *p_row = NULL;
    
    if ( p_textbox->length == 0 )
    {
        p_textbox->cursor_index = 0;
        return;
    }

    p_row = composition_child((composition *)p_textbox, 0);
    if ( !p_row )
    {
        p_textbox->cursor_index = 0;
        return;
    }

    for ( size_t i = 0; i < p_textbox->length; i++ )
    {
        glyph *p_char = composition_child((composition *)p_row, (int)i);
        rect char_b = {0};
        float mid_x = 0.0f;

        if ( !p_char ) continue;

        char_b = p_char->pfn_bounds_get(p_char);
        mid_x = char_b.origin.x + (char_b.extent.x / 2.0f);
        if ( x < mid_x )
        {
            p_textbox->cursor_index = i;
            return;
        }
    }

    p_textbox->cursor_index = p_textbox->length;
}

void textbox_draw ( textbox *p_textbox, window *p_window )
{
    rect b = p_textbox->_mono_glyph._composition._glyph._bounds;

    p_window->pfn_draw_textbox(
        p_window,
        (int)b.origin.x,
        (int)b.origin.y,
        (int)b.extent.x,
        (int)b.extent.y,
        "blue",
        p_textbox->is_focused
    );

    composition_draw((composition *)p_textbox, p_window);

    if ( p_textbox->is_focused )
        p_window->pfn_fill_rect(p_window, (int)textbox_cursor_x_get(p_textbox), (int)b.origin.y + 6.0f, 2, (int)b.extent.y - 12.0f);
}

void textbox_text_set ( textbox *p_textbox, const char *text )
{
    if ( NULL == text ) text = "";
    strncpy(p_textbox->text, text, sizeof(p_textbox->text) - 1);
    p_textbox->text[sizeof(p_textbox->text) - 1] = '\0';
    p_textbox->length = strlen(p_textbox->text);
    if ( p_textbox->cursor_index > p_textbox->length )
        p_textbox->cursor_index = p_textbox->length;
    textbox_rebuild_text(p_textbox);
}

const char *textbox_text_get ( textbox *p_textbox )
{
    return p_textbox->text;
}
