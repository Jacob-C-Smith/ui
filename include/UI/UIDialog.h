#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <UI/UI.h>
#include <UI/UItypedef.h>

// Constructors
UIWindow_t *construct_dialog_box ( char *title, char *prompt, char **options, size_t options_count );
int         dialog_box           ( char *title, char *prompt, char **options, size_t options_count );