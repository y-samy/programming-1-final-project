#include "availability.h"
#include <libui/io.h>
#include <stdio.h>

#define MENU_STATIC \
"CHECK ROOM AVAILABILITY\n"\
"-----------------------\n\n"

int availability_menu(room_t *room_list, size_t count)
{
    display_menu(MENU_STATIC);
    size_t i;
    printf(CLR_BG_GREEN "Available Rooms:\n" CLR_RESET);
    for (i = 0; i < count; i++) {
        if (is_available(room_list + i)) {
            printf("%d %15s %d\n", get_room_id(room_list + i), get_view_s(room_list+i), get_price(room_list+i));
        }
    }
    printf(CLR_BG_RED "Reserved Rooms:\n" CLR_RESET);
    for (i = 0; i < count; i++) {
        if (!is_available(&room_list[i])) {
            printf("%d %15s %d\n", get_room_id(room_list + i), get_view_s(room_list+i), get_price(room_list+i));
        }
    }
    choices("Back\nExit\n");
}