#include <stdlib.h>
#include <stdio.h>
#include <libui/io.h>
#include "reservation_report.h"
#include "status.h"

#define MENU_STATIC \
    "RESERVATION REPORT \n" \
    "------------------\n\n"




int reservation_report(HotelSession *session)
{
    int choice;
    struct tm current_date = get_current_date();
    struct tm search_date = current_date;
    room_t *room = NULL;

    while (1)
    {
        display_menu(MENU_STATIC);
        printf("Choose reservation date: \n");
        choice = input_date(&current_date, &search_date);

        room = get_room_by_checkin_date(session, search_date);

        if (!room)
            printf("\nNothing to show here");

        while (room != NULL) {
            printf("\nCustomer name: %s\n", room->reservation.customer.name);
            printf("\nCustomer email: %s\n", room->reservation.customer.email);
            printf("\nCustomer nationalID: %s\n", room->reservation.customer.nationalId);
            printf("\nCustomer phone number: %s\n\n", room->reservation.customer.phoneNum);

            fflush(stdout);
            room = get_room_by_checkin_date(NULL, search_date);
        }

        if (choice == IO_STATUS_UNDO) {
            search_date = current_date;
            printf(CUR_UP);
            continue;
        }

        choice = choices("Create another report\nMain menu\nExit");
        if (choice == IO_STATUS_EXIT)
            return MENU_SIGNAL_EXIT;
        if (choice == IO_STATUS_ESC)
            return MENU_SIGNAL_CANCEL;
    }
}