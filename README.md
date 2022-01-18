# UI
##### **This project is still incomplete. This notice will be removed when the project is functional**
![UI window example](UI/Window.png)

This simple callback driven UI library implements many UI elements, like labels, buttons, and dropdowns to name a few. UI element colors are customizable, and the user configurations are stored nontemporally in AppData. Windows and UI elements are constructed at run time from JSON files.

Here's the source for the above window:

```json
{
    "name"     : "Test window",
    "width"    : 160,
    "height"   : 120,
    "elements" : [
        {
            "type"     : "LABEL",
            "text"     : "Label",
            "x"        : 16,
            "y"        : 16
        },
        {
            "type"     : "BUTTON",
            "text"     : "Button",
            "x"        : 16,
            "y"        : 32
        },
        {
            "type"      : "CHECKBOX",
            "x"         : 16,
            "y"         : 48,
            "checked"   : true,
            "label"     : "Checkbox"
        },
        {
            "type"      : "DROPDOWN",
            "x"         : 16,
            "y"         : 64,
            "options"   : [
                "Option 1",
                "Option 2",
                "Option 3"
            ],
            "index"     : -1,
            "collapsed" : false
        }
    ]
}
```

[ [UI Window JSON](UI/UI-Window.json) ]