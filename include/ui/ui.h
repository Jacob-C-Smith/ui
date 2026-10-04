#pragma once

#include <core/interfaces.h>
#include <data/array.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

struct point_s;
struct rect_s;
struct application_window_s;
struct sdl_window_factory_s;
struct sdl_window_s;
struct window_factory_s;
struct window_impl_s;
struct window_s;
struct glyph_s;
struct rectangle_s;
struct character_s;
struct composition_s;
struct row_s;
struct column_s;
struct mono_glyph_s;
struct border_s;
struct scroller_s;
struct compositor_s;
struct null_compositor_s;
struct simple_compositor_s;

typedef struct point_s point;
typedef struct rect_s rect;
typedef struct application_window_s application_window;
typedef struct sdl_window_factory_s sdl_window_factory;
typedef struct sdl_window_s sdl_window;
typedef struct window_factory_s window_factory;
typedef struct window_impl_s window_impl;
typedef struct window_s window;
typedef struct glyph_s glyph;
typedef struct rectangle_s rectangle;
typedef struct character_s character;
typedef struct composition_s composition;
typedef struct row_s row;
typedef struct column_s column;
typedef struct mono_glyph_s mono_glyph;
typedef struct border_s border;
typedef struct scroller_s scroller;
typedef struct compositor_s compositor;
typedef struct null_compositor_s null_compositor;
typedef struct simple_compositor_s simple_compositor; 

typedef int(fn_window_draw)(window *p_window);
typedef int(fn_window_redraw)(window *p_window);
typedef int(fn_window_raise)(window *p_window);
typedef int(fn_window_lower)(window *p_window);
typedef int(fn_window_iconify)(window *p_window);
typedef int(fn_window_deiconify)(window *p_window);
typedef int(fn_window_set_contents)(window *p_window, glyph *p_glyph);
typedef void(fn_window_draw_char)(window *p_window, char c, int x, int y);
typedef void(fn_window_draw_rect)(window *p_window, int x, int y, int w, int h);
typedef void(fn_window_fill_rect)(window *p_window, int x, int y, int w, int h);
typedef void(fn_window_draw_button)(window *p_window, int x, int y, int w, int h, const char *p_button);
typedef void(fn_window_draw_label)(window *p_window, int x, int y, int w, int h, const char *p_label);
typedef int(fn_window_char_width)(window *p_window, char c);
typedef int(fn_window_char_height)(window *p_window, char c);

typedef window_impl *(fn_window_impl_construct)(window_factory *p_window_factory, const char *p_title, window *p_window);
typedef int(fn_window_impl_redraw)(window_impl *p_window_impl);
typedef int(fn_window_impl_raise)(window_impl *p_window_impl);
typedef int(fn_window_impl_lower)(window_impl *p_window_impl);
typedef int(fn_window_impl_iconify)(window_impl *p_window_impl);
typedef int(fn_window_impl_deiconify)(window_impl *p_window_impl);
typedef int(fn_window_impl_set_contents)(window_impl *p_window_impl);
typedef void(fn_window_impl_draw_char)(window_impl *p_window_impl, char c, int x, int y);
typedef void(fn_window_impl_draw_rect)(window_impl *p_window_impl, int x, int y, int w, int h);
typedef void(fn_window_impl_fill_rect)(window_impl *p_window_impl, int x, int y, int w, int h);
typedef void(fn_window_impl_draw_button)(window_impl *p_window_impl, int x, int y, int w, int h, const char *p_button);
typedef void(fn_window_impl_draw_label)(window_impl *p_window_impl, int x, int y, int w, int h, const char *p_label);
typedef int(fn_window_impl_char_width)(window_impl *p_window_impl, char c);
typedef int(fn_window_impl_char_height)(window_impl *p_window_impl, char c);

typedef void(fn_glyph_draw)(glyph *p_glyph, window *p_window);
typedef window *(fn_glyph_window_get)(glyph *p_glyph);
typedef void (fn_glyph_position_set)(glyph *p_glyph, point _point);
typedef point (fn_glyph_position_get)(glyph *p_glyph);
typedef void (fn_glyph_compose)(glyph *p_glyph);
typedef void (fn_glyph_size)(glyph *p_glyph, window *p_window);
typedef rect (fn_glyph_bounds_get)(glyph *p_glyph);
typedef glyph *(fn_glyph_parent_get)(glyph *p_glyph);
typedef composition *(fn_glyph_composition_get)(glyph *p_glyph);
typedef bool (fn_glyph_intersects)(glyph *p_glyph, point p);
typedef void (fn_glyph_parent_set)(glyph *p_glyph, glyph *p_parent);
typedef void (fn_glyph_window_set)(glyph *p_glyph, window *p_window);
typedef void (fn_glyph_bounds_set)(glyph *p_glyph, rect bounds);
typedef point (fn_glyph_cursor)(glyph *p_glyph);
typedef point (fn_glyph_adjust_child)(glyph *p_glyph, glyph *p_child, point cursor);
typedef void (fn_glyph_adjust)(glyph *p_glyph, point cursor);
typedef void (fn_glyph_insert)(glyph *p_glyph, glyph *p_child, int i);
typedef void (fn_glyph_remove)(glyph *p_glyph, glyph *p_child);
typedef glyph *(fn_glyph_child)(glyph *p_glyph, int i);
typedef iterator(fn_glyph_iterator)(glyph *p_glyph);

