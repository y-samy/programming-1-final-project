#include <stdlib.h>
#include <stdio.h>
#include <libui/io.h>
#include <management.h>

#include "../status.h"

#define MENU_STATIC \
"RESERVATION\n"\
"-----------\n\n"

#define CATEGORY_CHOICES \
"Sea View\n" \
"Lake View\n" \
"Garden View\n"


int reserve_room(HotelSession *session)
{
    int stage = 1;
    int choice;
    reservation_t reservation = create_reservation();
    char nights_count_buffer[10] = {0};
    struct tm current_date = get_current_date();
    reservation.date = current_date;
    room_t *available_room = NULL;
    while (1) {
        while (stage == 1) {
            display_menu(MENU_STATIC);
            choice = input(reservation.customer.name, "Customer name: ", 0, 100, INPUT_ALPHABETICAL, true);
            if (choice == IO_STATUS_UNDO) {
                reservation.customer.name[0] = '\0';
                continue;
            }
            if (choice == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            if (choice == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            stage++;
        }
        while (stage == 2) {
            choice = input(reservation.customer.nationalId, "Customer national ID: ", 0, 15, INPUT_INT_POSITIVE, true);
            if (choice == IO_STATUS_UNDO) {
                printf(CUR_UP);
                stage--;
                break;
            }
            if (choice == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            if (choice == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            stage++;
        }
        while (stage == 3) {
            choice = input(reservation.customer.email, "Customer email: ", 0, 100, INPUT_EMAIL, true);
            if (choice == IO_STATUS_UNDO) {
                printf(CUR_UP);
                stage--;
                break;
            }
            if (choice == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            if (choice == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            stage++;
        }
        while (stage == 4) {
            choice = input(reservation.customer.phoneNum, "Customer mobile number: ", 11, 12, INPUT_INT_POSITIVE, true);
            if (choice == IO_STATUS_UNDO) {
                printf(CUR_UP);
                stage--;
                break;
            }
            if (choice == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            if (choice == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            stage++;
        }
        while (stage == 5) {
            printf("Choose reservation date: \n");
            choice = input_date(&reservation.date, &current_date, NULL);
            if (choice == IO_STATUS_UNDO) {
                printf(CUR_UP CLEAR_LN CUR_UP);
                stage--;
                break;
            }
            if (choice == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            if (choice == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            stage++;
        }
        while (stage == 6) {
            choice = input(nights_count_buffer, "Number of nights: ", 1, 3, INPUT_INT_POSITIVE, true);
            if (choice == IO_STATUS_UNDO) {
                printf(CUR_UP CUR_UP);
                stage--;
                break;
            }
            if (choice == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            if (choice == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            stage++;
            reservation.nights_count = atoi(nights_count_buffer);
            reservation.checked_in = false;
        }
        while (stage == 7) {
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
            if ((available_room = get_available_room_by_category(session, choice)) == NULL) {
                printf("\033[3B" CLEAR_LN "Sorry, there is no room with the chosen view available. \033[4A");
                continue;
            }
            stage++;
        }
        while (stage == 8) {
            int id = add_reservation(session, available_room, reservation);
            printf("\n\nReservation Succeeded\n" CLEAR_LN "Your reservation ID: %d\n\n", id);
            choice = choices("Reserve Again\nMain Menu\nExit\n");
            if (choice == IO_STATUS_UNDO) {
                stage--;
                cancel_reservation(session, id);
                int i;
                for (i = 0; i < 6; ++i)
                    printf(CUR_UP CLEAR_LN);
            }
            if (choice == 1) {
                stage = 1;
                reservation = create_reservation();
                nights_count_buffer[0] = '\0';
                current_date = get_current_date();
                reservation.date = current_date;
                available_room = NULL;
            }
            if (choice == IO_STATUS_ESC || choice == 2)
                return MENU_SIGNAL_PROCEED;
            if (choice == IO_STATUS_EXIT || choice == 3)
                return MENU_SIGNAL_EXIT;
        }
    }
}
