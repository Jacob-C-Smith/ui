#pragma once

#include <stdarg.h>

#include <ui/ui.h>
#include <glyph/composition.h>
#include <glyph/character.h>

row *row_construct ( void );
row *row_from_string ( const char *string );
row *row_from_arguments ( size_t count, ... );
