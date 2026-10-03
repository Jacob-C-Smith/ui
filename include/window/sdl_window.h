#pragma once

#include <core/interfaces.h>

#include <ui/ui.h>
#include <window/window_impl.h>
#include <window/window.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

window_impl *sdl_window_construct ( const char *title, window *w);
int sdl_window_destroy ( sdl_window *p_sdl_window );