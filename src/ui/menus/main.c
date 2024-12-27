#include "ui.h"
#include <libui/io.h>

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


int main_menu(HotelSession *session)
{
    int choice;
    display_menu(MENU_STATIC);
    if (session->customers_overstaying)
        printf(ERROR_HIGHLIGHT "Some customers are currently overstaying\n\n");
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

