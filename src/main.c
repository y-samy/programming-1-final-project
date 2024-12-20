#include <ui.h>
#include <auth/login.h>


int main()
{
    /* Deserialize */
    user_t user = new_user_session();

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
    }
    /* Unload serialized data */
    end_user_session();
    /* Deserialize */

    return 0;
}
