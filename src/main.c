#include "ui.h"
#include "login.h"
#include "platform.h"

int main(int argc, char *argv[])
{
    user_t user = session();
    while(!is_logged_in(&user)) {
        display_menu(MENU_LOGIN, "");
        char username[USERNAME_LEN];
        char password[USERNAME_LEN];
        input(username, "Username: ", USERNAME_LEN, ECHO);
        if (!verify_username(&user, username))
            continue;
        input(password, "Password: ", PASSWORD_LEN, ECHO_OFF);
        verify_password(&user, password);
    }
    display_menu(MENU_MAIN, "");
    c_sleep(5);
    return 0;
}
