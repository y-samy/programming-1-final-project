#include "check_out.h"
#include "status.h"
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
    char input_buffer[9] = {0};
    int id;
    int price;
    reservation_t *reservation = NULL, old_reservation = create_reservation();
    struct tm today = get_current_date();
    int status;
    room_t *room = NULL;
    int nights_count = 0;
    while (1) {
        while (reservation == NULL) {
            status = input(input_buffer, "Reservation ID: ", 0, 9, INPUT_INT_POSITIVE, false);
            if (status == IO_STATUS_UNDO)
                continue;
            if (status == IO_STATUS_ESC)
                return MENU_SIGNAL_PROCEED;
            if (status == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            id = atoi(input_buffer);
            reservation = get_reservation_by_id(session, id);
            if (reservation == NULL) {
                printf(
                    CLEAR_LN ERROR_HIGHLIGHT "Reservation ID:" CLR_TEXT_BLACK "%d" ERROR_HIGHLIGHT " not found"
                    CLR_RESET CUR_UP, id);
                continue;
            }
            if (!reservation->checked_in) {
                printf(CLEAR_LN ERROR_HIGHLIGHT "Cannot check-out before checking in" CLR_RESET CUR_UP);
                reservation = NULL;
                continue;
            }
            old_reservation = *reservation;
            room = get_room_by_reservation(session, reservation);
            nights_count = (int) ceil(difftime(mktime(&today), mktime(&reservation->date))) / 86400;
            price = nights_count ? room->price * nights_count : room->price;
            printf("Price: %d\n", price);
            cancel_reservation(session, reservation->reservation_id);
        }
        status = choices("Undo Check-out\nCheck-out Another Customer\nMain Menu\nExit\n");
        if (status == IO_STATUS_UNDO || status == 1) {
            room->reserved = true;
            room->reservation = old_reservation;
            reservation = NULL;
            room = NULL;
            display_menu(MENU_STATIC);
        }
        if (status == 2)
            reservation = NULL;
        if (status == IO_STATUS_ESC || status == 3)
            return MENU_SIGNAL_PROCEED;
        if (status == IO_STATUS_EXIT || status == 4)
            return MENU_SIGNAL_EXIT;
    }
}
