#pragma once

#include <core/interfaces.h>
#include <data/array.h>
#include <data/avl.h>

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
struct overlay_s;
struct mono_glyph_s;
struct margin_s;
struct border_s;
struct padding_s;
struct scroller_s;
struct compositor_s;
struct null_compositor_s;
struct simple_compositor_s;
struct gui_factory_s;
struct red_gui_factory_s;
struct green_gui_factory_s;
struct blue_gui_factory_s;
struct button_s;
struct red_button_s;
struct green_button_s;
struct blue_button_s;
struct label_s;
struct red_label_s;
struct green_label_s;
struct blue_label_s;
struct command_s;
struct print_command_s;
struct menu_toggle_s;
struct menu_s;
struct red_menu_s;
struct green_menu_s;
struct blue_menu_s;
struct menu_item_s;
struct red_menu_item_s;
struct green_menu_item_s;
struct blue_menu_item_s;

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
typedef struct overlay_s overlay;
typedef struct mono_glyph_s mono_glyph;
typedef struct margin_s margin;
typedef struct border_s border;
typedef struct padding_s padding;
typedef struct scroller_s scroller;
typedef struct compositor_s compositor;
typedef struct null_compositor_s null_compositor;
typedef struct simple_compositor_s simple_compositor; 
typedef struct gui_factory_s gui_factory;
typedef struct red_gui_factory_s red_gui_factory;
typedef struct green_gui_factory_s green_gui_factory;
typedef struct blue_gui_factory_s blue_gui_factory;
typedef struct button_s button;
typedef struct red_button_s red_button;
typedef struct green_button_s green_button;
typedef struct blue_button_s blue_button;
typedef struct label_s label;
typedef struct red_label_s red_label;
typedef struct green_label_s green_label;
typedef struct blue_label_s blue_label;
typedef struct command_s command;
typedef struct print_command_s print_command;
typedef struct menu_toggle_s menu_toggle;
typedef array key_map;
typedef struct menu_s menu;
typedef struct red_menu_s red_menu;
typedef struct green_menu_s green_menu;
typedef struct blue_menu_s blue_menu;
typedef struct menu_item_s menu_item;
typedef struct red_menu_item_s red_menu_item;
typedef struct green_menu_item_s green_menu_item;
typedef struct blue_menu_item_s blue_menu_item;

typedef int(fn_window_draw)(window *p_window);
typedef int(fn_window_redraw)(window *p_window);
typedef int(fn_window_raise)(window *p_window);
typedef int(fn_window_lower)(window *p_window);
typedef int(fn_window_iconify)(window *p_window);
typedef int(fn_window_deiconify)(window *p_window);
typedef int(fn_window_set_contents)(window *p_window, glyph *p_glyph);
typedef void(fn_window_draw_char)(window *p_window, char c, bool bold, bool italic, float size, int x, int y);
typedef void(fn_window_draw_rect)(window *p_window, int x, int y, int w, int h);
typedef void(fn_window_clear_rect)(window *p_window, int x, int y, int w, int h);
typedef void(fn_window_fill_rect)(window *p_window, int x, int y, int w, int h);
typedef void(fn_window_draw_button)(window *p_window, int x, int y, int w, int h, const char *p_button);
typedef void(fn_window_draw_label)(window *p_window, int x, int y, int w, int h, const char *p_label);
typedef int(fn_window_char_width)(window *p_window, char c, bool bold, bool italic, float size);
typedef int(fn_window_char_height)(window *p_window, char c, bool bold, bool italic, float size);
typedef void(fn_window_key)(window *p_window, char c);
typedef void(fn_window_click)(window *p_window, int x, int y);

typedef window_impl *(fn_window_impl_construct)(window_factory *p_window_factory, const char *p_title, window *p_window);
typedef int(fn_window_impl_redraw)(window_impl *p_window_impl);
typedef int(fn_window_impl_raise)(window_impl *p_window_impl);
typedef int(fn_window_impl_lower)(window_impl *p_window_impl);
typedef int(fn_window_impl_iconify)(window_impl *p_window_impl);
typedef int(fn_window_impl_deiconify)(window_impl *p_window_impl);
typedef int(fn_window_impl_set_contents)(window_impl *p_window_impl);
typedef void(fn_window_impl_draw_char)(window_impl *p_window_impl, char c, bool bold, bool italic, float size, int x, int y);
typedef void(fn_window_impl_draw_rect)(window_impl *p_window_impl, int x, int y, int w, int h);
typedef void(fn_window_impl_clear_rect)(window_impl *p_window_impl, int x, int y, int w, int h);
typedef void(fn_window_impl_fill_rect)(window_impl *p_window_impl, int x, int y, int w, int h);
typedef void(fn_window_impl_draw_button)(window_impl *p_window_impl, int x, int y, int w, int h, const char *p_button);
typedef void(fn_window_impl_draw_label)(window_impl *p_window_impl, int x, int y, int w, int h, const char *p_label);
typedef int(fn_window_impl_char_width)(window_impl *p_window_impl, char c, bool bold, bool italic, float size);
typedef int(fn_window_impl_char_height)(window_impl *p_window_impl, char c, bool bold, bool italic, float size);
typedef void(fn_window_impl_key)(window_impl *p_window_impl, char c);
typedef void(fn_window_impl_click)(window_impl *p_window_impl, int x, int y);

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
typedef glyph *(fn_glyph_find)(glyph *p_glyph, point p);
typedef void(fn_glyph_click)(glyph *p_glyph);
typedef void(fn_glyph_key)(glyph *p_glyph, char c);
typedef void (fn_glyph_command_set)( glyph *p_glyph, command *p_command );
typedef glyph *(fn_glyph_command_get)( glyph *p_glyph );

