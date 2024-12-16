/*
* Pragma once to prevent the includes
 * from happening multiple times
 */
#pragma once
#include <stdbool.h>

int get_key(void);
void clear_screen(void);
int termios_echo(bool state);