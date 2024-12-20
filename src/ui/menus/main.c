#include "ui.h"
#include <libui/io.h>
#include <stdlib.h>

#define MENU_STATIC \
"MAIN MENU\n"\
"---------\n\n"

#define MENU_CHOICES \
"Reserve a Room\n"\
"Check-in\n"\
"Cancel Reservation\n"\
"Check-out\n"\
"Check Room Availability\n"\
"View Customer Details\n"\
"Edit Reservation Details\n"\
"Query (search)\n"\
"Reservation Report\n"\
"Sign Out\n"\
"Exit\n"


int main_menu(void)
{
    char choice;
    while (1) {
        display_menu(MENU_STATIC);
        choice = choices(MENU_CHOICES);
        if (choice == IO_STATUS_ESC)
            MAIN_M_CHOICE_LOGOUT;
        if (choice == 11)
            exit(0);
        return choice;
    }
}

