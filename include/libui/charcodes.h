#pragma once

#define CLEAR_LN "\33[2K\r"
#define CUR_UP "\033[A"
#define CUR_DOWN "\033[B"

#define CARET_HIDE "\033[?25l"
#define CARET_RESET "\033[?25h"

#define CLR_TEXT_RED "\033[31m"
#define CLR_TEXT_GREEN "\033[32m"
#define CLR_TEXT_BLACK "\033[30m"
#define CLR_BG_RED "\033[41m"
#define CLR_BG_GREEN "\033[42m"
#define CLR_BG_YLW "\033[43m"
#define CLR_RESET "\033[0m"

#define CTRL_C_KEY 3
#define ESC_KEY 27
#define BACKSPACE_KEY 8
#define DEL_KEY 127

#define ARR_UP_KEY -'A'
#define ARR_DOWN_KEY -'B'
#define ARR_LEFT_KEY -'C'
#define ARR_RIGHT_KEY -'D'

#ifdef _WIN32
#define ARR_UP_EC 72
#define ARR_DOWN_EC 80
#define ARR_RIGHT_EC 77
#define ARR_LEFT_EC 75
#else
#ifdef __unix__
#define ARR_UP_EC 65
#define ARR_DOWN_EC 66
#define ARR_RIGHT_EC 67
#define ARR_LEFT_EC 68
#endif
#endif