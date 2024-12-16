#include "platform.h"

#include <stdlib.h>
#include <stdio.h>

#include "charcodes.h"

#ifdef _WIN32
#include <conio.h>

void clear_screen(void)
{
    system("cls");
    printf(CLR_RESET CARET_RESET);
}

int get_key(void)
{
    int c = _getch();
    if (c == 0 || c == 0xE0) {
        c = _getch();
        switch (c) {
            case ESC_KEY:
                c = ESC_KEY;
                break;
            case ARR_UP_EC:
                c = ARR_UP_KEY;
                break;
            case ARR_DOWN_EC:
                c = ARR_DOWN_KEY;
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
    printf(CLR_RESET CARET_RESET);
}

int termios_echo(bool state)
{
    /* https://stackoverflow.com/a/32421674 */
    static struct termios old_kbd_mode;    /* orig keyboard settings   */
    static struct termios new_kbd_mode;
    if (!state) {
        if (tcgetattr (0, &old_kbd_mode)) { /* save orig settings   */
            fprintf (stderr, "%s() error: tcgetattr failed.\n", __func__);
        }
        memcpy (&new_kbd_mode, &old_kbd_mode, sizeof(struct termios));

        new_kbd_mode.c_lflag &= ~(ICANON | ECHO);  /* new kbd flags */
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
    if (c == ESC_K) {
        c = getchar();
        if (c == ESC_KEY)
            return ESC_KEY;
        if (c == '[')
            switch (c) {
                case ARR_UP_EC:
                    c = ARR_UP_KEY;
                break;
                case ARR_DOWN_EC:
                    c = ARR_DOWN_KEY;
                break;
                default:
                    c = 0;
            }
        return 0;
    }
    return c;
}

#else

#include <stdio.h>



#endif
#endif
