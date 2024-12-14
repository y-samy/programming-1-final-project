/*
* Pragma once to prevent the includes
 * from happening multiple times
 */
#pragma once
#include <stdbool.h>

void c_sleep(float seconds);
void c_clear_screen(void);
char c_getch(void);
int termios_echo(bool state);