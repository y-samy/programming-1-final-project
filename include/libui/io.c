#include "io.h"
#include "platform.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    if (echo != ECHO_OFF)
        printf(CARET_RESET);
    else
        printf(CARET_HIDE);
#ifdef __unix__
    termios_echo(false);
#endif

    int i;
    char c;
    for (i = 0; i < max_size - 1; ) {

        c = get_key(); /* does not print what you type */
        if (c == ESC_KEY)
            return IO_STATUS_ESC;
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

int choices(char *choices)
{
    printf(CARET_HIDE);
    int current_choice = 1;
    int i = 0, choice_count = 0;
    while (choices[i] != '\0') {
        if (choices[i++] == '\n')
            choice_count++;
    }
    char *_choices_s = malloc(sizeof(char) * (i + 1));
    strcpy(_choices_s, choices);
    char **choice_i = malloc(sizeof(char*) * choice_count);
    char *_token = NULL;
    _token = strtok(_choices_s, "\n");
    i = 0;
    while (_token != NULL) {
        choice_i[i++] = _token;
        _token = strtok(NULL, "\n");
    }
    printf(CLR_BG_YLW ">%s\n" CLR_RESET, choice_i[0]);
    for (i = 1; i < choice_count; ++i) {
        printf("%s\n", choice_i[i]);
    }
    printf("\033[%dA", choice_count);
    char c;
    while (1) {
        c = get_key();
        if (c == ESC_KEY)
            return IO_STATUS_ESC;
        if (c == EOF || c == CTRL_C_KEY)
            exit(ABRUPT_EXIT);
        if ((c == '\n' || c == '\r')) {
            free(_choices_s);
            free(choice_i);
            return current_choice;
        }
        if (c == ARR_UP_KEY && current_choice > 1) {
            printf(CLEAR_LN CLR_RESET "%s" CUR_UP CLEAR_LN CLR_BG_YLW ">%s" CLR_RESET, choice_i[current_choice-1], choice_i[current_choice - 2]);
            current_choice--;
        } else if (c == ARR_DOWN_KEY && current_choice < choice_count) {
            printf(CLEAR_LN CLR_RESET "%s" CUR_DOWN CLEAR_LN CLR_BG_YLW ">%s" CLR_RESET, choice_i[current_choice-1], choice_i[current_choice]);
            current_choice++;
        }
    }
}