typedef void (fn_compositor_composition_set)(compositor *p_compositor, composition *p_composition);
typedef void (fn_compositor_compose)(compositor *p_compositor);

typedef button *(fn_gui_factory_button_construct)( gui_factory *p_gui_factory, const char *text );
typedef label *(fn_gui_factory_label_construct)( gui_factory *p_gui_factory, const char *text );
typedef menu *(fn_gui_factory_menu_construct)( gui_factory *p_gui_factory );
typedef menu_item *(fn_gui_factory_menu_item_construct)( gui_factory *p_gui_factory, const char *text );

typedef void (fn_command_execute)( command *p_command );
typedef void (fn_command_unexecute)( command *p_command );
typedef command *(fn_command_clone)( command *p_command );

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
    fn_window_impl_clear_rect  *pfn_clear_rect;
    fn_window_impl_draw_button *pfn_draw_button;
    fn_window_impl_draw_label  *pfn_draw_label;
    fn_window_impl_char_width  *pfn_char_width;
    fn_window_impl_char_height *pfn_char_height;
    fn_window_impl_key         *pfn_key;
    fn_window_impl_click       *pfn_click;
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
    fn_window_clear_rect   *pfn_clear_rect;
    fn_window_draw_button  *pfn_draw_button;
    fn_window_draw_label   *pfn_draw_label;
    fn_window_char_width   *pfn_char_width;
    fn_window_char_height  *pfn_char_height;
    fn_window_key          *pfn_key;
    fn_window_click        *pfn_click;
    const char *p_title;
    window_impl *p_impl;
    glyph *p_contents;
};

struct application_window_s
{
    window _window;
    key_map *p_key_map;
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

    const char *title;
    window *p_window;
    SDL_Window *p_w;
    SDL_Renderer *p_r;
    TTF_Font *p_f;
    avl_tree *p_glyph_cache;
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
    fn_glyph_find            *pfn_find;   
    fn_glyph_click           *pfn_click;    
    fn_glyph_key             *pfn_key;
    fn_glyph_command_set     *pfn_command_set;
    fn_glyph_command_get     *pfn_command_get;
    command                  *p_command;
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
    bool _bold;
    bool _italic;
    float _size;
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

struct overlay_s
{
    composition _composition;
};

struct mono_glyph_s
{
    composition _composition;
};

struct margin_s
{
    mono_glyph _mono_glyph;
    int _s;
};

struct border_s
{
    mono_glyph _mono_glyph;
    int _s;
};

struct padding_s
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

struct gui_factory_s
{
    gui_factory                     *p_unique_instance;
    fn_gui_factory_button_construct *pfn_button_construct;
    fn_gui_factory_label_construct  *pfn_label_construct;
    fn_gui_factory_menu_construct   *pfn_menu_construct;
    fn_gui_factory_menu_item_construct *pfn_menu_item_construct;
};

struct red_gui_factory_s
{
    red_gui_factory                 *p_unique_instance;
    fn_gui_factory_button_construct *pfn_button_construct;
    fn_gui_factory_label_construct  *pfn_label_construct;
    fn_gui_factory_menu_construct   *pfn_menu_construct;
    fn_gui_factory_menu_item_construct *pfn_menu_item_construct;
};

struct green_gui_factory_s
{
    green_gui_factory               *p_unique_instance;
    fn_gui_factory_button_construct *pfn_button_construct;
    fn_gui_factory_label_construct  *pfn_label_construct;
    fn_gui_factory_menu_construct   *pfn_menu_construct;
    fn_gui_factory_menu_item_construct *pfn_menu_item_construct;
};

struct blue_gui_factory_s
{
    blue_gui_factory                *p_unique_instance;
    fn_gui_factory_button_construct *pfn_button_construct;
    fn_gui_factory_label_construct  *pfn_label_construct;
    fn_gui_factory_menu_construct   *pfn_menu_construct;
    fn_gui_factory_menu_item_construct *pfn_menu_item_construct;
};

struct button_s
{
    mono_glyph _mono_glyph;
};

struct red_button_s
{
    button _button;
};

struct green_button_s
{
    button _button;
};

struct blue_button_s
{
    button _button;
};

struct label_s 
{
    mono_glyph _mono_glyph;
};

struct red_label_s
{
    label _label;
};

struct green_label_s
{
    label _label;
};

struct blue_label_s
{
    label _label;
};

struct menu_s
{
    column _column;
    bool _open;
};

struct red_menu_s { menu _menu; };
struct green_menu_s { menu _menu; };
struct blue_menu_s { menu _menu; };

struct menu_item_s
{
    row _item;
};

struct red_menu_item_s { menu_item _menu_item; };
struct green_menu_item_s { menu_item _menu_item; };
struct blue_menu_item_s { menu_item _menu_item; };

struct command_s 
{
    fn_command_execute   *pfn_execute;
    fn_command_unexecute *pfn_unexecute;
    fn_command_clone     *pfn_clone;
    bool reversable;
};

struct print_command_s
{
    command _command;
    const char *text;
};

struct menu_toggle_s
{
    command _command;
    menu *p_menu;
};