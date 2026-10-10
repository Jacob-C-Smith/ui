#include <window/sdl_window.h>
#include <data/avl.h>

struct font_cache_entry_s
{
    char c;
    bool bold;
    bool italic;
    float size;
    int width;
    int height;
    SDL_Texture *texture;
};

int  sdl_window_set_contents ( sdl_window *p_window );
int  sdl_window_redraw       ( sdl_window *p_window );
void sdl_window_draw_rect    ( sdl_window *p_window, int x, int y, int w, int h );
void sdl_window_fill_rect    ( sdl_window *p_window, int x, int y, int w, int h );
void sdl_window_clear_rect   ( sdl_window *p_window, int x, int y, int w, int h );
void sdl_window_draw_circle  ( sdl_window *p_window, int x, int y, int w, int h );
void sdl_window_fill_circle  ( sdl_window *p_window, int x, int y, int w, int h );
void sdl_window_clear_circle ( sdl_window *p_window, int x, int y, int w, int h );
int  sdl_window_char_width   ( sdl_window *p_window, char c, bool bold, bool italic, float size );
int  sdl_window_char_height  ( sdl_window *p_window, char c, bool bold, bool italic, float size );
void sdl_window_char_draw    ( sdl_window *p_window, char c, bool bold, bool italic, float size, int x, int y );
void sdl_window_draw_button  ( sdl_window *p_window, int x, int y, int w, int h, const char *p_button );
void sdl_window_draw_label   ( sdl_window *p_window, int x, int y, int w, int h, const char *p_label );
void sdl_window_click        ( sdl_window *p_window, int x, int y );
void sdl_window_key          ( sdl_window *p_window, char c );

typedef struct font_cache_entry_s font_cache_entry;

int font_cache_comparator(const void *const p_a, const void *const p_b) 
{
    const font_cache_entry *a = p_a;
    const font_cache_entry *b = p_b;

    if (a->c      != b->c)      return a->c      - b->c;
    if (a->bold   != b->bold)   return a->bold   - b->bold;
    if (a->italic != b->italic) return a->italic - b->italic;
    if (a->size   != b->size)   return (a->size > b->size) ? 1 : -1;

    return 0;
}

void *font_cache_key_accessor(const void *const p_value) 
{
    return (void *)p_value;
}

void *font_cache_destroyer(void *p_value, unsigned long long size) 
{
    font_cache_entry *p_entry = (font_cache_entry *)p_value;

    if (p_entry) 
        if ( p_entry->texture )
            SDL_DestroyTexture(p_entry->texture);
    
    return default_allocator(p_value, (size_t)size);
}

window_impl *sdl_window_construct ( const char *title, window *w)
{
    sdl_window *p_sdl_window = default_allocator(NULL, sizeof(sdl_window));
    avl_tree *p_glyph_cache = NULL;
    SDL_Window *_w = NULL;
    SDL_Renderer *_r = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_CreateWindowAndRenderer(title,800,600,SDL_WINDOW_HIGH_PIXEL_DENSITY, &_w, &_r);

    SDL_SetRenderVSync(_r, 1);

    TTF_Init();
    
    avl_tree_construct(&p_glyph_cache, sizeof(font_cache_entry), font_cache_comparator, font_cache_key_accessor);

    *p_sdl_window = (sdl_window)
    {
        ._window_impl = 
        {
            .pfn_set_contents = (fn_window_impl_set_contents *) sdl_window_set_contents,
            .pfn_redraw       = (fn_window_impl_redraw *)       sdl_window_redraw,
            .pfn_draw_rect    = (fn_window_impl_draw_rect *)    sdl_window_draw_rect,
            .pfn_fill_rect    = (fn_window_impl_fill_rect *)    sdl_window_fill_rect,
            .pfn_clear_rect   = (fn_window_impl_clear_rect *)   sdl_window_clear_rect,
            .pfn_draw_circle  = (fn_window_impl_draw_circle *)  sdl_window_draw_circle,
            .pfn_fill_circle  = (fn_window_impl_fill_circle *)  sdl_window_fill_circle,
            .pfn_clear_circle = (fn_window_impl_clear_circle *) sdl_window_clear_circle,
            .pfn_char_width   = (fn_window_impl_char_width *)   sdl_window_char_width,
            .pfn_draw_button  = (fn_window_impl_draw_button *)  sdl_window_draw_button,
            .pfn_draw_label   = (fn_window_impl_draw_label *)   sdl_window_draw_label,
            .pfn_char_height  = (fn_window_impl_char_height *)  sdl_window_char_height,
            .pfn_draw_char    = (fn_window_impl_draw_char *)    sdl_window_char_draw,
            .pfn_key          = (fn_window_impl_key *)          sdl_window_key,
            .pfn_click        = (fn_window_impl_click *)        sdl_window_click,
        },
        .p_w = _w,
        .p_r = _r,
        .p_f = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial.ttf", 30.0f),
        .p_window = w,
        .title = title,
        .p_glyph_cache = p_glyph_cache,
    };

    return (window_impl *)p_sdl_window;
}

