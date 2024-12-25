#pragma once

#include "charcodes.h"
#include <libdate.h>
#include <stdbool.h>

#define SELECTION_HIGHLIGHT CLR_BG_CYAN CLR_TEXT_BLACK
#define ERROR_HIGHLIGHT CLR_BG_RED CLR_TEXT_WHITE
#define TABLE_HIGHLIGHT CLR_BG_WHITE CLR_TEXT_BLACK

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

#define IO_STATUS_ESC -ESC_KEY
#define IO_STATUS_EXIT -CTRL_C_KEY
#define IO_STATUS_UNDO -CTRL_Z_KEY


#define PROMPT_UNDO_KEY_S "[CTRL-Z]"
#ifdef _WIN32
#define PROMPT_CANCEL_KEY_S "[ESC]"
#else
#ifdef __unix__
#define PROMPT_CANCEL_KEY_S "[ESC] + [ESC]"
#endif
#endif


int input(char *buffer, char *prompt_s, int max_size, int input_type, bool edit);
int input_date(struct tm *date_buffer, struct tm *lower_bound, struct tm *upper_bound);
int choices(char *choices);
void display_menu(char *menu);
void clear_screen(void);