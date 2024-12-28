#include "check_in.h"
#include "status.h"

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
    char input_buffer[9] = {0};
    int id;
    int status;
    reservation_t *reservation = NULL;
    struct tm today = get_current_date();
    struct tm old_date;
    int old_nights_count;
    while (1) {
        while (reservation == NULL) {
            status = input(input_buffer, "Reservation ID: ", 9, INPUT_INT_POSITIVE, true);
            if (status == IO_STATUS_UNDO)
                continue;
            if (status == IO_STATUS_ESC)
                return MENU_SIGNAL_PROCEED;
            if (status == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            id = atoi(input_buffer);
            reservation = get_reservation_by_id(session, id);
            if (reservation == NULL) {
                printf(CLEAR_LN ERROR_HIGHLIGHT "Reservation ID: " CLR_TEXT_BLACK "%d" ERROR_HIGHLIGHT " not found" CLR_RESET CUR_UP, id);
                continue;
            }
            if (difftime(mktime(&today), mktime(&(reservation->date))) < 0) {
                printf(CLEAR_LN ERROR_HIGHLIGHT "Cannot check-in yet, come back another day" CLR_RESET CUR_UP);
                reservation = NULL;
                continue;
            }
            if (reservation->checked_in) {
                printf(CLEAR_LN ERROR_HIGHLIGHT "Already checked-in on reservation with ID: " CLR_TEXT_BLACK "%d" CLR_RESET CUR_UP, id);
                reservation = NULL;
                continue;
            }
            old_date = reservation->date;
            old_nights_count = reservation->nights_count;
            reservation->checked_in = true;
            reservation->nights_count = (int) ceil(difftime(mktime(&today), mktime(&reservation->date))) / 86400;
            reservation->date = today;
        }
        printf(CLEAR_LN CUR_DOWN);
        status = choices("Undo Check-in\nMain Menu\nExit\n");
        if (status == IO_STATUS_UNDO || status == 1) {
            reservation->checked_in = false;
            reservation->date = old_date;
            reservation->nights_count = old_nights_count;
            reservation = NULL;
            display_menu(MENU_STATIC);
        }
        if (status == IO_STATUS_ESC || status == 2)
            return MENU_SIGNAL_PROCEED;
        if (status == IO_STATUS_EXIT || status == 3)
            return MENU_SIGNAL_EXIT;
    }
}