#pragma once

#include <stdarg.h>

#include <ui/ui.h>
#include <glyph/composition.h>
#include <glyph/row.h>

column *column_construct ( void );
column *column_from_strings ( int count, const char *string[], bool bold, bool italic, float size );
column *column_from_arguments ( size_t count, ... );