#pragma once

#include <ui/ui.h>
#include <window/window_impl.h>
#include <window/window_factory.h>

int window_construct ( window *p_window, const char *p_title );
int window_redraw ( window *p_window );
