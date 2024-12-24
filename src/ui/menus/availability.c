#include "availability.h"
#include <libui/io.h>
#include <stdio.h>

#include "status.h"

#define MENU_STATIC \
"CHECK ROOM AVAILABILITY\n"\
"-----------------------\n\n"

int availability_menu(HotelSession *session)
{
    display_menu(MENU_STATIC);
    printf(CLR_BG_GREEN "Available Rooms:\n" CLR_RESET);
    room_t *room = NULL;
    room = get_available_rooms(session);
    while (room != NULL) {
        printf("%d %15s %d\n", get_room_id(room), stringify_view(room), get_price_per_night(room));
        room = get_available_rooms(NULL);
    }

    printf(CLR_BG_RED "Reserved Rooms:\n" CLR_RESET);
    room = get_reserved_rooms(session);
    while (room != NULL) {
        printf("%d %15s %d\n", get_room_id(room), stringify_view(room), get_price_per_night(room));
        room = get_reserved_rooms(NULL);
    }

    if (choices("Back\nExit\n") == IO_STATUS_EXIT)
        return MENU_SIGNAL_EXIT;

    return MENU_SIGNAL_PROCEED;
}