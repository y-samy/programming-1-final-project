#pragma once

#define CLEAR_LN "\33[2K\r"
#define CUR_UP "\033[A"
#define CUR_DOWN "\033[B"

#define CARET_HIDE "\033[?25l"
#define CARET_RESET "\033[?25h"

#define CLR_TEXT_RED "\033[1;35m"
#define CLR_TEXT_BLACK "\033[1;30m"
#define CLR_BG_YLW "\033[1;43m"
#define CLR_RESET "\033[0m"

#define CTRL_C_KEY 3
#define ESC_KEY 27
#define BACKSPACE_KEY 8
#define DEL_KEY 127

#define ARR_UP_KEY -'A'
#define ARR_DOWN_KEY -'B'

#ifdef _WIN32
#define ARR_UP_EC 72
#define ARR_DOWN_EC 80
#else
#ifdef __unix__
#define ARR_UP_EC 65
#define ARR_DOWN_EC 66
#endif
#endif