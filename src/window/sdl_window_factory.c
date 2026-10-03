#include <window/sdl_window_factory.h>

static sdl_window_factory _sdl_window_factory = { 0 };

window_impl *sdl_window_imp_construct ( sdl_window_factory *p_sdl_window_factory, const char *p_title, window *p_window );

int sdl_window_factory_construct ( sdl_window_factory *p_sdl_window_factory )
{
    _sdl_window_factory.p_unique_instance = &_sdl_window_factory;
    _sdl_window_factory.pfn_window_imp_construct = (fn_window_impl_construct *)sdl_window_imp_construct;
    _sdl_window_factory._window_factory.pfn_window_imp_construct = (fn_window_impl_construct *)sdl_window_imp_construct;
    return 1;
}

window_factory *sdl_window_factory_instance ( void )
{
    if ( NULL == _sdl_window_factory.p_unique_instance )
    {
        sdl_window_factory_construct(_sdl_window_factory.p_unique_instance);
    }

    return (window_factory *)&_sdl_window_factory;
}

window_impl *sdl_window_imp_construct ( sdl_window_factory *p_sdl_window_factory, const char *p_title, window *p_window )
{
    return sdl_window_construct(p_title, p_window);
}