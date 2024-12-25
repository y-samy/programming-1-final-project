#include "edit_reservation.h"
#include <libui/io.h>
#include "status.h"
#include <stdio.h>
#include <stdlib.h>

#define MENU_STATIC \
"EDIT RESERVATION\n"\
"----------------\n\n"

#define MENU_CHOICES \
"Using Room Number\n"\
"Using Reservation ID\n"

#define CATEGORY_CHOICES \
"Sea View\n" \
"Lake View\n" \
"Garden View\n"

int edit_reservation_menu(HotelSession *session)
{
    reservation_t new_reservation;
    int old_room_id;
    int choice;
    char id_buffer[11] = {0};
    char nights_count_buffer[11] = {0};
    int stage = 1;
    int id_type = 1;
    struct tm current_date = get_current_date();
    while (1) {
        while (stage == 1) {
            display_menu(MENU_STATIC);
            choice = choices(MENU_CHOICES);
            if (choice == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            if (choice == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            if (choice == IO_STATUS_UNDO)
                continue;
            stage++;
            id_type = choice;
        }
        while (stage == 2) {
            if (id_type == 1) {
                choice = input(id_buffer, "\nRoom Number: ", 10, INPUT_INT_POSITIVE, true);
                if (choice == IO_STATUS_UNDO && id_buffer[0] == '\0') {
                    stage--;
                    break;
                }
                if (choice == IO_STATUS_UNDO) {
                    id_buffer[0] = '\0';
                    continue;
                }
                if (choice == IO_STATUS_ESC)
                    return MENU_SIGNAL_CANCEL;
                if (choice == IO_STATUS_EXIT)
                    return MENU_SIGNAL_EXIT;
                int id = atoi(id_buffer);
                room_t *room = get_room_by_id(session, id);
                if (room->reserved) {
                    new_reservation = room->reservation;
                    old_room_id = room->id;
                }
            }
            if (id_type == 2) {
                choice = input(id_buffer, "\nReservation ID: ", 10, INPUT_INT_POSITIVE, true);
                if (choice == IO_STATUS_UNDO && id_buffer[0] == '\0') {
                    stage--;
                    break;
                }
                if (choice == IO_STATUS_UNDO) {
                    id_buffer[0] = '\0';
                    continue;
                }
                if (choice == IO_STATUS_ESC)
                    return MENU_SIGNAL_CANCEL;
                if (choice == IO_STATUS_EXIT)
                    return MENU_SIGNAL_EXIT;
                int id = atoi(id_buffer);
                room_t *old_room = get_room_by_reservation(session, get_reservation_by_id(session, id));
                old_room_id = old_room->id;
                new_reservation = old_room->reservation;
            }
        }
        choice = input(new_reservation.customer.name, "\nCustomer name: ", 100, INPUT_ALPHABETICAL, true);
        if (choice == IO_STATUS_EXIT)
            return MENU_SIGNAL_EXIT;
        if (choice == IO_STATUS_ESC)
            return MENU_SIGNAL_CANCEL;

        choice = input(new_reservation.customer.email, "\nCustomer email: ", 100, INPUT_EMAIL, true);
        if (choice == IO_STATUS_EXIT)
            return MENU_SIGNAL_EXIT;
        if (choice == IO_STATUS_ESC)
            continue;

        choice = input(new_reservation.customer.phoneNum, "\nCustomer mobile number: ", 15, INPUT_INT_POSITIVE, true);
        if (choice == IO_STATUS_EXIT)
            return MENU_SIGNAL_EXIT;
        if (choice == IO_STATUS_ESC)
            continue;

        putchar('\n');
        choice = input_date(&new_reservation.date, &current_date, NULL);
        sprintf(nights_count_buffer, "%d", new_reservation.nights_count);
        choice = input(nights_count_buffer, "\nNumber of nights: ", 3, INPUT_INT_POSITIVE, true);
        if (choice == IO_STATUS_EXIT)
            return MENU_SIGNAL_EXIT;
        if (choice == IO_STATUS_ESC)
            continue;
        new_reservation.nights_count = atoi(nights_count_buffer);
        new_reservation.checked_in = false;
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
                edit_reservation(session, available_room, new_reservation, old_room_id);
                display_menu(MENU_STATIC);
                printf("Reservation Succeeded\n");
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
