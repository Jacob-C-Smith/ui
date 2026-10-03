#include <window/application_window.h>

int application_window_construct ( application_window *p_application_window, const char *p_title )
{
    window_construct((window *)p_application_window, p_title);

    return 1;
}