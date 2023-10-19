#pragma once
#include <stdio.h>

#include <dict/dict.h>

#include <json/json.h>

#include <ui/typedef.h>
#include <ui/element.h>

// UI Table. 
struct UITable_s
{

    // Table location
	u32      x, 
		     y, 
		     w,
		     h,
             max_rows,
             max_columns,
             last_x,
             last_y;

    char   **data;
    size_t  *column_widths;

    // Callback information
    size_t   on_click_count,   on_click_max,
             on_hover_count,   on_hover_max,
             on_release_count, on_release_max;
    
    // Callback function pointers
    void   **on_click,
           **on_hover,
           **on_release;
};

// Allocators

 /** !
  *  Allocate a UI Table
  *
  *  @param pp_table : Pointer to pointer to table
  *  
  *  @sa destroy_table
  *  
  *  @return 1 on success, 0 on error.  
  */
DLLEXPORT int           create_table               ( ui_table  **pp_table );

// Constructors
 /** !
  *  Load a UI Table from a dict 
  *
  *  @param pp_table     : Pointer to pointer to table
  *  @param p_dictionary : Pointer to dict 
  * 
  *  @sa load_element_as_json 
  *  
  *  @return 1 on success, 0 on error.  
  */
DLLEXPORT int           load_table_as_json_value   ( ui_table  **pp_table, json_value *p_value );


// Callbacks
/** !
  *  Fire each hover callbacks. 
  *
  *  @param p_table    : Pointer to table
  *  @param mouse_state : Mouse state 
  * 
  *  @sa click_table
  *  @sa release_table
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int           hover_table                ( ui_table   *p_table, ui_mouse_state mouse_state );

/** !
  *  Fire each click callbacks. 
  *
  *  @param p_table    : Pointer to table
  *  @param mouse_state : Mouse state 
  * 
  *  @sa hover_table
  *  @sa release_table
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int           click_table                ( ui_table   *p_table, ui_mouse_state mouse_state );

/** !
  *  Fire each release callbacks. 
  *
  *  @param p_table    : Pointer to table
  *  @param mouse_state : Mouse state 
  *
  *  @sa click_table
  *  @sa hover_table
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int           release_table              ( ui_table   *p_table , ui_mouse_state mouse_state );

// Add callbacks
/** !
  *  Add a click callback.
  *
  *  @param p_table : Pointer to table
  *  @param callback : function pointer. Should be of type int callback ( ui_button* , ui_mouse_state )
  *
  *  @sa add_hover_callback_table
  *  @sa add_release_callback_table
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int           add_click_callback_table   ( ui_table   *p_table , void (*callback) ( ui_table*, ui_mouse_state ) );

/** !
  *  Add a hover callback.
  *
  *  @param p_table : Pointer to table
  *  @param callback : function pointer. Should be of type int callback ( ui_button* , ui_mouse_state )
  *
  *  @sa add_click_callback_table
  *  @sa add_release_callback_table
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int           add_hover_callback_table   ( ui_table   *p_table, void (*callback) ( ui_table*, ui_mouse_state ) );

/** !
  *  Add a release callback.
  *
  *  @param p_table : Pointer to table
  *  @param callback : function pointer. Should be of type int callback ( ui_button* , ui_mouse_state )
  *
  *  @sa add_click_callback_table
  *  @sa add_hover_callback_table
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int           add_release_callback_table ( ui_table   *p_table, void (*callback) ( ui_table*, ui_mouse_state ) );

DLLEXPORT char         *get_table_cell ( ui_table   *p_table, size_t x, size_t y );

DLLEXPORT int           set_table_cell ( ui_table   *p_table, size_t x, size_t y, char *cell_text );

// Drawing
/** !
  *  Draw a UI table.
  *
  *  @param window  : Pointer to UI window
  *  @param p_table : Pointer to table
  *
  *  @sa draw_element
  *
  *  @return 1 on success, 0 on error.
  */
DLLEXPORT int           draw_table                 ( ui_window   *window   , ui_table *p_table );

// Collision
/** !
  *  Checks for pointer table overlap
  * 
  *  @param p_table    : Pointer to table
  *  @param mouse_state : Mouse state
  *
  *  @return true if cursor is on the table, and false otherwise
  */
DLLEXPORT bool          table_in_bounds            ( ui_table   *p_table, ui_mouse_state mouse_state );

// Deallocators
/** !
  *  Deallocates a table and its contents
  *  @param p_table    : Pointer to table
  *
  *  @return 
  */
DLLEXPORT int           destroy_table              ( ui_table   *p_table);