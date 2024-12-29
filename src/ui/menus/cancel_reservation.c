#include "cancel_reservation.h"

#include <stdlib.h>
#include <libui/io.h>
#include <management.h>
#include <stdio.h>

#include "../status.h"

#define MENU_STATIC \
    "CANCEL RESERVATION\n"\
    "------------------\n\n"

int cancel_reservation_menu(HotelSession *session)
{
    int id;
    int id_buff[11] = {0};
    int status;
    int stage = 1;
    int id_type = 0;
    while (1) {
        while (stage == 1) {
            display_menu(MENU_STATIC);
            status = choices("By room number\nBy reservation ID\n");
            if (status == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            if (status == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            if (status == IO_STATUS_UNDO)
                continue;
            stage++;
            id_type = status;
        }
        while (stage == 2) {
            if (id_type == 1) {
                room_t *room = NULL;
                status = input(id_buff, "Room ID: ", 0, 10, INPUT_INT_POSITIVE, true);
                if (status == IO_STATUS_UNDO) {
                    stage--;
                    break;
                }
                if (status == IO_STATUS_ESC)
                    return MENU_SIGNAL_CANCEL;
                if (status == IO_STATUS_EXIT)
                    return MENU_SIGNAL_EXIT;
                id = atoi(id_buff);
                if ((room = get_room_by_id(session, id)) == NULL) {
                    printf(CLEAR_LN ERROR_HIGHLIGHT "No room found with ID " CLR_TEXT_BLACK "%d" CLR_RESET CUR_UP, id);
                    continue;
                }
                if (!room->reserved) {
                    printf(CLEAR_LN ERROR_HIGHLIGHT "Room " CLR_TEXT_BLACK "%d" ERROR_HIGHLIGHT " has no reservations." CLR_RESET CUR_UP, id);
                    continue;
                }
                if (room->reservation.checked_in) {
                    printf(CLEAR_LN ERROR_HIGHLIGHT "Cannot cancel after check-in." CLR_RESET CUR_UP);
                    continue;
                }
                printf(CLEAR_LN TABLE_HIGHLIGHT "Are you sure you want to cancel the reservation? This action is irreversible." CLR_RESET "\n\n");
                status = choices("Confirm\nUndo\nMain Menu\nExit\n");
                if (status == IO_STATUS_ESC || status == 3)
                    return MENU_SIGNAL_CANCEL;
                if (status == IO_STATUS_EXIT || status == 4)
                    return MENU_SIGNAL_EXIT;
                if (status == IO_STATUS_UNDO || status == 2) {
                    stage--;
                    break;
                }
                cancel_reservation(session,room->reservation.reservation_id);
                printf(CLEAR_LN "\nReservation %d has successfully been cancelled\n", id);
                return MENU_SIGNAL_CANCEL;
            }
            if (id_type == 2) {
                reservation_t *reservation = NULL;
                status = input(id_buff, "Reservation ID: ", 0, 10, INPUT_INT_POSITIVE, true);
                if (status == IO_STATUS_UNDO) {
                    stage--;
                    break;
                }
                if (status == IO_STATUS_ESC)
                    return MENU_SIGNAL_CANCEL;
                if (status == IO_STATUS_EXIT)
                    return MENU_SIGNAL_EXIT;
                id = atoi(id_buff);
                if ((reservation = get_reservation_by_id(session, id)) == NULL) {
                    printf(CLEAR_LN ERROR_HIGHLIGHT "No reservation found with ID " CLR_TEXT_BLACK "%d" CLR_RESET CUR_UP, id);
                    continue;
                }
                if (reservation->checked_in) {
                    printf(CLEAR_LN ERROR_HIGHLIGHT "Cannot cancel after check-in." CLR_RESET CUR_UP);
                    continue;
                }
                printf(CLEAR_LN TABLE_HIGHLIGHT "Are you sure you want to cancel the reservation? This action is irreversible." CLR_RESET "\n\n");
                status = choices("Confirm\nUndo\nMain Menu\nExit\n");
                if (status == IO_STATUS_ESC || status == 3)
                    return MENU_SIGNAL_CANCEL;
                if (status == IO_STATUS_EXIT || status == 4)
                    return MENU_SIGNAL_EXIT;
                if (status == IO_STATUS_UNDO || status == 2) {
                    stage--;
                    break;
                }
                cancel_reservation(session,id);
                printf(CLEAR_LN "\nReservation %d has successfully been cancelled\n", id);
                return MENU_SIGNAL_PROCEED;
            }
        }
    }
}