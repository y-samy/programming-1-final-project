#include "availability.h"
#include <libui/io.h>
#include <management/rooms.h>

#define MENU_STATIC \
"LOGIN\n"\
"-----\n"\

int check_room_availability(room_t room_list*)
{
    choices("Back\nExit\n");
}