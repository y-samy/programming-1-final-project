#include "platform.h"

#include <stdlib.h>
#include <stdio.h>

#include "charcodes.h"

#ifdef _WIN32
#include <conio.h>

void clear_screen(void)
{
    system("cls");
    printf(CLR_RESET CARET_RESET CUR_ORIGIN);
}

int get_key(void)
{
    int c = _getch();
    if (c == '\r')
        return '\n';
    if (c == 0 || c == 0xE0) {
        c = _getch();
        switch (c) {
            case ESC_KEY:
                c = ESC_KEY;
                break;
            case ARR_UP_EC:
                c = ARR_UP_KEY;
                break;
            case ARR_LEFT_EC:
                c = ARR_LEFT_KEY;
                break;
            case ARR_DOWN_EC:
                c = ARR_DOWN_KEY;
                break;
            case ARR_RIGHT_EC:
                c = ARR_RIGHT_KEY;
                break;
            default:
                c = 0;
        }
    }
    return c;
}

#else
#ifdef __unix__

#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>

void clear_screen(void)
{
    system("clear");
    printf(CLR_RESET CARET_RESET CUR_ORIGIN);
}

int termios_echo(bool state)
{
    /* https://stackoverflow.com/a/32421674 */
    static struct termios old_kbd_mode;
    static struct termios new_kbd_mode;
    if (!state) {
        if (tcgetattr (0, &old_kbd_mode)) {
            fprintf (stderr, "%s() error: tcgetattr failed.\n", __func__);
        }
        memcpy (&new_kbd_mode, &old_kbd_mode, sizeof(struct termios));

        new_kbd_mode.c_lflag &= ~(ICANON | ECHO | ISIG | ICRNL | IXON);
        new_kbd_mode.c_cc[VTIME] = 0;
        new_kbd_mode.c_cc[VMIN] = 1;
        if (tcsetattr (0, TCSANOW, &new_kbd_mode)) {
            fprintf (stderr, "%s() error: tcsetattr failed.\n", __func__);
        }
    } else {
        if (tcsetattr (0, TCSANOW, &old_kbd_mode)) {
            fprintf (stderr, "%s() error: tcsetattr failed.\n", __func__);
        }
    }
}

int get_key(void)
{

    int c = getchar();
    if (c == ESC_KEY) {
        c = getchar();
        if (c == ESC_KEY)
            return ESC_KEY;
        if (c == '[')
        {
            c = getchar();
            switch (c) {
                case ESC_KEY:
                    c = ESC_KEY;
                break;
                case ARR_UP_EC:
                    c = ARR_UP_KEY;
                break;
                case ARR_LEFT_EC:
                    c = ARR_LEFT_KEY;
                break;
                case ARR_DOWN_EC:
                    c = ARR_DOWN_KEY;
                break;
                case ARR_RIGHT_EC:
                    c = ARR_RIGHT_KEY;
                break;
                default:
                    c = 0;
            }
        }
    }
    return c;
}
#endif
#endif
