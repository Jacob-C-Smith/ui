#include <compositor/compositor.h>

void compositor_composition_set ( compositor *p_compositor, composition *p_composition ) { p_compositor->p_composition = p_composition; }

void compositor_compose ( compositor *p_compositor ) { (void) p_compositor; }