#include "check_in.h"

#include <stdio.h>
#include <libui/io.h>

#include "management/reservations.h"


#define MENU_STATIC \
    "CHECK-IN\n"\
    "--------\n"

int check_in()
{
    display_menu(MENU_STATIC);
    char input_buffer[9];
    int id;
    reservation_t *reservations = get_reservations_list();
    size_t reservation_count = get_reservations_count();
    id = atoi(input_buffer);
    size_t i;
    reservation_t *reservation = NULL;
    struct tm today = get_current_date();
    input(input_buffer, "Reservation ID: ", 9, INPUT_INT_POSITIVE);
    while (reservation == NULL) {
        for (i = 0; i < reservation_count; i++) {
            if (reservations[i].reservation_id == id) {
                reservation = reservations + i;
                break;
            }
        }
        if (reservation == NULL) {
            printf("Reservation ID: %d not found\n", id);
        }
        if (difftime(mktime(&today), mktime(&(reservation->date))) < 0)
            printf("Cannot reserve yet\n");
    }
}