typedef void (fn_compositor_composition_set)(compositor *p_compositor, composition *p_composition);
typedef void (fn_compositor_compose)(compositor *p_compositor);

struct point_s 
{
    float x, y;
};

struct rect_s
{
    point origin, extent;
};

struct window_impl_s
{
    fn_window_impl_redraw      *pfn_redraw;
    fn_window_impl_raise       *pfn_raise;
    fn_window_impl_lower       *pfn_lower;
    fn_window_impl_iconify     *pfn_iconify;
    fn_window_impl_deiconify   *pfn_deiconify;
    fn_window_impl_draw_char   *pfn_draw_char;
    fn_window_impl_draw_rect   *pfn_draw_rect;
    fn_window_impl_fill_rect   *pfn_fill_rect;
    fn_window_impl_draw_button *pfn_draw_button;
    fn_window_impl_draw_label  *pfn_draw_label;
    fn_window_impl_char_width  *pfn_char_width;
    fn_window_impl_char_height *pfn_char_height;
};

struct window_s
{
    fn_window_draw         *pfn_draw;
    fn_window_redraw       *pfn_redraw;
    fn_window_raise        *pfn_raise;
    fn_window_lower        *pfn_lower;
    fn_window_iconify      *pfn_iconify;
    fn_window_deiconify    *pfn_deiconify;
    fn_window_set_contents *pfn_set_contents;
    fn_window_draw_char    *pfn_draw_char;
    fn_window_draw_rect    *pfn_draw_rect;
    fn_window_fill_rect    *pfn_fill_rect;
    fn_window_draw_button  *pfn_draw_button;
    fn_window_draw_label   *pfn_draw_label;
    fn_window_char_width   *pfn_char_width;
    fn_window_char_height  *pfn_char_height;
    const char *p_title;
    window_impl *p_impl;
    glyph *p_contents;
};

struct application_window_s
{
    window _window;
    int i;
};

struct window_factory_s
{
    window_factory *p_unique_instance;
    fn_window_impl_construct *pfn_window_imp_construct;
};

struct sdl_window_factory_s
{
    window_factory _window_factory;
    sdl_window_factory *p_unique_instance;
    fn_window_impl_construct *pfn_window_imp_construct;
};

struct sdl_window_s
{
    window_impl _window_impl;

    const char *tite;
    window *p_window;
    SDL_Window *p_w;
    SDL_Renderer *p_r;
    TTF_Font *p_f;
};

struct glyph_s
{
    fn_glyph_draw            *pfn_draw;      
    fn_glyph_window_get      *pfn_window_get;            
    fn_glyph_position_set    *pfn_position_set;              
    fn_glyph_position_get    *pfn_position_get;              
    fn_glyph_compose         *pfn_compose;         
    fn_glyph_size            *pfn_size;      
    fn_glyph_bounds_get      *pfn_bounds_get;            
    fn_glyph_parent_get      *pfn_parent_get;            
    fn_glyph_composition_get *pfn_composition_get;                 
    fn_glyph_intersects      *pfn_intersects;            
    fn_glyph_parent_set      *pfn_parent_set;            
    fn_glyph_window_set      *pfn_window_set;            
    fn_glyph_bounds_set      *pfn_bounds_set;            
    fn_glyph_cursor          *pfn_cursor;   
    fn_glyph_adjust_child    *pfn_adjust_child;
    fn_glyph_adjust          *pfn_adjust;
    fn_glyph_insert          *pfn_insert;        
    fn_glyph_remove          *pfn_remove;        
    fn_glyph_child           *pfn_child;       
    fn_glyph_iterator        *pfn_iterator;          
    window                   *p_window;
    glyph                    *p_parent;
    rect                      _bounds;
};

struct rectangle_s 
{
    glyph _glyph;
    rect _dimensions;
};

struct character_s
{
    glyph _glyph;
    char _c;
};

struct composition_s
{
    glyph _glyph;
    array *p_array;
    rect _size;
    point _position;
    compositor *p_compositor;
};

struct row_s
{
    composition _composition;
};

struct column_s
{
    composition _composition;
};

struct mono_glyph_s
{
    composition _composition;
};

struct border_s
{
    mono_glyph _mono_glyph;
    int _s;
};

struct scroller_s
{
    mono_glyph _mono_glyph;
    int _w;
};

struct compositor_s 
{
    fn_compositor_composition_set *pfn_compositor_composition_set;
    fn_compositor_compose         *pfn_compositor_compose;
    composition                   *p_composition;
};

struct null_compositor_s 
{
    compositor _compositor;
};

struct simple_compositor_s 
{
    compositor _compositor;
};