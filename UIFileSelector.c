#include <UI/UIFileSelector.h>
int update_ftab();
int dirup_click  (UIButton_t *p_button, ui_mouse_state_t m);
int select_click (UIButton_t *p_button, ui_mouse_state_t m);

int (*filesel_callb)(char *);

int file_selector (char *path, int(*cb)(char *))
{

    // Initialized data
    UIInstance_t *p_ui_instance = ui_get_active_instance();
    UIWindow_t   *p_ui_window   = 0;

    // Load a window from the filesystem
    if ( load_window(&p_ui_window, "fileselector.json") == 0 )
        goto failed_to_load_window;

    // Add the window to the instance
    ui_append_window(p_ui_instance, p_ui_window);
    
    UITable_t     *t = ((UIElement_t *)find_element(p_ui_window, "ftab"))->table;
    UITextInput_t *i = ((UIElement_t *)find_element(p_ui_window, "filepath"))->text_input;
    UIButton_t    *b1 = ((UIElement_t *)find_element(p_ui_window, "up"))->button;
    
    size_t plen = strlen(path);
    strncpy(i->text, path, plen);
    i->width = 8*(plen+1);

    add_click_callback_element(find_element(p_ui_window, "ftab"), &dirtab_click);
    add_click_callback_element(find_element(p_ui_window, "up"), &dirup_click);
    add_click_callback_element(find_element(p_ui_window, "select"), &select_click);

    b1->label[0]='\207';
    
    set_table_cell(t,1,0,"name");
    update_ftab();
    filesel_callb = cb;
    return 1;

    failed_to_load_window:
    return 0;
}

int update_ftab()
{
    UIInstance_t  *p_ui_instance = ui_get_active_instance();
    UIWindow_t    *p_ui_window   = dict_get(p_ui_instance->windows, "UI_FILE_SELECTOR");
    
    UITable_t     *t = ((UIElement_t *)find_element(p_ui_window, "ftab"))->table;
    UITextInput_t *i = ((UIElement_t *)find_element(p_ui_window, "filepath"))->text_input;
    UIButton_t    *b2 = ((UIElement_t *)find_element(p_ui_window, "select"))->button;

    t->max_rows = 35;
    DIR *dir;
    struct dirent *entry;
    int z = 1;
    int count;
    if ((dir = opendir(i->text)) == NULL)
        perror("opendir() error");
    else {
        count = 0;
        while ((entry = readdir(dir)) != NULL) {
            if(entry->d_name[0]!='.'){
                size_t l = strlen(entry->d_name);
                char *y = calloc(l+1, sizeof(char));
                char *x = calloc(32+1, sizeof(char));

                strncpy(y,entry->d_name,l);
                sprintf(x,"%d",entry->d_reclen);

                set_table_cell(t,0,z,(entry->d_type==DT_DIR)?"\205":"\206");
                set_table_cell(t,1,z,y);
                z++;
            }
            
        }
        closedir(dir);
    }
    table_in_bounds(t,(ui_mouse_state_t){0});
    t->max_rows = z;
    p_ui_window->height = z*12+64;
    p_ui_window->width = 32+t->w;
    b2->y=z*12+44;
    resize_window(p_ui_window);
    
    return 1;

}

int dirtab_click (UITable_t *p_table, ui_mouse_state_t m)
{
    if(p_table->last_y == 0)
        return 1;
    UIInstance_t  *p_ui_instance = ui_get_active_instance();
    UIWindow_t    *p_ui_window   = dict_get(p_ui_instance->windows, "UI_FILE_SELECTOR");
    UITextInput_t *i             = ((UIElement_t *)find_element(p_ui_window,"filepath"))->text_input;
    UITable_t     *t             = ((UIElement_t *)find_element(p_ui_window, "ftab"))->table;

    char *isFile = get_table_cell(p_table, 0, p_table->last_y);
    if(*(isFile)=='\205')
    {
        strcat(i->text, get_table_cell(p_table, p_table->last_x, p_table->last_y));
        strcat(i->text, "/");
        t->last_x=-1;
        t->last_y=-1;
    }

    update_ftab();
    return 1;
}

int dirup_click (UIButton_t *p_button, ui_mouse_state_t m)
{

    UIInstance_t  *p_ui_instance = ui_get_active_instance();
    UIWindow_t    *p_ui_window   = dict_get(p_ui_instance->windows, "UI_FILE_SELECTOR");
    UITextInput_t *i             = ((UIElement_t *)find_element(p_ui_window,"filepath"))->text_input;
    if (i->text[0]=='/'&&i->text[1]=='\0')
        return 1;
    *(strrchr(i->text, '/'))=0;
    *(strrchr(i->text, '/'))=0;
    strcat(i->text, "/");

    update_ftab();
    return 1;
}

int select_click (UIButton_t *p_button, ui_mouse_state_t m)
{
    UIInstance_t  *p_ui_instance = ui_get_active_instance();
    UIWindow_t    *p_ui_window   = dict_get(p_ui_instance->windows, "UI_FILE_SELECTOR");
    UIWindow_t    *p_load_w      = 0;
    UITextInput_t *i             = ((UIElement_t *)find_element(p_ui_window,"filepath"))->text_input;
    UITable_t     *t             = ((UIElement_t *)find_element(p_ui_window,"ftab"))->table;
    char *buf = calloc(1024, sizeof(char));

    sprintf(buf, "%s%s",i->text,get_table_cell(t,1,t->last_y));
    fflush(stdout);

    filesel_callb(buf);
    p_ui_window->is_open = false;
    return 1;
}