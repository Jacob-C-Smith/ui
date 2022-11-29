#pragma once
#include <UI/UItypedef.h>

#define DLLEXPORT extern __declspec(dllexport)

// Useful typedefs 
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

// Color. R is bits 0-7, G is 8-15, B 16-23, A 24-31
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
typedef struct ui_mouse_state_s ui_mouse_state_t;

// UI Label type
typedef struct UILabel_s	    UILabel_t;

// UI Button type
typedef struct UIButton_s	    UIButton_t;

// UI Canvas type
typedef struct UICanvas_s	    UICanvas_t;

// UI Chart type
typedef struct UIChart_s	    UIChart_t;

// UI Table type
typedef struct UITable_s        UITable_t;

// UI Checkbox type
typedef struct UICheckbox_s     UICheckbox_t;

// UI Contianer type
typedef struct UIContainer_s    UIContainer_t;

// UI Dropdown type
typedef struct UIDropdown_s	    UIDropdown_t;

// UI Image type
typedef struct UIImage_s        UIImage_t;

// UI Label type
typedef struct UILabel_s        UILabel_t;

// UI Radio button type
typedef struct UIRadioButton_s  UIRadioButton_t;

// UI Slider type
typedef struct UISlider_s       UISlider_t;

// UI Text input type
typedef struct UITextInput_s    UITextInput_t;

// UI Element type
typedef struct UIElement_s      UIElement_t;

// UI Window type
typedef struct UIWindow_s       UIWindow_t;

// UI Instance type
typedef struct UIInstance_s     UIInstance_t;