int sdl_window_set_contents ( sdl_window *p_window )
{
    float scale = SDL_GetWindowDisplayScale(p_window->p_w);
    rect b = p_window->p_window->p_contents->_bounds;

    SDL_SetWindowSize(p_window->p_w, b.extent.x / scale, b.extent.y / scale);

    return 1;
}

int sdl_window_redraw ( sdl_window *p_window )
{
    bool done = false;
    
    while (!done) 
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                    done = true;
                    break;
                
                case SDL_EVENT_KEY_DOWN:
                {
                    char c = (char) event.key.key;
                    c = (event.key.mod & SDL_KMOD_SHIFT) ? c - 0x20 : c;
                    c = (event.key.mod & SDL_KMOD_CTRL)  ? c & 0x1f : c;
                    p_window->_window_impl.pfn_key((window_impl *)p_window, c);
                }
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                {
                    SDL_ConvertEventToRenderCoordinates(p_window->p_r, &event);
                    p_window->_window_impl.pfn_click((window_impl *)p_window, event.motion.x, event.motion.y);
                }
                    break;
                default:
                    break;
            }
        } 

        SDL_SetRenderDrawColor(p_window->p_r,255,255,255,255);
        SDL_RenderClear(p_window->p_r);

        SDL_SetRenderDrawColor(p_window->p_r,0,0,0,255);

        p_window->p_window->pfn_draw(p_window->p_window);

        SDL_RenderPresent(p_window->p_r);
    }

    avl_tree_destroy(&p_window->p_glyph_cache, font_cache_destroyer);

    SDL_DestroyRenderer(p_window->p_r);
    SDL_DestroyWindow(p_window->p_w);
    SDL_Quit();

    return 1;
}

void sdl_window_draw_rect ( sdl_window *p_window, int x, int y, int w, int h )
{
    SDL_FRect r = {(float)x,(float)y,(float)w,(float)h};
    
    SDL_RenderRect(p_window->p_r, &r);
}

void sdl_window_fill_rect ( sdl_window *p_window, int x, int y, int w, int h )
{
    SDL_FRect r = {(float)x,(float)y,(float)w,(float)h};
    
    SDL_RenderFillRect(p_window->p_r, &r);
}

void sdl_window_clear_rect ( sdl_window *p_window, int x, int y, int w, int h )
{
    SDL_Color lc = { 0 };
    SDL_FRect r = {(float)x,(float)y,(float)w,(float)h};

    SDL_GetRenderDrawColor(p_window->p_r,&lc.r,&lc.g,&lc.b,&lc.a);

    SDL_SetRenderDrawColor(p_window->p_r, 255,255,255,255);

    sdl_window_fill_rect(p_window, x, y, w, h);

    SDL_SetRenderDrawColor(p_window->p_r,lc.r,lc.g,lc.b,lc.a);
}

