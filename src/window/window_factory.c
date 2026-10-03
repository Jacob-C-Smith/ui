#include <window/window_factory.h>

static window_factory _window_factory = { 0 };

window_impl *window_impl_construct ( window_factory *p_window_factory, const char *p_title, window *p_window );

window_factory *window_factory_instance ( void )
{
    if ( NULL == _window_factory.p_unique_instance )
    {
        _window_factory.p_unique_instance = sdl_window_factory_instance();
        _window_factory.pfn_window_imp_construct = window_impl_construct;
    }

    return &_window_factory;
}

window_impl *window_impl_construct ( window_factory *p_window_factory, const char *p_title, window *p_window )
{
    return p_window_factory->p_unique_instance->pfn_window_imp_construct(p_window_factory->p_unique_instance,p_title, p_window);
}