#pragma once

#include "charcodes.h"

#define ABRUPT_EXIT 1
#define EXIT_SUCCESS 0



#define ECHO 1
#define ECHO_OFF 0
#define ECHO_MASK -1
#define PROMPT_ERR_CANCEL 1
#ifdef _WIN32
#define PROMPT_CANCEL_KEY_S "[ESC]"
#else
#ifdef __unix__
#define PROMPT_CANCEL_KEY_S "[ESC] + [ESC]"
#endif
#endif


int input(char *buffer, char *prompt_s, int max_size, int echo);
void display_menu(char *menu);
void clear_screen(void);