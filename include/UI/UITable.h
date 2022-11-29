#pragma once
#include <stdio.h>

#include <dict/dict.h>

#include <JSON/JSON.h>

#include <UI/UItypedef.h>
#include <UI/UIElement.h>

// UI Table. 
struct UITable_s
{

    // Table location
	u32      x, 
		     y, 
		     w,
		     h,
             max_rows,
             max_columns;

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

 /* !
  *  Allocate a UI Table
  *
  *  @param pp_table : Pointer to pointer to table
  *  
  *  @sa destroy_table
  *  
  *  @return 0 on success, -1 on error.  
  */
DLLEXPORT int           create_table               ( UITable_t  **pp_table );

// Constructors
 /* !
  *  Load a UI Table from a dict 
  *
  *  @param pp_table     : Pointer to pointer to table
  *  @param p_dictionary : Pointer to dict 
  * 
  *  @sa load_element_as_json 
  *  
  *  @return 0 on success, -1 on error.  
  */
DLLEXPORT int           load_table_as_dict         ( UITable_t  **pp_table, dict *dictionary );

// Callbacks
/* !
  *  Fire each hover callbacks. 
  *
  *  @param p_table    : Pointer to table
  *  @param mouse_state : Mouse state 
  * 
  *  @sa click_table
  *  @sa release_table
  *
  *  @return 0 on success, -1 on error.
  */
DLLEXPORT int           hover_table                ( UITable_t   *p_table, ui_mouse_state_t mouse_state );

/* !
  *  Fire each click callbacks. 
  *
  *  @param p_table    : Pointer to table
  *  @param mouse_state : Mouse state 
  * 
  *  @sa hover_table
  *  @sa release_table
  *
  *  @return 0 on success, -1 on error.
  */
DLLEXPORT int           click_table                ( UITable_t   *p_table, ui_mouse_state_t mouse_state );

/* !
  *  Fire each release callbacks. 
  *
  *  @param p_table    : Pointer to table
  *  @param mouse_state : Mouse state 
  *
  *  @sa click_table
  *  @sa hover_table
  *
  *  @return 0 on success, -1 on error.
  */
DLLEXPORT int           release_table              ( UITable_t   *p_table , ui_mouse_state_t mouse_state );

// Add callbacks
/* !
  *  Add a click callback.
  *
  *  @param p_table : Pointer to table
  *  @param callback : function pointer. Should be of type int callback ( UIButton_t* , ui_mouse_state_t )
  *
  *  @sa add_hover_callback_table
  *  @sa add_release_callback_table
  *
  *  @return 0 on success, -1 on error.
  */
DLLEXPORT int           add_click_callback_table   ( UITable_t   *p_table , void (*callback) ( UITable_t*, ui_mouse_state_t ) );

/* !
  *  Add a hover callback.
  *
  *  @param p_table : Pointer to table
  *  @param callback : function pointer. Should be of type int callback ( UIButton_t* , ui_mouse_state_t )
  *
  *  @sa add_click_callback_table
  *  @sa add_release_callback_table
  *
  *  @return 0 on success, -1 on error.
  */
DLLEXPORT int           add_hover_callback_table   ( UITable_t   *p_table, void (*callback) ( UITable_t*, ui_mouse_state_t ) );

/* !
  *  Add a release callback.
  *
  *  @param p_table : Pointer to table
  *  @param callback : function pointer. Should be of type int callback ( UIButton_t* , ui_mouse_state_t )
  *
  *  @sa add_click_callback_table
  *  @sa add_hover_callback_table
  *
  *  @return 0 on success, -1 on error.
  */
DLLEXPORT int           add_release_callback_table ( UITable_t   *p_table, void (*callback) ( UITable_t*, ui_mouse_state_t ) );

DLLEXPORT char         *get_table_cell ( UITable_t   *p_table, size_t x, size_t y );

DLLEXPORT int           set_table_cell ( UITable_t   *p_table, size_t x, size_t y, char *cell_text );

// Drawing
/* !
  *  Draw a UI table.
  *
  *  @param window  : Pointer to UI window
  *  @param p_table : Pointer to table
  *
  *  @sa draw_element
  *
  *  @return 0 on success, -1 on error.
  */
DLLEXPORT int           draw_table                 ( UIWindow_t   *window   , UITable_t *p_table );

// Collision
/* !
  *  Checks for pointer table overlap
  * 
  *  @param p_table    : Pointer to table
  *  @param mouse_state : Mouse state
  *
  *  @return true if cursor is on the table, and false otherwise
  */
DLLEXPORT bool          table_in_bounds            ( UITable_t   *p_table, ui_mouse_state_t mouse_state );

// Deallocators
/* !
  *  Deallocates a table and its contents
  *  @param p_table    : Pointer to table
  *
  *  @return 
  */
DLLEXPORT int           destroy_table              ( UITable_t   *p_table);