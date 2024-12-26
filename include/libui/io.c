#include "io.h"
#include "platform.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef enum { ECHO_OFF, ECHO_THRU, ECHO_MASK, ECHO_ON } echo_t;

static void set_echo(echo_t mode)
{
    switch (mode) {
        case ECHO_OFF:
            printf(CARET_HIDE);
#ifdef __unix__
            termios_echo(false);
#endif
            break;
        case ECHO_MASK:
            printf(CARET_RESET);
#ifdef __unix__
            termios_echo(false);
#endif
            break;
        case ECHO_THRU:
            printf(CARET_RESET);
#ifdef __unix__
            termios_echo(false);
#endif
            break;
        case ECHO_ON:
            printf(CARET_RESET);
#ifdef __unix__
            termios_echo(true);
#endif
            break;
    }
}


void display_menu(char *menu)
{
    fflush(stdout);
    clear_screen();
    printf("%s", menu);
}


static char *month_names[] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "SEP", "AUG", "OCT", "NOV", "DEC"};
static char *highlight_types[] = {ERROR_HIGHLIGHT, SELECTION_HIGHLIGHT};

int input_date(struct tm *date_buffer, struct tm *lower_bound, struct tm *upper_bound)
{
    struct tm temp_date = {0}, starting_date = {0};
    set_echo(ECHO_OFF);
    if (lower_bound != NULL && upper_bound != NULL && difftime(mktime(upper_bound), mktime(lower_bound)) < 0)
        return IO_STATUS_ESC;
    if (lower_bound != NULL && difftime(mktime(date_buffer), mktime(lower_bound)) < 0)
        starting_date = *lower_bound;
    else if (upper_bound != NULL && difftime(mktime(date_buffer), mktime(upper_bound)) > 0)
        starting_date = *upper_bound;
    else
        starting_date = *date_buffer;
    sanitize_date(&starting_date);
    temp_date = starting_date;
    int c;
    int current_choice = 0;
    char *date_highlight = highlight_types[1];
    while (1) {
        switch (current_choice) {
            case 0:
                printf(CLEAR_LN "%s%02d" CLR_RESET " / %s / %d", date_highlight, temp_date.tm_mday,
                       month_names[temp_date.tm_mon], temp_date.tm_year + 1900);
                break;
            case 1:
                printf(CLEAR_LN "%02d / " "%s%s" CLR_RESET " / %d", temp_date.tm_mday,
                       date_highlight, month_names[temp_date.tm_mon], temp_date.tm_year + 1900);
                break;
            case 2:
                printf(CLEAR_LN "%02d / %s / " "%s%d" CLR_RESET, temp_date.tm_mday,
                       month_names[temp_date.tm_mon], date_highlight, temp_date.tm_year + 1900);
                break;
        }
        c = get_key();
        switch (c) {
            case '\n':
                *date_buffer = temp_date;
                printf(CLEAR_LN CLR_RESET "%02d / %s / %d\n", date_buffer->tm_mday,
                       month_names[date_buffer->tm_mon], date_buffer->tm_year + 1900);
                set_echo(ECHO_ON);
                return 0;
            case CTRL_Z_KEY:
                if ((int) difftime(mktime(&temp_date),mktime(&starting_date)) != 0) {
                    temp_date = starting_date;
                    continue;
                }
                printf(CLEAR_LN);
                set_echo(ECHO_ON);
                return IO_STATUS_UNDO;
            case ESC_KEY:
                printf(CLEAR_LN);
                set_echo(ECHO_ON);
                return IO_STATUS_ESC;
            case CTRL_C_KEY:
            case CTRL_D_KEY:
            case EOF:
                printf(CLEAR_LN);
                set_echo(ECHO_ON);
                return IO_STATUS_EXIT;
            case ARR_RIGHT_KEY:
                if (current_choice < 2)
                    current_choice++;
                break;
            case ARR_LEFT_KEY:
                if (current_choice > 0)
                    current_choice--;
                break;
            case ARR_DOWN_KEY:
                switch (current_choice) {
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
                switch (current_choice) {
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
        if (lower_bound != NULL && difftime(mktime(&temp_date), mktime(lower_bound)) < 0) {
            temp_date = *lower_bound;
            date_highlight = highlight_types[0];
        }
        else if (upper_bound != NULL && difftime(mktime(&temp_date), mktime(upper_bound)) > 0) {
            temp_date = *upper_bound;
            date_highlight = highlight_types[0];
        }
        else
            date_highlight = highlight_types[1];
        sanitize_date(&temp_date);
    }
}

int input(char *buffer, char *prompt_s, int max_size, int input_type, bool edit)
{
    printf(CLEAR_LN "%s", prompt_s);
    fflush(stdout);
    echo_t echo_mode = ECHO_THRU;
    if (input_type == INPUT_PASSWORD)
        echo_mode = ECHO_MASK;

    set_echo(echo_mode);

    int i = 0;
    int c;
    bool input_valid = false;
    int floating_point_i = -1;
    int email_at_i = -1;
    int email_dot_i = -1;
    if (edit) {
        i = strlen(buffer);
        printf("%s", buffer);
        if (input_type == INPUT_EMAIL) {
            int j;
            for (j = 0; j < i; j++) {
                c = buffer[j];
                if (c == '@' && email_at_i == -1)
                    email_at_i = j;
                if (c == '.' && email_dot_i == -1)
                    email_dot_i = j;
            }
        }
    } else
        buffer[0] = '\0';
    while (true) {
        c = get_key(); /* does not print what you type */
        if (c == ESC_KEY) {
            printf(CLEAR_LN);
            set_echo(ECHO_ON);
            return IO_STATUS_ESC;
        }
        if (c == CTRL_Z_KEY) {
            printf(CLEAR_LN);
            if (buffer[0] != '\0') {
                floating_point_i = -1;
                email_at_i = -1;
                email_dot_i = -1;
                buffer[0] = '\0';
                printf("%s", prompt_s);
                fflush(stdout);
                i = 0;
                continue;
            }
            set_echo(ECHO_ON);
            return IO_STATUS_UNDO;
        }
        if (c == EOF || c == CTRL_C_KEY || c == CTRL_D_KEY) {
            printf(CLEAR_LN);
            set_echo(ECHO_ON);
            return IO_STATUS_EXIT;
        }
        if (c == '\n' && i > 0) {
            if (input_type == INPUT_EMAIL && (email_at_i == -1 || email_dot_i == -1 || buffer[i - 1] == '@' || buffer[
                                                  i - 1] == '.' || buffer[i - 2] == '.')) {
                printf(CARET_ERROR);
                continue;
            }
            putchar('\n');
            break;
        }
        if ((c == BACKSPACE_KEY || c == BACKSPACE_EC) && i > 0) {
            /* Backspace simulation */
            printf(CARET_RESET);
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
                    input_valid = (c >= ' ' && c < 127);
                    break;
                case INPUT_USERNAME:
                case INPUT_PASSWORD:
                    input_valid = (c > ' ' && c < 127);
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
                    input_valid = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == ' ');
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
                    if (c == '@' && email_at_i == -1 && i && buffer[i - 1] != '.') {
                        email_at_i = i;
                        input_valid = true;
                    } else if (c == '.' && buffer[i - 1] != '.' && i && buffer[i - 1] != '@') {
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
            printf(CARET_RESET);
            if (echo_mode == ECHO_THRU)
                putchar(c);
            else /* Password hiding */
                putchar('*');

            buffer[i] = c;
            i++;
        } else {
            printf(CARET_ERROR);
        }
    }
    buffer[i] = '\0';

    set_echo(ECHO_ON);
    return 0;
}

int choices(char *choices)
{
    set_echo(false);
    printf(CARET_HIDE);
    int current_choice = 1;
    int i = 0, choice_count = 0;
    while (choices[i] != '\0') {
        if (choices[i++] == '\n')
            choice_count++;
    }
    char *choices_s = malloc(sizeof(char) * (i + 1));
    strcpy(choices_s, choices);
    char **choice_i = malloc(sizeof(char *) * choice_count);
    char *_token = NULL;
    _token = strtok(choices_s, "\n");
    i = 0;
    while (_token != NULL) {
        choice_i[i++] = _token;
        _token = strtok(NULL, "\n");
    }
    printf(SELECTION_HIGHLIGHT ">%s\n" CLR_RESET, choice_i[0]);
    for (i = 1; i < choice_count; ++i) {
        printf(CLEAR_LN "%s\n", choice_i[i]);
    }
    printf("\033[%dA", choice_count);
    char c;
    while (1) {
        int i;
        c = get_key();
        if (c == ESC_KEY) {
            for (; current_choice < choice_count; ++current_choice) {
                printf(CUR_DOWN);
            }
            for (i = 1; i < choice_count; ++i) {
                printf(CLEAR_LN CUR_UP CLEAR_LN);
            }
            set_echo(ECHO_ON);
            free(choices_s);
            free(choice_i);
            return IO_STATUS_ESC;
        }
        if (c == CTRL_Z_KEY) {
            for (; current_choice < choice_count; ++current_choice) {
                printf(CUR_DOWN);
            }
            for (i = 1; i < choice_count; ++i) {
                printf(CLEAR_LN CUR_UP CLEAR_LN);
            }
            set_echo(ECHO_ON);
            free(choices_s);
            free(choice_i);
            return IO_STATUS_UNDO;
        }
        if (c == EOF || c == CTRL_C_KEY || c == CTRL_D_KEY) {
            for (; current_choice < choice_count; ++current_choice) {
                printf(CUR_DOWN);
            }
            for (i = 1; i < choice_count; ++i) {
                printf(CLEAR_LN CUR_UP CLEAR_LN);
            }
            set_echo(ECHO_ON);
            free(choices_s);
            free(choice_i);
            return IO_STATUS_EXIT;
        }
        if ((c == '\n' || c == '\r')) {
            for (i = current_choice; i < choice_count; ++i) {
                printf(CUR_DOWN);
            }
            for (i = 1; i < choice_count; ++i) {
                printf(CLEAR_LN CUR_UP CLEAR_LN);
            }
            printf("%s", choice_i[current_choice - 1]);
            set_echo(ECHO_ON);
            free(choices_s);
            free(choice_i);
            return current_choice;
        }
        if (c == ARR_UP_KEY && current_choice > 1) {
            printf(CLEAR_LN CLR_RESET "%s" CUR_UP CLEAR_LN SELECTION_HIGHLIGHT ">%s" CLR_RESET,
                   choice_i[current_choice - 1],
                   choice_i[current_choice - 2]);
            current_choice--;
        } else if (c == ARR_DOWN_KEY && current_choice < choice_count) {
            printf(CLEAR_LN CLR_RESET "%s" CUR_DOWN CLEAR_LN SELECTION_HIGHLIGHT ">%s" CLR_RESET,
                   choice_i[current_choice - 1],
                   choice_i[current_choice]);
            current_choice++;
        } else if (c == ARR_UP_KEY && current_choice == 1) {
            printf(CLEAR_LN CLR_RESET "%s\033[%dB" CLEAR_LN SELECTION_HIGHLIGHT ">%s" CLR_RESET,
                   choice_i[current_choice - 1]
                   , choice_count - 1, choice_i[choice_count - 1]);
            current_choice = choice_count;
        } else if (c == ARR_DOWN_KEY && current_choice == choice_count) {
            current_choice = 1;
            printf(CLEAR_LN CLR_RESET "%s\033[%dA" CLEAR_LN SELECTION_HIGHLIGHT ">%s" CLR_RESET,
                   choice_i[choice_count - 1]
                   , choice_count - 1, choice_i[current_choice - 1]);
        }
    }
}
