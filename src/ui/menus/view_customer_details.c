#include "view_customer_details.h"

#include <stdlib.h>
#include <libui/io.h>
#include <stdio.h>
#include <management.h>

#include "status.h"

#define MENU_STATIC \
    "SEARCH CUSTOMER DETAILS\n"\
    "-----------------------\n\n"

#define MENU_CHOICES \
    "Using Room Number\n"\
    "Using Reservation ID\n"

int view_customer_details(HotelSession *session)
{
    int choice;
    char buffer[11] = {0};
    int stage = 1;
    int id_type = 1;
    while (true) {
        while (stage == 1) {
            display_menu(MENU_STATIC);
            choice = choices(MENU_CHOICES);
            if (choice == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            if (choice == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            if (choice == IO_STATUS_UNDO)
                continue;
            id_type = choice;
            stage++;
        }
        while (stage == 2) {
            if (id_type == 1) {
                choice = input(buffer, "Room Number: ", 10, INPUT_INT_POSITIVE, true);
                if (choice == IO_STATUS_UNDO && buffer[0] == '\0') {
                    stage--;
                    break;
                }
                if (choice == IO_STATUS_UNDO) {
                    buffer[0] = '\0';
                    continue;
                }
                if (choice == IO_STATUS_ESC)
                    return MENU_SIGNAL_CANCEL;
                if (choice == IO_STATUS_EXIT)
                    return MENU_SIGNAL_EXIT;
                int id = atoi(buffer);
                room_t *room = NULL;
                if ((room = get_room_by_id(session, id)) == NULL) {
                    printf(CLEAR_LN ERROR_HIGHLIGHT "No room found with ID " CLR_TEXT_BLACK "%d" CLR_RESET CUR_UP, id);
                    continue;
                }
                if (!room->reserved) {
                    printf(CLEAR_LN ERROR_HIGHLIGHT "Room " CLR_TEXT_BLACK "%d" ERROR_HIGHLIGHT " has no reservations." CLR_RESET CUR_UP, id);
                    continue;
                }
                customer_t customer = room->reservation.customer;
                printf(CLEAR_LN "Customer details:\n%s %s %s\n", customer.name, customer.email, customer.phoneNum);
                choice = choices("Main Menu\nExit\n");
                if (choice == IO_STATUS_ESC || choice == 1)
                    return MENU_SIGNAL_CANCEL;
                if (choice == IO_STATUS_EXIT || choice == 2)
                    return MENU_SIGNAL_EXIT;
                if (choice == IO_STATUS_UNDO) {
                    display_menu(MENU_STATIC);
                    continue;
                }
            }
            if (id_type == 2) {
                choice = input(buffer, "Reservation ID: ", 10, INPUT_INT_POSITIVE, true);
                if (choice == IO_STATUS_UNDO && buffer[0] == '\0') {
                    stage--;
                    break;
                }
                if (choice == IO_STATUS_UNDO) {
                    buffer[0] = '\0';
                    continue;
                }
                if (choice == IO_STATUS_ESC)
                    return MENU_SIGNAL_CANCEL;
                if (choice == IO_STATUS_EXIT)
                    return MENU_SIGNAL_EXIT;
                int id = atoi(buffer);
                reservation_t *reservation = NULL;
                if ((reservation = get_reservation_by_id(session, id)) == NULL) {
                    printf(CLEAR_LN ERROR_HIGHLIGHT "No reservation found with ID " CLR_TEXT_BLACK "%d" CLR_RESET CUR_UP, id);
                    continue;
                }
                customer_t customer = reservation->customer;
                printf(CLEAR_LN "Customer details:\n%s %s %s\n", customer.name, customer.email, customer.phoneNum);
                choice = choices("Main Menu\nExit\n");
                if (choice == IO_STATUS_ESC || choice == 1)
                    return MENU_SIGNAL_CANCEL;
                if (choice == IO_STATUS_EXIT || choice == 2)
                    return MENU_SIGNAL_EXIT;
                if (choice == IO_STATUS_UNDO) {
                    display_menu(MENU_STATIC);
                    continue;
                }
            }
        }
    }
}