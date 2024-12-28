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
    reservation_t new_reservation, old_reservation;
    room_t *new_room, *old_room;
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
                choice = input(id_buffer, "Room Number: ", 0, 10, INPUT_INT_POSITIVE, true);
                if (choice == IO_STATUS_UNDO) {
                    stage--;
                    break;
                }
                if (choice == IO_STATUS_ESC)
                    return MENU_SIGNAL_CANCEL;
                if (choice == IO_STATUS_EXIT)
                    return MENU_SIGNAL_EXIT;
                int id = atoi(id_buffer);
                old_room = get_room_by_id(session, id);
                if (old_room == NULL) {
                    printf(
                        CLEAR_LN ERROR_HIGHLIGHT "Room with ID: " CLR_TEXT_BLACK "%d" ERROR_HIGHLIGHT " not found"
                        CLR_RESET CUR_UP, id);
                    continue;
                }
                if (!old_room->reserved) {
                    printf(
                           CLEAR_LN ERROR_HIGHLIGHT "Room with ID: " CLR_TEXT_BLACK "%d" ERROR_HIGHLIGHT " is not reserved"
                           CLR_RESET CUR_UP, id);
                    continue;
                }
                if (old_room->reservation.checked_in) {
                    printf(
                        CLEAR_LN ERROR_HIGHLIGHT "Cannot edit reservation details after check-in" CLR_RESET CUR_UP);
                    continue;
                }
                new_reservation = old_reservation = old_room->reservation;
                stage++;
            }
            if (id_type == 2) {
                choice = input(id_buffer, "Reservation ID: ", 0, 10, INPUT_INT_POSITIVE, true);
                if (choice == IO_STATUS_UNDO) {
                    stage--;
                    break;
                }
                if (choice == IO_STATUS_ESC)
                    return MENU_SIGNAL_CANCEL;
                if (choice == IO_STATUS_EXIT)
                    return MENU_SIGNAL_EXIT;
                int id = atoi(id_buffer);
                reservation_t *reservation = get_reservation_by_id(session, id);
                if (reservation == NULL) {
                    printf(
                        CLEAR_LN ERROR_HIGHLIGHT "Reservation with ID: " CLR_TEXT_BLACK "%d" ERROR_HIGHLIGHT
                        " not found" CLR_RESET CUR_UP, id);
                    continue;
                }
                old_room = get_room_by_reservation(session, reservation);
                if (old_room->reservation.checked_in) {
                    printf(CLEAR_LN ERROR_HIGHLIGHT "Cannot edit reservation details after check-in" CLR_RESET CUR_UP);
                    continue;
                }
                new_reservation = old_reservation = old_room->reservation;
                stage++;
            }
        }
        while (stage == 3) {
            choice = input(new_reservation.customer.name, "Customer name: ", 0, 100, INPUT_ALPHABETICAL, true);
            if (choice == IO_STATUS_UNDO) {
                printf(CUR_UP);
                stage--;
                break;
            }
            if (choice == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            if (choice == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            stage++;
        }
        while (stage == 4) {
            choice = input(new_reservation.customer.email, "Customer email: ", 0, 100, INPUT_EMAIL, true);
            if (choice == IO_STATUS_UNDO) {
                printf(CUR_UP);
                stage--;
                break;
            }
            if (choice == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            if (choice == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            stage++;
        }
        while (stage == 5) {
            choice = input(new_reservation.customer.phoneNum, "Customer mobile number: ", 11, 12, INPUT_INT_POSITIVE, true);
            if (choice == IO_STATUS_UNDO) {
                printf(CUR_UP);
                stage--;
                break;
            }
            if (choice == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            if (choice == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            stage++;
        }
        while (stage == 6) {
            printf("Choose new date: \n");
            choice = input_date(&new_reservation.date, &current_date, NULL);
            if (choice == IO_STATUS_UNDO) {
                printf(CUR_UP CLEAR_LN CUR_UP);
                stage--;
                break;
            }
            if (choice == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            if (choice == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            stage++;
        }
        while (stage == 7) {
            sprintf(nights_count_buffer, "%d", new_reservation.nights_count);
            choice = input(nights_count_buffer, "Number of nights: ", 0, 3, INPUT_INT_POSITIVE, true);
            if (choice == IO_STATUS_UNDO) {
                printf(CUR_UP CUR_UP);
                stage--;
                break;
            }
            if (choice == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            if (choice == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            stage++;
            new_reservation.nights_count = atoi(nights_count_buffer);
            new_reservation.checked_in = false;
        }
        while (stage == 8) {
            printf(CLEAR_LN "Choose room Category:\n");
            choice = choices(CATEGORY_CHOICES);
            if (choice == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            if (choice == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            if (choice == IO_STATUS_UNDO) {
                printf("\033[3B" CLEAR_LN "\033[3A" CLEAR_LN CUR_UP CLEAR_LN CUR_UP);
                stage--;
                break;
            }
            choice--;
            if ((new_room = get_available_room_by_category(session, choice)) == NULL) {
                printf("\033[3B" CLEAR_LN "Sorry, there is no room with the chosen view available. \033[4A");
                continue;
            }
            stage++;
        }
        while (stage == 9) {
            cancel_reservation(session, old_room->reservation.reservation_id);
            new_room->reservation = new_reservation;
            new_room->reserved = true;
            printf("\n\nReservation Succeeded\n" CLEAR_LN);
            choice = choices("Undo Edits\nEdit Another Reservation\nMain Menu\nExit\n");
            if (choice == IO_STATUS_UNDO || choice == 1) {
                stage--;
                cancel_reservation(session, new_room->reservation.reservation_id);
                old_room->reservation = old_reservation;
                old_room->reserved = true;
                int i;
                for (i = 0; i < 4; ++i)
                    printf(CLEAR_LN CUR_UP);
            }
            if (choice == 2) {
                stage = 1;
                new_reservation = create_reservation();
                nights_count_buffer[0] = '\0';
                id_buffer[0] = '\0';
                current_date = get_current_date();
                new_reservation.date = current_date;
                new_room = NULL;
            }
            if (choice == IO_STATUS_ESC || choice == 3)
                return MENU_SIGNAL_PROCEED;
            if (choice == IO_STATUS_EXIT || choice == 4)
                return MENU_SIGNAL_EXIT;
        }
    }
}
