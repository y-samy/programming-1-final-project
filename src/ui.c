#include "ui.h"

#include "platform.h"
#include <stdio.h>
#include <stdlib.h>

void display_menu(char *menu, char *options)
{
    c_clear_screen();
    printf("%s", menu);
}

int *input(char *buffer, const char *prompt, size_t input_size, bool echo)
{
    printf("%s", prompt);
    fflush(stdout);
    if (echo) {
        char c;
        size_t size;
        for (size = 0; (c = getchar()) != EOF && c != '\n' && size < input_size - 1; ++size) {
            buffer[size] = c;
        }
        buffer[size] = '\0';
    } else {
#ifdef __unix__
        termios_echo(false);
#endif
        int size;
        char c;
        for (size = 0; size < input_size - 1; size++) {
            c = c_getch();
            if (c == '\r' || c == EOF || c == '\0' || c == '\n')
                break;
            if (c == '\b') {
                if (size > 0)
                    printf("\b \b");
                size -= 2;
                if (size < 0) {
                    size = -1;
                }
            } else {
                putchar('*');
                buffer[size] = c;
            }
        }
        buffer[size] = '\0';
#ifdef __unix__
        termios_echo(true);
#endif
    }
    return 0;
}
