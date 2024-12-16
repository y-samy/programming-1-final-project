#include "ui.h"
#include <libui/io.h>
#include <auth/login.h>
#include <stdlib.h>
#include <stdio.h>


#define MENU_MAIN \
"MAIN MENU\n"\
"---------\n\n"

#define MENU_MAIN_CHOICES \
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
    display_menu(MENU_MAIN);
    char choice;
    while (1) {
        choice = choices(MENU_MAIN_CHOICES);
        if (choice == IO_STATUS_ESC)
            break;
        switch (choice) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                continue;
            case 10:
            case IO_STATUS_ESC:
                return MAIN_M_CHOICE_LOGOUT;
                return;
            case 11:
                exit(0);
            default:
                continue;
        }
    }
}
