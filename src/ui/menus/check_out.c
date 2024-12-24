#include "check_out.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <libui/io.h>

#define MENU_STATIC \
    "CHECK-IN\n"\
    "--------\n"

int check_out_menu(HotelSession *session)
{
    display_menu(MENU_STATIC);
    char input_buffer[9];
    int id;
    int price;
    reservation_t *reservation = NULL;
    struct tm today = get_current_date();
    while (reservation == NULL) {
        input(input_buffer, "Reservation ID: ", 9, INPUT_INT_POSITIVE, false);
        id = atoi(input_buffer);
        reservation = get_reservation_by_id(session, id);
        room_t *room = get_room_by_reservation(session, reservation);
        if (reservation == NULL) {
            printf(CUR_DOWN "Reservation ID: %d not found\n" CUR_UP, id);
            continue;
        }
        if (!reservation->checked_in) {
            printf(CUR_DOWN "Cannot check-out yet\n" CUR_UP);
            reservation = NULL;
            continue;
        }
        reservation->nights_count = floor(difftime(mktime(&today), mktime(&reservation->date))) / 86400;
        price = reservation->nights_count? room->price * reservation->nights_count : room->price;
        cancel_reservation(session, reservation->reservation_id);
    }
    printf("Price: %d", price);
    choices("Main Menu\nExit\n");
}