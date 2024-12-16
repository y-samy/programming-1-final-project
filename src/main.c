#include <ui.h>
#include <auth/login.h>


int main()
{
    user_t user;
    while (1) {
        if (root_menu() == ROOT_M_CHOICE_EXIT)
            return 0;
        user = user_session();
        if(login_menu(&user) != LOGIN_M_SUCCES)
            continue;
        int menu_choice = main_menu();
        if (menu_choice == MAIN_M_CHOICE_LOGOUT) {
            logout(&user);
            continue;
        }
    }
    return 0;
}
