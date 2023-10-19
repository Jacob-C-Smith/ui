// Include guard
#pragma once

// Platform dependent macros
#ifdef _WIN64
    #define DLLEXPORT extern __declspec(dllexport)
#else
    #define DLLEXPORT
#endif

// Type definitions
typedef unsigned char        u8;
typedef signed   char        s8;
typedef          char        i8;
typedef unsigned short       u16;
typedef signed   short       s16;
typedef          short       i16;
typedef unsigned long        u32;
typedef signed   long        s32;
typedef          long        i32;
typedef unsigned long long   u64;
typedef signed   long long   s64;
typedef          long long   i64;
typedef float                f32;
typedef double               f64;
typedef long     double      f80;

// Color
// R is bits 0-7, G is 8-15, B 16-23, A 24-31
typedef u32 color;

// UI Structures
struct UILabel_s;
struct UIButton_s;
struct ui_mouse_state_s;
struct UICanvas_s;
struct UIChart_s;
struct UICheckbox_s;
struct UIContainer_s;
struct UIDropdown_s;
struct UIImage_s;
struct UILabel_s;
struct UIRadioButton_s;
struct UISlider_s;
struct UITextInput_s;
struct UIElement_s;
struct UIWindow_s;
struct UIInstance_s;

// Mouse state type
typedef struct ui_mouse_state_s ui_mouse_state;

// UI Label type
typedef struct UILabel_s ui_label;

// UI Button type
typedef struct UIButton_s ui_button;

// UI Canvas type
typedef struct UICanvas_s ui_canvas;

// UI Chart type
typedef struct UIChart_s ui_chart;

// UI Table type
typedef struct UITable_s ui_table;

// UI Checkbox type
typedef struct UICheckbox_s ui_checkbox;

// UI Dropdown type
typedef struct UIDropdown_s ui_dropdown;

// UI Image type
typedef struct UIImage_s ui_image;

// UI Label type
typedef struct UILabel_s ui_label;

// UI Radio button type
typedef struct UIRadioButton_s ui_radiobutton;

// UI Slider type
typedef struct UISlider_s ui_slider;

// UI Text input type
typedef struct UITextInput_s ui_textinput;

// UI Element type
typedef struct UIElement_s ui_element;

// UI Window type
typedef struct UIWindow_s ui_window;

// UI Instance type
typedef struct UIInstance_s ui_instance;