void sdl_window_draw_circle(sdl_window *p_window, int x, int y, int w, int h)
{
    long rx = w / 2;
    long ry = h / 2;

    if (rx <= 0 || ry <= 0) {
        return;
    }

    int cx = x + rx;
    int cy = y + ry;

    long rx_sq = rx * rx;
    long ry_sq = ry * ry;

    long curr_x = 0;
    long curr_y = ry;

    long d1 = ry_sq - (rx_sq * ry) + (rx_sq / 4);
    long dx = 2 * ry_sq * curr_x;
    long dy = 2 * rx_sq * curr_y;

    while (dx < dy) {
        SDL_RenderPoint(p_window->p_r, cx + curr_x, cy + curr_y);
        SDL_RenderPoint(p_window->p_r, cx - curr_x, cy + curr_y);
        SDL_RenderPoint(p_window->p_r, cx + curr_x, cy - curr_y);
        SDL_RenderPoint(p_window->p_r, cx - curr_x, cy - curr_y);

        curr_x++;
        dx += 2 * ry_sq;

        if (d1 < 0) {
            d1 += dx + ry_sq;
        } else {
            curr_y--;
            dy -= 2 * rx_sq;
            d1 += dx - dy + ry_sq;
        }
    }

    long d2 = ry_sq * (curr_x * curr_x + curr_x) + (ry_sq / 4) +
              rx_sq * (curr_y - 1) * (curr_y - 1) -
              rx_sq * ry_sq;

    while (curr_y >= 0) {
        SDL_RenderPoint(p_window->p_r, cx + curr_x, cy + curr_y);
        SDL_RenderPoint(p_window->p_r, cx - curr_x, cy + curr_y);
        SDL_RenderPoint(p_window->p_r, cx + curr_x, cy - curr_y);
        SDL_RenderPoint(p_window->p_r, cx - curr_x, cy - curr_y);

        curr_y--;
        dy -= 2 * rx_sq;

        if (d2 > 0) {
            d2 += rx_sq - dy;
        } else {
            curr_x++;
            dx += 2 * ry_sq;
            d2 += dx - dy + rx_sq;
        }
    }
}

void sdl_window_fill_circle(sdl_window *p_window, int x, int y, int w, int h)
{
    long rx = w / 2;
    long ry = h / 2;

    if (rx <= 0 || ry <= 0) {
        return;
    }

    int cx = x + rx;
    int cy = y + ry;

    long rx_sq = rx * rx;
    long ry_sq = ry * ry;

    long curr_x = 0;
    long curr_y = ry;

    long d1 = ry_sq - (rx_sq * ry) + (rx_sq / 4);
    long dx = 2 * ry_sq * curr_x;
    long dy = 2 * rx_sq * curr_y;

    long last_drawn_y = -1;

    while (dx < dy) {
        if (curr_y != last_drawn_y) {
            SDL_RenderLine(p_window->p_r, cx - curr_x, cy + curr_y, cx + curr_x, cy + curr_y);
            SDL_RenderLine(p_window->p_r, cx - curr_x, cy - curr_y, cx + curr_x, cy - curr_y);
            last_drawn_y = curr_y;
        }

        curr_x++;
        dx += 2 * ry_sq;

        if (d1 < 0) {
            d1 += dx + ry_sq;
        } else {
            curr_y--;
            dy -= 2 * rx_sq;
            d1 += dx - dy + ry_sq;
        }
    }

    long d2 = ry_sq * (curr_x * curr_x + curr_x) + (ry_sq / 4) +
              rx_sq * (curr_y - 1) * (curr_y - 1) -
              rx_sq * ry_sq;

    while (curr_y >= 0) {
        if (curr_y != last_drawn_y) {
            SDL_RenderLine(p_window->p_r, cx - curr_x, cy + curr_y, cx + curr_x, cy + curr_y);
            SDL_RenderLine(p_window->p_r, cx - curr_x, cy - curr_y, cx + curr_x, cy - curr_y);
            last_drawn_y = curr_y;
        }

        curr_y--;
        dy -= 2 * rx_sq;

        if (d2 > 0) {
            d2 += rx_sq - dy;
        } else {
            curr_x++;
            dx += 2 * ry_sq;
            d2 += dx - dy + rx_sq;
        }
    }
}

void sdl_window_clear_circle(sdl_window *p_window, int x, int y, int w, int h)
{
    SDL_Color lc = { 0 };
    SDL_FRect r = {(float)x,(float)y,(float)w,(float)h};

    SDL_GetRenderDrawColor(p_window->p_r,&lc.r,&lc.g,&lc.b,&lc.a);

    SDL_SetRenderDrawColor(p_window->p_r, 255,255,255,255);

    sdl_window_fill_circle(p_window, x, y, w, h);

    SDL_SetRenderDrawColor(p_window->p_r,lc.r,lc.g,lc.b,lc.a);
}

