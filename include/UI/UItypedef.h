#pragma once
#include <UI/UItypedef.h>

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
struct mouse_state_s;
typedef struct mouse_state_s mouse_state_t;

struct UIInstance_s;
typedef struct UIInstance_s UIInstance_t;

struct UILabel_s;
typedef struct UILabel_s UILabel_t;

struct UIButton_s;
typedef struct UIButton_s UIButton_t;

struct UICanvas_s;
typedef struct UICanvas_s UICanvas_t;

struct UIChart_s;
typedef struct UIChart_s UIChart_t;

struct UICheckbox_s;
typedef struct UICheckbox_s UICheckbox_t;

struct UIContainer_s;
typedef struct UIContainer_s UIContainer_t;

struct UIDropdown_s;
typedef struct UIDropdown_s UIDropdown_t;

struct UIImage_s;
typedef struct UIImage_s UIImage_t;

struct UILabel_s;
typedef struct UILabel_s UILabel_t;

struct UIRadioButton_s;
typedef struct UIRadioButton_s UIRadioButton_t;

struct UISlider_s;
typedef struct UISlider_s UISlider_t;

struct UITextInput_s;
typedef struct UITextInput_s UITextInput_t;

struct UIWindow_s;
typedef struct UIWindow_s UIWindow_t;

struct UIElement_s;
typedef struct UIElement_s UIElement_t;