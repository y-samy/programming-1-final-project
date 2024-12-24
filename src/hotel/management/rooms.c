#include "rooms.h"
#include <stdio.h>
#include <string.h>




bool get_availability(room_t *room)
{
    return room->is_available;
}





int get_room_id(room_t *room)
{
    return room->id;
}

room_t *get_room_by_id(int id)
{
    size_t room_count = count_holder(0, false);
    room_t *rooms_list = list_holder(NULL, false);
    size_t i;
    for (i = 0; i < room_count; i++) {
        if (rooms_list[i].id == id)
            return rooms_list + i;
    }
    return NULL;
}