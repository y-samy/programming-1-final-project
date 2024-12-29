#include "query.h"
#include <libui/io.h>
#include <stdio.h>
#include <stdlib.h>

#include "../status.h"

#define MENU_OPTIONS \
"By Customer Name\n"\
"By Room Number\n"\
"By Room Status\n"

#define MENU_STATIC \
"QUERY MENU\n"\
"----------\n\n"

int query_menu(HotelSession *session)
{
    int stage = 1;
    int choice, status;
    while (1) {
        while (stage == 1) {
            display_menu(MENU_STATIC);
            status = choice = choices(MENU_OPTIONS);
            if (status == IO_STATUS_UNDO)
                continue;
            if (status == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            if (status == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            stage++;
        }
        while (stage == 2) {
            if (choice == 1) {
                char customer_name[100] = {0};
                status = input(customer_name, "Customer name: ", 0, 99, INPUT_ALPHABETICAL,true);
                if (status == IO_STATUS_UNDO) {
                    printf(CUR_UP);
                    stage--;
                    break;
                }
                if (status == IO_STATUS_EXIT)
                    return MENU_SIGNAL_EXIT;
                if (status == IO_STATUS_ESC)
                    return MENU_SIGNAL_CANCEL;
                room_t *room = get_room_by_customer_name(session, customer_name);
                if (room == NULL) {
                    printf(ERROR_HIGHLIGHT "No customer names match " CLR_TEXT_BLACK "%s" CLR_RESET CUR_UP,
                           customer_name);
                    continue;
                }
                while (room != NULL) {
                    printf(CLEAR_LN CUR_DOWN
                           "Customer Name: %s\nPhone Number: %s\nEmail: %s\nRoom Number: %d\nReservation Date: %s\nNumber of nights: %d\nChecked-in: %s\n\n",
                           room->reservation.customer.name, room->reservation.customer.phoneNum,
                           room->reservation.customer.email, room->id, stringify_date(&room->reservation.date),
                           room->reservation.nights_count, (room->reservation.checked_in) ? "YES" : "NO");
                    fflush(stdout);
                    room = get_room_by_customer_name(NULL, customer_name);
                }
                stage++;
            }
            if (choice == 2) {
                char room_number[11] = {0};
                int room_id = 0;
                status = input(room_number, "Room number: ", 0,99, INPUT_INT_POSITIVE,true);
                if (status == IO_STATUS_UNDO) {
                    printf(CUR_UP);
                    stage--;
                    break;
                }
                if (status == IO_STATUS_EXIT)
                    return MENU_SIGNAL_EXIT;
                if (status == IO_STATUS_ESC)
                    return MENU_SIGNAL_CANCEL;
                room_id = atoi(room_number);
                room_t *room = get_room_by_id(session, room_id);
                if (room == NULL) {
                    printf(
                        CLEAR_LN ERROR_HIGHLIGHT "Room with ID: " CLR_TEXT_BLACK "%d" ERROR_HIGHLIGHT " not found"
                        CLR_RESET CUR_UP, room_id);
                    continue;
                }
                printf(CLEAR_LN CUR_DOWN "Room View: %s\nReserved: %s\n", stringify_view(room), (room->reserved) ? "YES" : "NO");
                if (room->reserved)
                    printf(
                       "Customer Name: %s\nPhone Number: %s\nEmail: %s\nRoom Number: %d\nReservation Date: %s\nNumber of nights: %d\nChecked-in: %s\n\n",
                       room->reservation.customer.name, room->reservation.customer.phoneNum,
                       room->reservation.customer.email, room->id, stringify_date(&room->reservation.date),
                       room->reservation.nights_count, (room->reservation.checked_in) ? "YES" : "NO");
                stage++;
            }
            if (choice == 3) {
                status = choices("View Available Rooms\nView Reserved Rooms\nView Occupied Rooms\n");
                if (status == IO_STATUS_UNDO) {
                    printf(CUR_UP);
                    stage--;
                    break;
                }
                if (status == IO_STATUS_EXIT)
                    return MENU_SIGNAL_EXIT;
                if (status == IO_STATUS_ESC)
                    return MENU_SIGNAL_CANCEL;
                room_t *room = NULL;
                if (status == 1) {
                    room = get_available_rooms(session);
                    while (room != NULL) {
                        printf(CLEAR_LN "%d %-13s %5d\n", get_room_id(room), stringify_view(room), get_price_per_night(room));
                        room = get_available_rooms(NULL);
                    }
                }
                if (status == 2) {
                    room = get_reserved_rooms(session);
                    while (room != NULL) {
                        printf(CLEAR_LN "%d %-13s %5d %s\n", get_room_id(room), stringify_view(room), get_price_per_night(room), stringify_date(&room->reservation.date));
                        room = get_reserved_rooms(NULL);
                    }
                }
                if (status == 3) {
                    room = get_reserved_rooms(session);
                    while (room != NULL) {
                        if (room->reservation.checked_in)
                            printf(CLEAR_LN "%d %-13s %5d %s\n", get_room_id(room), stringify_view(room), get_price_per_night(room), stringify_date(&room->reservation.date));
                        room = get_reserved_rooms(NULL);
                    }
                }
                stage++;
            }
        }
        while (stage == 3) {
            choice = choices("Search Again\nMain Menu\nExit\n");
            if (choice == 1 || choice == IO_STATUS_UNDO)
                stage = 1;
            if (choice == 2 || choice == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            if (choice == 3 || choice == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
        }
    }
}
