#pragma once

#include "charcodes.h"
#include <libdate.h>
#include <stdbool.h>

#define SELECTION_HIGHLIGHT CLR_BG_CYAN CLR_TEXT_BLACK
#define ERROR_HIGHLIGHT "\a" CLR_BG_RED CLR_TEXT_WHITE
#define TABLE_HIGHLIGHT CLR_BG_WHITE CLR_TEXT_BLACK

typedef enum {INPUT_ANY, INPUT_USERNAME, INPUT_PASSWORD, INPUT_ALPHANUMERIC, INPUT_ALPHABETICAL,INPUT_INT_POSITIVE,
    INT_POSITIVE_ALLOW_LEADING_ZEROES, INPUT_INT_ANY, INPUT_FLOAT_POSITIVE, INPUT_FLOAT_ANY, INPUT_EMAIL} VALIDATION_TYPE;

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


int input(char *buffer, char *prompt_s, int max_size, VALIDATION_TYPE input_type, bool edit);
int input_date(struct tm* date_buffer, struct tm* lower_bound, struct tm* upper_bound);
int choices(char* choices);
void display_menu(char* menu);
void clear_screen(void);
