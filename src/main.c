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
        if (root_menu() == ROOT_M_CHOICE_EXIT)
            return 0;
        if(login_menu(&user) != LOGIN_M_SUCCES)
            continue;
        int menu_choice = main_menu();
        if (menu_choice == MAIN_M_CHOICE_LOGOUT) {
            logout(&user);
            continue;
        }
        if (menu_choice == 5) {
            availability_menu(rooms, room_count);
        }
    }
    /* Unload serialized data */
    end_user_session();
    /* Deserialize */
    save_and_unload_rooms();
    return 0;
}
