#pragma once

#include <ui/ui.h>
#include <glyph/glyph.h>
#include <glyph/composition.h>

overlay *overlay_construct ( void );
overlay *overlay_from_arguments ( size_t count, ... );
