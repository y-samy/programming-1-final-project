#include "io.h"
#include "platform.h"
#include <stdlib.h>
#include <stdio.h>

void display_menu(char *menu)
{
    clear_screen();
    printf("%s", menu);
}

int input(char *buffer, char* prompt_s, int max_size, int echo)
{
    printf("%s", prompt_s);
    fflush(stdout);
    /* Turn cursor off if ECHO_OFF */
    if (echo == ECHO_OFF)
        printf(CARET_HIDE);
#ifdef __unix__
    termios_echo(false);
#endif

    int i;
    char c;
    for (i = 0; i < max_size - 1; ) {

        c = get_key(); /* does not print what you type */
        if (c == ESC_KEY)
            return PROMPT_ERR_CANCEL;
        if (c == EOF || c == CTRL_C_KEY)
            exit(ABRUPT_EXIT);
        if ((c == '\n' || c == '\r') && i > 0)
            break;
        if ((c == BACKSPACE_KEY || c == DEL_KEY) && i > 0) { /* Backspace simulation */
                printf("\b \b");
                i--;
        }
        if (c > 32 && c < 129) { /* Echo handling */
            if (echo == ECHO)
                putchar(c);
            else if (echo == ECHO_MASK) /* Password hiding */
                putchar('*');
            /* If ECHO_OFF, nothing is sent out */

            buffer[i] = c;
            i++;
        }
    }
    buffer[i] = '\0';

#ifdef __unix__
    termios_echo(true);
#endif

    return 0;
}