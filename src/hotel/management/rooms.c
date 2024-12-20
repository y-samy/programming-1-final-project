#include "rooms.h"
#include <stdio.h>
#include <string.h>

size_t room_count(bool reset) /* private */
{
    static size_t count = 0;
    if (reset) {
        /* reset */
        count = 0;
        return count;
    }
    if (count)
        return count;
    char c, prev_c = 0;
    FILE *rooms_file = fopen(ROOM_FILE_NAME, "r");
    while(1){
        c = fgetc(rooms_file);
        if (c == EOF) {
            if (prev_c != '\n')
                count++;
            break;
        }
        if (c == '\n')
            count++;
        prev_c = c;
    }
    fclose(rooms_file);
    return count;
}

room_t *room_list(size_t room_count, bool reset) /* private */
{
    static room_t *rooms_list = NULL;
    if (reset) {
        free(rooms_list);
        return NULL;
    }
    if (rooms_list)
        return rooms_list;
    rooms_list = malloc(room_count * sizeof(room_t));
    FILE *rooms_file = fopen(ROOM_FILE_NAME, "r");
    size_t i;
    char avail_buffer[10];
    char room_category_buffer[11];
    for (i = 0; i < room_count; i++) {
        fscanf(rooms_file, "%d %9s %10s %d", &rooms_list[i].id, avail_buffer, room_category_buffer,
               &rooms_list[i].price);
        if (!strcmp(avail_buffer, "Available"))
            rooms_list[i].is_available = true;
        else
            rooms_list[i].is_available = false;
        if (!strcmp(room_category_buffer, "SeaView"))
            rooms_list[i].view_category = SeaView;
        if (!strcmp(room_category_buffer, "LakeView"))
            rooms_list[i].view_category = LakeView;
        if (!strcmp(room_category_buffer, "GardenView"))
            rooms_list[i].view_category = GardenView;
    }
    fclose(rooms_file);
    return rooms_list;
}

size_t get_room_count(void)
{
    return room_count(false);
}


room_t *load_rooms(void)
{
    return room_list(room_count(false), false);
}

void save_and_unload_rooms(void)
{
    FILE *rooms_file = fopen(ROOM_FILE_NAME, "w");
    size_t count = room_count(false);
    room_t *rooms_list = room_list(count, false);
    size_t i;
    for (i = 0; i < count; i++) {
        fprintf(rooms_file, "%d %s %s %d", get_room_id(rooms_list + i), get_availability_s(rooms_list + i),
                get_view_s(rooms_list + i), get_price(rooms_list + i));
    }
    fclose(rooms_file);
}

bool is_available(room_t *room)
{
    return room->is_available;
}

char *get_availability_s(room_t *room)
{
    return room->is_available ? "Available" : "Unavailable";
}

int get_price(room_t *room)
{
    return room->price;
}

room_view_t get_view(room_t *room)
{
    return room->view_category;
}

char *get_view_s(room_t *room)
{
    switch (room->view_category) {
        case SeaView:
            return "SeaView";
            break;
        case LakeView:
            return "LakeView";
            break;
        case GardenView:
            return "GardenView";
            break;
    }
}

int get_room_id(room_t *room)
{
    return room->id;
}

void set_available(room_t *room, bool available)
{
    room->is_available = available;
}
