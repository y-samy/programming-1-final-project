#include "availability.h"
#include <libui/io.h>
#include <stdio.h>

#include "status.h"

#define MENU_STATIC \
"CHECK ROOM AVAILABILITY\n"\
"-----------------------\n\n"

#define COL_SEP "  |  "
#define HEADER_SEP "--|--"

int availability_menu(HotelSession *session)
{
    display_menu(MENU_STATIC);
    printf(CLR_BG_GREEN "\tAvailable Rooms\n\n" CLR_RESET);
    room_t *room = NULL;
    room = get_available_rooms(session);
    printf(TABLE_HIGHLIGHT "%-4s" CLR_RESET COL_SEP "%-13s" COL_SEP TABLE_HIGHLIGHT "PRICE\n" CLR_RESET, "ID", "VIEW");
    printf(TABLE_HIGHLIGHT "----" CLR_RESET HEADER_SEP "-------------" HEADER_SEP TABLE_HIGHLIGHT "-----\n" CLR_RESET);
    while (room != NULL) {
        printf(TABLE_HIGHLIGHT "%d" CLR_RESET COL_SEP "%-13s" COL_SEP TABLE_HIGHLIGHT "%5d" CLR_RESET "\n", get_room_id(room), stringify_view(room), get_price_per_night(room));
        room = get_available_rooms(NULL);
    }

    printf(CLR_BG_RED "\n\tReserved Rooms\n\n" CLR_RESET);
    printf(TABLE_HIGHLIGHT "%-4s" CLR_RESET COL_SEP "%-13s" COL_SEP TABLE_HIGHLIGHT "PRICE\n" CLR_RESET, "ID", "VIEW");
    printf(TABLE_HIGHLIGHT "----" CLR_RESET HEADER_SEP "-------------" HEADER_SEP TABLE_HIGHLIGHT "-----\n" CLR_RESET);
    room = get_reserved_rooms(session);
    while (room != NULL) {
        printf(TABLE_HIGHLIGHT "%d" CLR_RESET COL_SEP "%-13s" COL_SEP TABLE_HIGHLIGHT "%5d" CLR_RESET "\n", get_room_id(room), stringify_view(room), get_price_per_night(room));
        room = get_reserved_rooms(NULL);
    }
    putchar('\n');
    while (1) {
        int choice = choices("Back\nExit\n");
        if (choice == IO_STATUS_UNDO)
            continue;
        if (choice == 1 || choice == IO_STATUS_ESC)
            return MENU_SIGNAL_PROCEED;
        if (choice == 2 || choice == IO_STATUS_EXIT)
            return MENU_SIGNAL_EXIT;
    }
}