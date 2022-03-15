#include <UI/UITextInput.h>

UITextInput_t* create_text_input(void)
{
	return 0;
}

UITextInput_t* load_text_input(const char path[])
{
	return 0;
}

UITextInput_t* load_text_input_as_json_tokens(JSONToken_t* tokens, size_t token_count)
{
	return 0;
}

int draw_text_input(UIWindow_t* window, UITextInput_t* text_input)
{
	return 0;
}

int click_text_input(UITextInput_t* text_input, mouse_state_t mouse_state)
{
	return 0;
}

void destroy_text_input(UITextInput_t* text_input)
{
}
