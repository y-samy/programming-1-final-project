#pragma once
#include <stdlib.h>
#include <stdbool.h>
#define ROOM_FILE_NAME "Room.txt"

typedef enum {SeaView, LakeView, GardenView} room_view_t;

typedef struct 
{
    int id;
    bool is_available;
    room_view_t view_category;
    int price;
} room_t;

room_t *load_rooms(void);
void save_and_unload_rooms(void);
void set_available(room_t *room, bool available);
bool is_available(room_t *room);
int get_price(room_t *room);
room_view_t get_view(room_t *room);
size_t get_room_count(void);
int get_room_id(room_t *room);
char *get_view_s(room_t *room);
char *get_availability_s(room_t *room);
room_view_t get_view_from_string(char *view_s);