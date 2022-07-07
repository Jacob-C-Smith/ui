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

// Vector types
typedef struct { f32 x, y; } vec2;
typedef struct { s32 x, y; } ivec2;

// Color
typedef u32 color;

// UI Structures
struct UILabel_s;
struct UIButton_s;
struct mouse_state_s;
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

typedef struct mouse_state_s   mouse_state_t;
typedef struct UILabel_s	   UILabel_t;
typedef struct UIButton_s	   UIButton_t;
typedef struct UICanvas_s	   UICanvas_t;
typedef struct UIChart_s	   UIChart_t;
typedef struct UICheckbox_s    UICheckbox_t;
typedef struct UIContainer_s   UIContainer_t;
typedef struct UIDropdown_s	   UIDropdown_t;
typedef struct UIImage_s       UIImage_t;
typedef struct UILabel_s       UILabel_t;
typedef struct UIRadioButton_s UIRadioButton_t;
typedef struct UISlider_s      UISlider_t;
typedef struct UITextInput_s   UITextInput_t;
typedef struct UIElement_s     UIElement_t;
typedef struct UIWindow_s      UIWindow_t;
typedef struct UIInstance_s    UIInstance_t;
