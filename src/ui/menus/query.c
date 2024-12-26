#include "query.h"
#include <libui/io.h>
#include <stdio.h>
#include <stdlib.h>

#include "status.h"

#define MENU_OPTIONS \
"By Customer Name\n"\
"By Room Number\n"\
"By Room Status\n"

#define MENU_STATIC \
"QUERY MENU\n"\
"----------\n"

int query_menu(HotelSession *session)
{
    display_menu(MENU_STATIC);
    int stage = 1;
    int choice, status;
    while (1) {
        while (stage == 1) {
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
                status = input(customer_name, "Customer name: ", 99,INPUT_ALPHABETICAL,true);
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
                    printf(CUR_DOWN ERROR_HIGHLIGHT "No customer names match " CLR_TEXT_BLACK "%s" CLR_RESET CUR_UP, customer_name);
                    continue;
                }
                while (room != NULL) {
                    printf(CUR_DOWN CLEAR_LN "Customer Name: %s\n", room->reservation.customer.name);
                    fflush(stdout);
                    room = get_room_by_customer_name(NULL, customer_name);
                }
                stage++;
            }
            if (choice == 2) {
                char room_number[11] = {0};
                int room_id = 0;
                status = input(room_number, "Room number: ", 99,INPUT_ALPHABETICAL,true);
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

                }
            }
        }
    }
}
