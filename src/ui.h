/*
 * Pragma once to prevent the includes
 * from happening multiple times
 */
#pragma once

#define MENU_LOGIN\
 "Welcome to the hotel's reservation system.\n"\
 "Please login.\n"

#define MENU_MAIN\
 "Reserve a Room\n"\
 "Check-in\n"\
 "Cancel Reservation\n"\
 "Check-out\n"\
 "Check Room Availability\n"\
 "View Customer Details\n"\
 "Edit Reservation Details\n"\
 "Query (search)\n"\
 "Reservation Report\n"\
 "Exit\n"\

#define ECHO true
#define ECHO_OFF false

void display_menu(char *menu, char *options);

#include <stdbool.h>
#include <stdlib.h>
int *input(char *buffer, const char *prompt, size_t input_size, bool echo);