font_cache_entry *sdl_window_get_or_create_glyph ( sdl_window *p_window, char c, bool bold, bool italic, float size ) 
{
    font_cache_entry search_key = { .c = c, .bold = bold, .italic = italic, .size = size };
    font_cache_entry *p_entry = NULL;
    avl_tree *tree = (avl_tree *)p_window->p_glyph_cache;
    
    avl_tree_search(tree, &search_key, (void **)&p_entry);

    if (p_entry) return p_entry;
    
    font_cache_entry *p_new_entry = default_allocator(NULL, sizeof(font_cache_entry));
    *p_new_entry = search_key;
    
    int style = TTF_STYLE_NORMAL;
    if (bold) style |= TTF_STYLE_BOLD;
    if (italic) style |= TTF_STYLE_ITALIC;
    
    TTF_SetFontSize(p_window->p_f, size);
    TTF_SetFontStyle(p_window->p_f, style);

    char _c[2] = { c, '\0' };
    SDL_Surface *t = TTF_RenderText_Blended(p_window->p_f, _c, 1,(SDL_Color){0,0,0,255});

    if (t) 
    {
        p_new_entry->texture = SDL_CreateTextureFromSurface(p_window->p_r, t);
        p_new_entry->width = t->w;
        p_new_entry->height = t->h;
        SDL_DestroySurface(t);
    } 
    else
    {
        p_new_entry->texture = NULL;
        p_new_entry->width = 0;
        p_new_entry->height = 0;
    }
    
    avl_tree_insert(tree, p_new_entry);

    return p_new_entry;
}

void sdl_window_char_draw ( sdl_window *p_window, char c, bool bold, bool italic, float size, int x, int y )
{
    font_cache_entry *p_entry = sdl_window_get_or_create_glyph(p_window, c, bold, italic, size);
    
    if ( NULL ==          p_entry ) return;
    if ( NULL == p_entry->texture ) return;
    
    SDL_FRect dst = {(float)x,(float)y,(float)p_entry->width,(float)p_entry->height};

    SDL_RenderTexture(p_window->p_r, p_entry->texture, NULL, &dst);
}

void sdl_window_draw_button ( sdl_window *p_window, int x, int y, int w, int h, const char *p_button)
{
    SDL_Color lc = { 0 };
    SDL_GetRenderDrawColor(p_window->p_r,&lc.r,&lc.g,&lc.b,&lc.a);

    if ( 0 == strcmp("red", p_button) ) 
        SDL_SetRenderDrawColor(p_window->p_r, 255,0,0,255);
    else if ( 0 == strcmp("green", p_button) ) 
        SDL_SetRenderDrawColor(p_window->p_r, 0,255,0,255);
    else
        SDL_SetRenderDrawColor(p_window->p_r, 0,0,255,255);
        
    sdl_window_fill_rect(p_window, x, y, w, h);

    SDL_SetRenderDrawColor(p_window->p_r,lc.r,lc.g,lc.b,lc.a);
}

void sdl_window_draw_label  ( sdl_window *p_window, int x, int y, int w, int h, const char *p_label)
{
    SDL_Color lc = { 0 };
    SDL_GetRenderDrawColor(p_window->p_r,&lc.r,&lc.g,&lc.b,&lc.a);

    if ( 0 == strcmp("red", p_label) ) 
        SDL_SetRenderDrawColor(p_window->p_r, 255,0,0,255);
    else if ( 0 == strcmp("green", p_label) ) 
        SDL_SetRenderDrawColor(p_window->p_r, 0,255,0,255);
    else
        SDL_SetRenderDrawColor(p_window->p_r, 0,0,255,255);

    sdl_window_draw_rect(p_window, x, y, w, h);

    SDL_SetRenderDrawColor(p_window->p_r,lc.r,lc.g,lc.b,lc.a);
}

int sdl_window_char_width ( sdl_window *p_window, char c, bool bold, bool italic, float size )
{
    font_cache_entry *p_entry = sdl_window_get_or_create_glyph(p_window, c, bold, italic, size);
    return p_entry ? p_entry->width : 0;
}

int sdl_window_char_height ( sdl_window *p_window, char c, bool bold, bool italic, float size )
{
    font_cache_entry *p_entry = sdl_window_get_or_create_glyph(p_window, c, bold, italic, size);
    return p_entry ? p_entry->height : 0;
}

void sdl_window_click ( sdl_window *p_window, int x, int y )
{
    p_window->p_window->pfn_click(p_window->p_window, x, y);
}

void sdl_window_key ( sdl_window *p_window, char c )
{
    p_window->p_window->pfn_key(p_window->p_window, c);
}