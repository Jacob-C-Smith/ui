#include <UI/UICheckbox.h>
#include "include\UI\UICheckbox.h"

UICheckbox_t* create_checkbox(void)
{
    UICheckbox_t* ret = calloc(1, sizeof(UICheckbox_t));

    // TODO: Check memory

    return ret;

    // TODO: Error handling

}

UICheckbox_t* load_checkbox(const char* path)
{
    // TODO: Argument check

    // Initialized data
    UICheckbox_t *ret        = 0;
    char         *token_text = 0;
    size_t        token_len  = 0;

    // 
    token_len  = ui_load_file(path, 0);
    token_text = calloc(token_len, sizeof(u8));
    ui_load_file(path, token_text);

    ret = 0;// load_checkbox_as_json(token_text);

    free(token_text);

    return ret;

    // TODO: Error handling
}

UICheckbox_t* load_checkbox_as_json_tokens (JSONToken_t* tokens, size_t token_count)
{

    // TODO: Argument check

    // Initialized data
    UICheckbox_t *ret            = create_checkbox();

    // Search through values and pull out relevent information
    for (size_t j = 0; j < token_count; j++)
    {
        if (strcmp("type", tokens[j].key) == 0)
        {
            if (tokens[j].type == JSONstring)
                if (strcmp(tokens[j].value.n_where, "CHECKBOX") != 0)
                    goto notACheckbox;
        }
        if (strcmp("label", tokens[j].key) == 0)
        {
            char   *label = tokens[j].value.n_where;
            size_t  len   = strlen(label);
            ret->label    = calloc(len+1, sizeof(char));

            // TODO: Check allocated memory

            strncpy(ret->label, label, len);
            continue;
        }
        if (strcmp("group", tokens[j].key) == 0)
        {
            char   *group = tokens[j].value.n_where;
            size_t  len   = strlen(group);
            ret->group    = calloc(len, sizeof(char));

            // TODO: Check allocated memory

            strncpy(ret->group, group, len);
            continue;
        }
        if (strcmp("x", tokens[j].key) == 0)
            ret->x = atoi(tokens[j].value.n_where);
        if (strcmp("y", tokens[j].key) == 0)
            ret->y = atoi(tokens[j].value.n_where);
        if (strcmp("hidden", tokens[j].key) == 0)
        {
            // TODO
        }

        if (strcmp("checked", tokens[j].key) == 0)
        {
            if (tokens[j].value.n_where)
                ret->checked = true;
        }

    }

    free(tokens);

    return ret;

    // Error handling
    notACheckbox:
    ui_print_error("[UI] [Checkbox] NOT A CHECKBOX\n");
    return 0;
}

int hover_checkbox(UICheckbox_t* checkbox, mouse_state_t mouse_state)
{
    return 0;
}

int click_checkbox(UICheckbox_t* checkbox, mouse_state_t mouse_state)
{
    checkbox->checked = (checkbox->checked) ? false : true;

    // Iterate through callbacks
    for (size_t i = 0; i < checkbox->on_click_count; i++)
    {
        // Define the callback function
        void (*callback)(UIDropdown_t*, mouse_state_t) = checkbox->on_click[i];

        // Call the callback function
        (*callback)(checkbox, mouse_state);

    }

    return 0;
}

int draw_checkbox(UIWindow_t* window, UICheckbox_t* checkbox)
{
    //size_t   l = strlen(checkbox->label);
    SDL_Rect r = { checkbox->x, checkbox->y, 12, 12 };
    checkbox->width = 12,
    checkbox->height = 12;
    SDL_SetRenderDrawColor(window->renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderDrawRect(window->renderer, &r);

    if (checkbox->checked == true)
    {
        ui_draw_text("\200", window, r.x + 2, r.y + 1, 1);

    }

    ui_draw_text(checkbox->label, window, r.x + 14, r.y + 2, 1);
    return 0;

}

int destroy_checkbox(UICheckbox_t* checkbox)
{
    free(checkbox);
    return 0;
}
