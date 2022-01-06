#include <UI/UILabel.h>

UILabel_t* createLabel()
{
	// Initialized data
	UILabel_t *ret = calloc(1, sizeof(UILabel_t));
	
	// Check allocated memory, if in debug mode
	{
		#ifndef NDEBUG
		if (ret == (void*)0)
			goto noMem;
		#endif
	}
	
	// Return a pointer to the start of the struct
	return (UIButton_t *) ret;

	// Error handling
	{
		noMem:
		#ifndef NDEBUG
			UIPrintError("[UI] [Label] Failed to create a label; Out of memory\n");
		#endif
		return (void*)0;
	}
}

UILabel_t* loadLabel ( const char path [ ] )
{
	// Uninitialized data
    u8         *data;
	UILabel_t  *ret;

    // Initialized data
    size_t      i   = 0;

    // Load up the file
    i    = UILoadFile(path, 0, false);
    data = calloc(i, sizeof(u8));
    UILoadFile(path, data, false);

    ret  = loadLabelAsJSON(data);

    // Finish up
    free(data);

    return ret;

    // Error handling
    {
        invalidFile:
            #ifndef NDEBUG
                UIPrintError("[UI] [Label] Failed to load file %s\n", path);
            #endif
        return 0;
    }
}

UILabel_t* loadLabelAsJSON ( char* token )
{
	// Initialized data
    UILabel_t   *ret         = createLabel();
    size_t       len         = strlen(token),
                 token_count = parseJSON(token, len, 0, (void*)0);
    JSONToken_t *tokens      = calloc(token_count, sizeof(JSONToken_t));

    // Parse the JSON
    parseJSON(token, len, token_count, tokens);

    // Search through values and pull out relevent information
    for (size_t j = 0; j < token_count; j++)
    {
        // Handle comments
        if (strcmp("text", tokens[j].key) == 0)
        {
			char   *label_text     = tokens[j].value.nWhere;
			size_t  label_text_len = strlen(label_text);

			ret->text              = calloc(label_text_len, sizeof(u8));

			// TODO: Check RAM

			strncpy(ret->text, label_text, label_text_len);
        }

		else if ( strcmp("x", tokens[j].key) == 0 )
			if( tokens[j].type == JSONprimative )
				ret->x = atoi(tokens[j].value.nWhere);

		else if (strcmp("y", tokens[j].key) == 0)
			if( tokens[j].type == JSONprimative )
				ret->y = atoi(tokens[j].value.nWhere);

    }
}

int drawLabel ( UIWindow_t *window, UILabel_t* label )
{
	// TODO: Argument checks
	// TODO: Remove any % symbols
	if(label->hidden == false) 
		SDL_SetRenderDrawColor(window->renderer, 0x00, 0x00, 0x00, 0xff);
		UIDrawText(label->text, window, label->x, label->y, 1);

	return 0;

	// TODO: Error handling
}

void destroyLabel(UILabel_t* label)
{
	// TODO: 
}
