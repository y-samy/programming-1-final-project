#pragma once


#define CSI             "\033[" /* Control sequence introducer */
#define OSC             "\033]" /* Operating system command */

#define CLEAR_LN        CSI "2K\r"
#define CUR_UP          CSI "A"
#define CUR_DOWN        CSI "B"
#define CUR_ORIGIN      CSI "1;1H"

#define CARET_HIDE      CSI "?25l"
#define CARET_RESET     CSI "?25h" CSI "0 q"
#define CLR_TEXT_RED    CSI "31m"
#define CLR_TEXT_GREEN  CSI "32m"
#define CLR_TEXT_BLACK  CSI "30m"
#define CLR_TEXT_WHITE  CSI "37m"
#define CLR_BG_WHITE    CSI "47m"
#define CLR_BG_RED      CSI "41m"
#define CLR_BG_GREEN    CSI "42m"
#define CLR_BG_CYAN     CSI "46m"
#define CLR_BG_YLW      CSI "43m"
#define CLR_RESET       CSI "0m"

#define CTRL_C_KEY      3
#define CTRL_D_KEY      4
#define CTRL_Z_KEY      26

#define ESC_KEY         27

#define BACKSPACE_EC    8
#define BACKSPACE_KEY   127

#define DEL_KEY         -BACKSPACE_KEY

#define ARR_UP_KEY      -'A'
#define ARR_DOWN_KEY    -'B'
#define ARR_LEFT_KEY    -'C'
#define ARR_RIGHT_KEY   -'D'

#ifdef _WIN32
#define ARR_UP_EC       72
#define ARR_DOWN_EC     80
#define ARR_RIGHT_EC    77
#define ARR_LEFT_EC     75

#define DEL_EC          83
#else
#ifdef __unix__
#define ARR_UP_EC       65
#define ARR_DOWN_EC     66
#define ARR_RIGHT_EC    67
#define ARR_LEFT_EC     68

#define DEL_EC          61
#endif
#endif
