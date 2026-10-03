#include <compositor/null_compositor.h>

void null_compositor_compose ( compositor *p_compositor );

null_compositor *null_compositor_construct ( void )
{
    null_compositor *p_null_compositor = default_allocator(NULL, sizeof(null_compositor));

    *p_null_compositor = (null_compositor)
    {
        ._compositor = 
        {
            .pfn_compositor_composition_set = compositor_composition_set,
            .pfn_compositor_compose = null_compositor_compose,
        }
    };

    return p_null_compositor;
}

void null_compositor_compose ( compositor *p_compositor ) { (void) p_compositor; }
