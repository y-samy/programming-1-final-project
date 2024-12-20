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

const char *month_names[]  = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "SEP", "AUG", "OCT", "NOV", "DEC"};

int input_date(struct tm *date)
{
    printf("Pick a day\n");
    fflush(stdout);
#ifdef __unix__
    termios_echo(false);
#endif
    struct tm current_date = get_current_date();
    current_date.tm_sec = current_date.tm_hour = current_date.tm_min = 0;
    *date = current_date;
    struct tm temp_date = *date;
    char c;
    int current_choice = 0;

    while (1) {
        temp_date = *date;
        switch (current_choice) {
            case 0:
                printf(CLEAR_LN CLR_BG_YLW "%02d" CLR_RESET " / %s / %d", date->tm_mday, month_names[date->tm_mon], date->tm_year + 1900);
            break;
            case 1:
                printf(CLEAR_LN "%02d / " CLR_BG_YLW "%s" CLR_RESET " / %d", date->tm_mday, month_names[date->tm_mon], date->tm_year + 1900);
            break;
            case 2:
                printf(CLEAR_LN "%02d / %s / " CLR_BG_YLW "%d" CLR_RESET, date->tm_mday, month_names[date->tm_mon], date->tm_year + 1900);
            break;

        }
        c = get_key();
        switch (c) {
            case '\n':
                case '\r':
            return 0;
            case ESC_KEY:
                return IO_STATUS_ESC;
            case ARR_RIGHT_KEY:
                if (current_choice < 2)
                current_choice++;
            break;
            case ARR_LEFT_KEY:
                if (current_choice > 0)
                    current_choice--;
            break;
            case ARR_DOWN_KEY:
                switch(current_choice) {
                    case 0:
                        temp_date.tm_mday--;
                    break;
                    case 1:
                        temp_date.tm_mon--;
                    break;
                    case 2:
                        temp_date.tm_year--;
                    break;
                }
            break;
            case ARR_UP_KEY:
                switch(current_choice) {
                    case 0:
                        temp_date.tm_mday++;
                    break;
                    case 1:
                        temp_date.tm_mon++;
                    break;
                    case 2:
                        temp_date.tm_year++;
                    break;
                }
            break;
        }
        if (difftime(mktime(&current_date), mktime(&temp_date)) <= 0)
            *date = temp_date;

    }
#ifdef __unix__
    termios_echo(true);
#endif
}

int input(char *buffer, char *prompt_s, int max_size, int input_type)
{
    printf("%s", prompt_s);
    fflush(stdout);
    int echo = ECHO;
    if (input_type == INPUT_PASSWORD)
        echo = ECHO_MASK;
    /* Turn cursor off if ECHO_OFF */
    if (echo != ECHO_OFF)
        printf(CARET_RESET);
    else
        printf(CARET_HIDE);
#ifdef __unix__
    termios_echo(false);
#endif

    int i = 0;
    char c;
    bool input_valid = false;
    int floating_point_i = -1;
    int email_at_i = -1;
    int email_dot_i = -1;
    while (true) {
        c = get_key(); /* does not print what you type */
        if (c == ESC_KEY)
            return IO_STATUS_ESC;
        if (c == EOF || c == CTRL_C_KEY)
            exit(ABRUPT_EXIT);
        if ((c == '\n' || c == '\r') && i > 0) {
            if (input_type == INPUT_EMAIL && (email_at_i == -1 || email_dot_i == -1 || buffer[i-1] == '@' || buffer[i-1] == '.' || buffer[i-2] == '.'))
                continue;
            break;
        }
        if ((c == BACKSPACE_KEY || c == DEL_KEY) && i > 0) {
            /* Backspace simulation */
            printf("\b \b");
            i--;
            if (i == floating_point_i)
                floating_point_i = -1;
            if (i == email_at_i)
                email_at_i = -1;
            if (i == email_dot_i)
                email_dot_i = -1;
            continue;
        }
        input_valid = false;
        if (i != max_size - 1) {
            switch (input_type) {
                case INPUT_ANY:
                    input_valid = (c >= ' ' && c < 128);
                    break;
                case INPUT_USERNAME:
                case INPUT_PASSWORD:
                    input_valid = (c > ' ' && c < 128);
                    break;
                case INPUT_INT_POSITIVE:
                    input_valid = (c >= '0' && c <= '9');
                    break;
                case INPUT_INT_ANY:
                    input_valid = (i == 0 && c == '-') || (c >= '0' && c <= '9');
                    break;
                case INPUT_ALPHANUMERIC:
                    input_valid = (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
                    break;
                case INPUT_ALPHABETICAL:
                    input_valid = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
                    break;
                case INPUT_FLOAT_ANY:
                    if (c == '.' && floating_point_i == -1) {
                        floating_point_i = i;
                        input_valid = true;
                    } else
                        input_valid = (i == 0 && c == '-') || (c >= '0' && c <= '9');
                    break;
                case INPUT_FLOAT_POSITIVE:
                    if (c == '.' && floating_point_i == -1) {
                        floating_point_i = i;
                        input_valid = true;
                    } else
                        input_valid = (c >= '0' && c <= '9');
                    break;
                case INPUT_EMAIL:
                    if (c == '@' && email_at_i == -1 && i && buffer[i-1] != '.') {
                        email_at_i = i;
                        input_valid = true;
                    } else if (c == '.' && buffer[i - 1] != '.' && i && buffer[i-1] != '@') {
                        if (email_at_i != -1 && email_dot_i == -1)
                            email_dot_i = i;
                        input_valid = true;
                    } else {
                        input_valid = (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
                    }
                    break;
            }
        }
        if (input_valid) {
            /* Echo handling */
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
#ifdef __unix__
    termios_echo(false);
#endif

    printf(CARET_HIDE);
    int current_choice = 1;
    int i = 0, choice_count = 0;
    while (choices[i] != '\0') {
        if (choices[i++] == '\n')
            choice_count++;
    }
    char *_choices_s = malloc(sizeof(char) * (i + 1));
    strcpy(_choices_s, choices);
    char **choice_i = malloc(sizeof(char *) * choice_count);
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
        if (c == ESC_KEY) {
#ifdef __unix__
    termios_echo(true);
#endif
            free(_choices_s);
            free(choice_i);
            return IO_STATUS_ESC;
        }
        if (c == EOF || c == CTRL_C_KEY)
            exit(ABRUPT_EXIT);
        if ((c == '\n' || c == '\r')) {
            free(_choices_s);
            free(choice_i);
#ifdef __unix__
            termios_echo(true);
#endif
            return current_choice;
        }
        if (c == ARR_UP_KEY && current_choice > 1) {
            printf(CLEAR_LN CLR_RESET "%s" CUR_UP CLEAR_LN CLR_BG_YLW ">%s" CLR_RESET, choice_i[current_choice - 1],
                   choice_i[current_choice - 2]);
            current_choice--;
        } else if (c == ARR_DOWN_KEY && current_choice < choice_count) {
            printf(CLEAR_LN CLR_RESET "%s" CUR_DOWN CLEAR_LN CLR_BG_YLW ">%s" CLR_RESET, choice_i[current_choice - 1],
                   choice_i[current_choice]);
            current_choice++;
        }
    }
}
