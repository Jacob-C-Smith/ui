#include <window/sdl_window.h>

int  sdl_window_redraw      ( sdl_window *p_window );
void sdl_window_draw_rect   ( sdl_window *p_window, int x, int y, int w, int h );
void sdl_window_fill_rect   ( sdl_window *p_window, int x, int y, int w, int h );
int  sdl_window_char_width  ( sdl_window *p_window, char c );
int  sdl_window_char_height ( sdl_window *p_window, char c );
void sdl_window_char_draw   ( sdl_window *p_window, char c, int x, int y );
void sdl_window_draw_button ( sdl_window *p_window, int x, int y, int w, int h, const char *p_button );
void sdl_window_draw_label  ( sdl_window *p_window, int x, int y, int w, int h, const char *p_label );
void sdl_window_click       ( sdl_window *p_window, int x, int y );
void sdl_window_key         ( sdl_window *p_window, char c );

window_impl *sdl_window_construct ( const char *title, window *w)
{
    sdl_window *p_sdl_window = default_allocator(NULL, sizeof(sdl_window));
    
    SDL_Window *_w = NULL;
    SDL_Renderer *_r = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_CreateWindowAndRenderer(title,800,600,SDL_WINDOW_HIGH_PIXEL_DENSITY, &_w, &_r);

    SDL_SetRenderVSync(_r, 1);

    TTF_Init();

    *p_sdl_window = (sdl_window)
    {
        ._window_impl = 
        {
            .pfn_redraw      = (fn_window_impl_redraw *)      sdl_window_redraw,
            .pfn_draw_rect   = (fn_window_impl_draw_rect *)   sdl_window_draw_rect,
            .pfn_fill_rect   = (fn_window_impl_fill_rect *)   sdl_window_fill_rect,
            .pfn_char_width  = (fn_window_impl_char_width *)  sdl_window_char_width,
            .pfn_draw_button = (fn_window_impl_draw_button *) sdl_window_draw_button,
            .pfn_draw_label  = (fn_window_impl_draw_label *)  sdl_window_draw_label,
            .pfn_char_height = (fn_window_impl_char_height *) sdl_window_char_height,
            .pfn_draw_char   = (fn_window_impl_draw_char *)   sdl_window_char_draw,
            .pfn_key         = (fn_window_impl_key *)         sdl_window_key,
            .pfn_click       = (fn_window_impl_click *)       sdl_window_click,
        },
        .p_w = _w,
        .p_r = _r,
        .p_f = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial.ttf", 30.0f),
        .p_window = w,
        .title = title,
    };

    return (window_impl *)p_sdl_window;
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

void sdl_window_char_draw ( sdl_window *p_window, char c, int x, int y )
{
    char _c[2] = { c, '\0' };
    
    SDL_Surface *t = TTF_RenderText_Blended(p_window->p_f, _c, 1,(SDL_Color){0,0,0,255});
    SDL_Texture *u = SDL_CreateTextureFromSurface(p_window->p_r, t);
    SDL_FRect dst = {(float)x,(float)y,0,0};

    SDL_GetTextureSize(u, &dst.w, &dst.h);

    SDL_RenderTexture(p_window->p_r, u, NULL, &dst);

    SDL_DestroyTexture(u);
    SDL_DestroySurface(t);
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

int sdl_window_char_width ( sdl_window *p_window, char c )
{
    int width, height;
    char _c[2] = { c, '\0' };

    TTF_GetStringSize(p_window->p_f, _c, 1, &width, &height);

    return width;
}

int sdl_window_char_height ( sdl_window *p_window, char c )
{
    int width, height;
    char _c[2] = { c, '\0' };

    TTF_GetStringSize(p_window->p_f, _c, 1, &width, &height);

    return height;
}

void sdl_window_click ( sdl_window *p_window, int x, int y )
{
    p_window->p_window->pfn_click(p_window->p_window, x, y);
}

void sdl_window_key ( sdl_window *p_window, char c )
{
    p_window->p_window->pfn_key(p_window->p_window, c);
}