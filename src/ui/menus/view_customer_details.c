#include "view_customer_details.h"

#include <stdlib.h>
#include <libui/io.h>
#include <stdio.h>
#include <management.h>

#include "status.h"

#define MENU_STATIC \
    "SEARCH CUSTOMER DETAILS\n"\
    "-----------------------\n"

#define MENU_CHOICES \
    "Using Room Number\n"\
    "Using Reservation ID\n"

int view_customer_details(HotelSession *session)
{
    display_menu(MENU_STATIC);
    int choice;
    char buffer[11];
    while (true) {
        choice = choices(MENU_CHOICES);
        if (choice == IO_STATUS_EXIT)
            return MENU_SIGNAL_EXIT;
        if (choice == IO_STATUS_ESC)
            return MENU_SIGNAL_CANCEL;
        if (choice == 1) {
            choice = input(buffer, "Room Number: ", 10, INPUT_INT_POSITIVE, false);
            int id = atoi(buffer);
            room_t *room = get_room_by_id(session, id);
            customer_t customer = room->reservation.customer;
            if (room->reserved)
                printf("Customer details:\n%s %s %s\n", customer.name, customer.email, customer.phoneNum);
        }
        if (choice == 2) {
            choice = input(buffer, "Reservation ID: ", 10, INPUT_INT_POSITIVE, false);
            int id = atoi(buffer);
            reservation_t *reservation = get_reservation_by_id(session, id);
            customer_t customer = reservation->customer;
            printf("Customer details:\n%s %s %s\n", customer.name, customer.email, customer.phoneNum);

        }
    }
}