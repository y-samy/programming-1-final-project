#include <ui.h>
#include <auth/login.h>
#include <management/reservations.h>
#include <management/rooms.h>

int main()
{
    /* Deserialize */
    user_t user = new_user_session();
    room_t *rooms = load_rooms();
    size_t room_count = get_room_count();
    reservation_t *reservations;
    while (1) {
       reserve_room();

    }
    /* Unload serialized data */
    end_user_session();
    /* Deserialize */
    save_and_unload_rooms();
    return 0;
}
