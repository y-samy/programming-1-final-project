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
    int stage = 1;

    while (1)
    {
        display_menu(MENU_STATIC);
        while (stage == 1){
            printf("Choose reservation date: \n");
            choice = input_date(&current_date, &search_date);

            room = get_room_by_checkin_date(session, search_date);

            if (!room)
            {
                printf(CUR_DOWN CLEAR_LN ERROR_HIGHLIGHT CLR_TEXT_BLACK "Nothing to show here" CLR_RESET CUR_UP CLEAR_LN CUR_UP
                    CLEAR_LN CLEAR_LN CUR_UP);
                continue;
            }
            stage++;
        }

        while (stage == 2){
            while (room != NULL) {
                printf("\n" CLEAR_LN "Customer name: %s", room->reservation.customer.name);
                printf("\nCustomer email: %s", room->reservation.customer.email);
                printf("\nCustomer nationalID: %s", room->reservation.customer.nationalId);
                printf("\nCustomer phone number: %s\n\n", room->reservation.customer.phoneNum);

                fflush(stdout);
                room = get_room_by_checkin_date(NULL, search_date);
            }

            choice = choices("Create another report\nMain menu\nExit\n");
            if (choice == IO_STATUS_UNDO || choice == 1)
                stage = 1;

            if (choice == IO_STATUS_ESC || choice == 2)
                return MENU_SIGNAL_CANCEL;

            if (choice == IO_STATUS_EXIT || choice == 3)
                return MENU_SIGNAL_EXIT;
        }
    }
}