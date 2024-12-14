#pragma once

#include <stdlib.h>

#define CLEAR_LN "\33[2K\r"

#define ECHO 1
#define ECHO_OFF 0
#define ECHO_MASK -1


int *input(char *buffer, char *prompt_s, size_t input_size, int echo);
void clear_screen(void);