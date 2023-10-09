# UI
##### **This project is still incomplete. This notice will be removed when the project is polished to my liking**
![UI window example](Window.png)

This simple callback driven UI library implements many UI elements, like labels, buttons, and dropdowns to name a few. UI element colors are customizable, and the user configurations are stored nontemporally in AppData. Windows and UI elements are constructed at run time from JSON files.

## Window JSON
Here's the source for the above window:

```json
{
    "name"     : "Test window",
    "width"    : 800,
    "height"   : 720,
    "elements" : [
        {
            "type"     : "LABEL",
            "name"     : "label",
            "text"     : "Label", 
            "x"        : 16,
            "y"        : 16,
            "size"     : 1
        },
        {
            "type"      : "CHECKBOX",
            "name"      : "checkbox",
            "x"         : 16,
            "y"         : 32,
            "labels"    : [
                "Checkbox 1",
                "Checkbox 2",
                "Checkbox 3"
            ],
            "checked" : [
                false,
                false,
                false
            ]
        },
        {
            "type"  : "BUTTON",
            "name"  : "button",
            "label" : "Button",
            "x"     : 16,
            "y"     : 96
        },
        {
            "type"      : "DROPDOWN",
            "name"      : "dropdown",
            "x"         : 16,
            "y"         : 80,
            "options"   : [
                "Option 1",
                "Option 2",
                "Option 3"
            ],
            "index"     : -1,
            "collapsed" : true
        },
        {
            "type"      : "RADIO BUTTON",
            "name"      : "radiobutton",
            "x"         : 16,
            "y"         : 112,
            "labels"    : [
                "Radio button 1",
                "Radio button 2",
                "Radio button 3"
            ],
            "index" : 0
        },
        {
            "type"     : "LABEL",
            "name"     : "label 2",
            "text"     : "An Image:", 
            "x"        : 16,
            "y"        : 180,
            "size"     : 1
        },
        {
            "type"      : "IMAGE",
            "name"      : "image",
            "x"         : 16,
            "y"         : 192,
            "width"     : 768,
            "height"    : 512,
            "path"      : "image.png"
        },
        {
            "type"        : "TEXT INPUT",
            "name"        : "text input",
            "x"           : 16,
            "y"           : 160,
            "width"       : 80,
            "height"      : 14,
            "placeholder" : "Text Input",
            "length"      : 255
        },
        {
            "type"     : "LABEL",
            "name"     : "label 3",
            "text"     : "A Table:", 
            "x"        : 160,
            "y"        : 16,
            "size"     : 1
        },
        {
            "type"        : "TABLE",
            "name"        : "element table",
            "x"           : 160,
            "y"           : 32,
            "max rows"    : 5,
            "max columns" : 3
        }
    ]
}
```
[ [UI Window JSON](window.json) ]

## A minimal program written with the UI library
```c
#include <UI/UI.h>

int main ( int argc, const char **argv )
{
    // Initialized data
    ui_instance *p_ui_instance = 0;
    ui_window   *p_ui_window   = 0;

    // Initialize the UI library
    ui_init(&p_ui_instance, "");

    // Load a window from the filesystem
    load_window(&p_ui_window, "window.json");

    // Add the window to the instance
    ui_append_window(p_ui_instance, p_ui_window);

    // Start running
    p_ui_instance->running = true;

    // Loop
    while (p_ui_instance->running)
    {
        
        // Process input
        ui_process_input(p_ui_instance);

        // Draw windows
        ui_draw(p_ui_instance);
    }

    // Exit the UI library
    ui_exit(p_ui_instance);

    return 1;
}
```
