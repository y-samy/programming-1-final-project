#include "check_in.h"

#include <math.h>
#include <stdio.h>
#include <libui/io.h>
#include <stdlib.h>


#define MENU_STATIC \
    "CHECK-IN\n"\
    "--------\n"

int check_in(HotelSession *session)
{
    display_menu(MENU_STATIC);
    char input_buffer[9];
    int id;
    reservation_t *reservation = NULL;
    struct tm today = get_current_date();
    while (reservation == NULL) {
        input(input_buffer, "Reservation ID: ", 9, INPUT_INT_POSITIVE, false);
        id = atoi(input_buffer);
        reservation = get_reservation_by_id(session, id);
        if (reservation == NULL) {
            printf(CUR_DOWN "Reservation ID: %d not found\n" CUR_UP, id);
            continue;
        }
        if (difftime(mktime(&today), mktime(&(reservation->date))) < 0) {
            printf(CUR_DOWN "Cannot reserve yet\n" CUR_UP);
            continue;
        }
        reservation->checked_in = true;
        reservation->nights_count = floor(difftime(mktime(&today), mktime(&reservation->date))) / 86400;
        reservation->date = today;
    }
}