#include "rooms.h"
#include <stdio.h>
#include <string.h>

static size_t file_entry_count()
{
    size_t count = 0;
    char c, prev_c = 0;
    FILE *rooms_file = fopen(ROOM_FILE_NAME, "r");
    while (1) {
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

static size_t count_holder(size_t new_count, bool unset)
{
    /*
     * Usage:
     * set to 0: count_holder(0, true);
     * set to n > 0: count_holder(n, false);
     * get value: count_holder(0, false);
     */
    static size_t count = 0;
    if (unset)
        count = 0;
    else if (new_count)
        count = new_count;
    return count;
}

static room_t *list_holder(room_t *new_list, bool unset)
{
    /*
     * Usage:
     * set to NULL: list_holder(NULL, true);
     * set to room_t ptr: list_holder(ptr, false);
     * get ptr: list_holder(NULL, false);
     */
    static room_t *room_list = NULL;
    if (unset)
        room_list = NULL;
    if (new_list != NULL)
        room_list = new_list;
    return room_list;
}

static void load_from_file()
{
    size_t room_count = count_holder(0, false);
    room_t *rooms_list = malloc(room_count * sizeof(room_t));
    FILE *rooms_file = fopen(ROOM_FILE_NAME, "r");
    size_t i;
    char avail_buffer[14];
    char room_category_buffer[11];
    for (i = 0; i < room_count; i++) {
        fscanf(rooms_file, "%d %s %s %d", &rooms_list[i].id, avail_buffer, room_category_buffer,
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
    list_holder(rooms_list, false);
}

size_t get_room_count(void)
{
    return count_holder(0, false);
}

room_t *get_room_list(void)
{
    return list_holder(NULL, false);
}

void load_rooms(void)
{
    count_holder(file_entry_count(), false);
    load_from_file();
}

void save_and_unload_rooms(void)
{
    FILE *rooms_file = fopen(ROOM_FILE_NAME, "w");
    size_t count = get_room_count();
    room_t *rooms_list = get_room_list();
    size_t i;
    for (i = 0; i < count; i++) {
        fprintf(rooms_file, "%d %s %s %d\n", get_room_id(rooms_list + i), get_availability_s(rooms_list + i),
                get_view_s(rooms_list + i), get_price(rooms_list + i));
    }
    fclose(rooms_file);
    free(rooms_list);
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

room_view_t get_room_view(room_t *room)
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

room_view_t get_view_from_string(char *view_s)
{
    if (!strcmp(view_s, "SeaView")) return SeaView;
    if (!strcmp(view_s, "LakeView")) return LakeView;
    if (!strcmp(view_s, "GardenView")) return GardenView;
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

void set_available(room_t *room, bool available)
{
    room->is_available = available;
}
