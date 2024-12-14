#include "platform.h"

#ifdef _WIN32

#include <Windows.h>
#include <conio.h>

void c_sleep(float seconds)
{
    Sleep(1000 * seconds);
}

char c_getch(void)
{
    return _getch();
}

void c_clear_screen(void)
{
    system("cls");
}
#else
#ifdef __unix__

#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>

void c_sleep(float seconds)
{
    sleep((int)seconds);
}

void c_clear_screen(void)
{
    system("clear");
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

char c_getch(void)
{

    char c = getchar();
    if (c == 127)
        c = '\b';
    return c;
}

#else

#include <stdio.h>

void c_clear_screen(void)
{
    printf("\033[2J\033[H");
}

#endif
#endif
