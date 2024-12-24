#include <stdlib.h>
#include <stdio.h>
#include <libui/io.h>
#include <management.h>

#include "status.h"

#define MENU_STATIC \
"RESERVATION\n"\
"---------\n\n"

#define CATEGORY_CHOICES \
"Sea View\n" \
"Lake View\n" \
"Garden View\n"


int reserve_room(HotelSession *session)
{
    reservation_t reservation = create_reservation();
    display_menu(MENU_STATIC);
    bool input_valid = 0;

    char tmp[10];
    int choice;
    while (1) {
        choice = input(reservation.customer.name, "Customer name: ", 100, INPUT_ALPHABETICAL, false);
        if (choice == IO_STATUS_EXIT)
            return MENU_SIGNAL_EXIT;
        if (choice == IO_STATUS_ESC)
            return MENU_SIGNAL_CANCEL;

        choice = input(reservation.customer.nationalId, "\nCustomer national ID: ", 15, INPUT_INT_ANY, false);
        if (choice == IO_STATUS_EXIT)
            return MENU_SIGNAL_EXIT;
        if (choice == IO_STATUS_ESC)
            continue;

        choice = input(reservation.customer.email, "\nCustomer email: ", 100, INPUT_EMAIL, false);
        if (choice == IO_STATUS_EXIT)
            return MENU_SIGNAL_EXIT;
        if (choice == IO_STATUS_ESC)
            continue;

        choice = input(reservation.customer.phoneNum, "\nCustomer mobile number: ", 15, INPUT_INT_POSITIVE, false);
        if (choice == IO_STATUS_EXIT)
            return MENU_SIGNAL_EXIT;
        if (choice == IO_STATUS_ESC)
            continue;

        putchar('\n');
        struct tm current_date = get_current_date();
        input_date(&current_date, &reservation.date);

        choice = input(tmp, "\nNumber of nights: ", 3, INPUT_INT_POSITIVE, false);
        if (choice == IO_STATUS_EXIT)
            return MENU_SIGNAL_EXIT;
        if (choice == IO_STATUS_ESC)
            continue;
        reservation.nights_count = atoi(tmp);
        reservation.checked_in = false;
        putchar('\n');
        while (1) {
            room_t *available_room = NULL;
            printf(CLEAR_LN "Choose room Category:\n");
            choice = choices(CATEGORY_CHOICES) - 1;
            if (choice == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            if (choice == IO_STATUS_ESC)
                break;
            if ((available_room = get_available_room_by_category(session, choice)) != NULL) {
                int id = add_reservation(session, available_room, reservation);
                clear_screen();
                display_menu(MENU_STATIC);
                printf("Reservation Succeeded\nYour reservation ID: %d\n", id);
                choice = choices("Main Menu\nExit\n");
                if (choice == IO_STATUS_ESC || choice == 1)
                    return MENU_SIGNAL_PROCEED;
                if (choice == IO_STATUS_EXIT || choice == 2)
                    return MENU_SIGNAL_EXIT;
            }
            printf(CLEAR_LN "Sorry, there is no room with the chosen view available. \033[4A");
        }
    }
}
