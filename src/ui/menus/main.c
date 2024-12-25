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
    int choice;
    display_menu(MENU_STATIC);
    while (1) {
        choice = choices(MENU_CHOICES);
        if (choice == IO_STATUS_UNDO)
            continue;
        if (choice == 10 || choice == IO_STATUS_ESC)
            return MENU_SIGNAL_CANCEL;
        if (choice == 11 || choice == IO_STATUS_EXIT)
            return MENU_SIGNAL_EXIT;
        return choice;
    }
}

