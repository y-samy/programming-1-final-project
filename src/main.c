#include <ui.h>
#include <auth/login.h>
#include <management/reservations.h>
#include <management/rooms.h>

int main()
{
    /* Deserialize */
    user_t user = new_user_session();
    load_rooms();
    load_reservations();
        reserve_room();
    /* Unload serialized data */
    end_user_session();
    save_and_unload_reservations();
    save_and_unload_rooms();
    return 0;
}
