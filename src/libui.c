#include "libui.h"

#include <stdio.h>
#include "platform.h"


void clear_screen(void)
{
    c_clear_screen();
}

void prompt_gets(char *buffer, size_t input_size, int echo)
{
#ifdef __unix__
    termios_echo(false);
#endif

    int size;
    char c;
    for (size = 0; size < input_size - 1; size++) {

        /* Cross-platform get-keypress function */
        c = c_getch();
        if (c == '\n' || c == EOF || c == 3 || c == '\r')
            break;


        if (c == '\b') { /* Backspace simulation */
            if (size > 0) {
                printf("\b \b");
                size--;
            }
            size--;
        } else { /* Echo handling */
            if (echo == ECHO)
                putchar(c);
            else if (echo == ECHO_MASK) /* Password hiding */
                putchar('*');
            /* If ECHO_OFF, nothing is sent out */

            buffer[size] = c;
        }
    }
    buffer[size] = '\0';

#ifdef __unix__
    termios_echo(true);
#endif
}


int *input(char *buffer, char* prompt_s, size_t input_size, int echo)
{
    printf("%s", prompt_s);
    fflush(stdout);
    prompt_gets(buffer, input_size, echo);
    return 0;
}