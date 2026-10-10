#pragma once

#include <ui/ui.h>

#include <glyph/circle.h>
#include <glyph/column.h>
#include <glyph/row.h>
#include <glyph/mono_glyph.h>
#include <command/radio_button_command.h>
#include <command/radio_button_set_command.h>

radio_button *radio_button_construct( int count, const char *options[] );