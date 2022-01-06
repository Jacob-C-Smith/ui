#include <UI/UIWindow.h>

UIWindow_t* createWindow()
{
	// Initialized data
	UIWindow_t *ret = calloc(1, sizeof(UIWindow_t));

	// Check memory
	{
		#ifndef NDEBUG
			if(ret==(void*)0)
				goto noMem;
		#endif
	}

	return ret;

	// Argument check
	{
		noMem:
		#ifndef NDEBUG
			UIPrintError("[UI] [Window] Failed to allocate memory for UIWindow in call to function \"%s\"\n", __FUNCSIG__);
		#endif
		return 0;
	}
}

UIWindow_t* loadWindow(const char* path)
{
	// Argument check
	{
		#ifndef NDEBUG
			if(path==(void*)0)
				goto noPath;
		#endif
	}

	// Uninitialized data
	u8         *data;
	UIButton_t *ret;

	// Initialized data
	size_t      i   = 0;

	// Load up the file
	i    = UILoadFile(path, 0, false);
	data = calloc(i, sizeof(u8));
	UILoadFile(path, data, false);

	ret = loadWindowAsJSON(data);

	// Finish up
	free(data);

	return ret;

	// Error handling
	{
	noPath:
		#ifndef NDEBUG
			UIPrintError("[UI] [Window] Null pointer provided for \"path\"\n");
		#endif
		return 0;
	invalidFile:
		#ifndef NDEBUG
			UIPrintError("[UI] [Window] Failed to load file %s\n", path);
		#endif
		return 0;
	}
}
UIWindow_t* loadWindowAsJSON(char* token)
{

	// Initialized data
	UIWindow_t  *ret         = createWindow();
	size_t       len         = strlen(token),
                 token_count = parseJSON(token, len, 0, (void*)0);
    JSONToken_t *tokens      = calloc(token_count, sizeof(JSONToken_t));

    // Parse the JSON
    parseJSON(token, len, token_count, tokens);

    // Search through values and pull out relevent information
    for (size_t j = 0; j < token_count; j++)
    {
        //
    }

	ret->window   = SDL_CreateWindow("UI", SDL_WINDOWPOS_CENTERED, 900, 300, 110, SDL_WINDOW_BORDERLESS);
	ret->renderer = SDL_CreateRenderer(ret->window, -1, SDL_RENDERER_ACCELERATED);
	ret->name     = "UI Demo";

	return ret;
}

int         drawWindow ( UIWindow_t *window )
{
	int    w,
		   h,
		   t_1,
		   t_2;

	SDL_Rect r = { 0,0,0,0 };

	size_t len   = strlen(window->name),
		   g_len = len*8;
	

	SDL_SetRenderDrawColor(window->renderer, 0xff, 0xff, 0xff, 0);
	SDL_RenderClear(window->renderer);

	SDL_GetWindowSize(window->window, &w, &h);

	t_1 = (((w-48) / 2) - (g_len / 2)),
	t_2 = (((w-48) / 2) + (g_len / 2));

	r.x = w - 48;
	r.y = 0;
	r.w = 29;
	r.h = 11;

	SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 0);
	SDL_RenderDrawLine(window->renderer, 0, 5, 0, h - 1);
	SDL_RenderDrawLine(window->renderer, w - 1, 5, w - 1, h - 1);
	SDL_RenderDrawLine(window->renderer, 0, h - 1, w - 1, h - 1);
	
	UIDrawText(window->name, window, t_1 + 1, 0, 1);

	SDL_RenderDrawLine(window->renderer, 0, 5, t_1 - 2, 5);
	SDL_RenderDrawLine(window->renderer, t_1 - 2, 0, t_1 - 2, 10);

	SDL_RenderDrawLine(window->renderer, w - 1, 5, t_2 + 1, 5);
	SDL_RenderDrawLine(window->renderer, t_2 + 1, 0, t_2 + 1, 10);

	SDL_RenderFillRect(window->renderer, &r);

	r.x++,
	r.y++,
	r.w-=2,
	r.h-=2;

	SDL_SetRenderDrawColor(window->renderer, 0xff, 0, 0, 0);
	SDL_RenderFillRect(window->renderer, &r);

	return 0;
}

int          destroyWindow(UIWindow_t* window);
