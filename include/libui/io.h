#pragma once

#include "charcodes.h"
#include <libdate.h>

#define ABRUPT_EXIT 1
#define EXIT_SUCCESS 0


#define INPUT_ANY 0
#define INPUT_USERNAME 1
#define INPUT_PASSWORD 2
#define INPUT_ALPHANUMERIC 3
#define INPUT_ALPHABETICAL 4
#define INPUT_INT_POSITIVE 5
#define INPUT_INT_ANY 6
#define INPUT_FLOAT_POSITIVE 7
#define INPUT_FLOAT_ANY 8
#define INPUT_EMAIL 9

#define ECHO 1
#define ECHO_OFF 0
#define ECHO_MASK -1

#define IO_STATUS_ESC -ESC_KEY
#ifdef _WIN32
#define PROMPT_CANCEL_KEY_S "[ESC]"
#else
#ifdef __unix__
#define PROMPT_CANCEL_KEY_S "[ESC] + [ESC]"
#endif
#endif


int input(char *buffer, char *prompt_s, int max_size, int input_type);
int input_date(struct tm *date);
int choices(char *choices);
void display_menu(char *menu);
void clear_screen(void);