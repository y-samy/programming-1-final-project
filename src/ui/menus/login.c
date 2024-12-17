#include "login.h"
#include <libui/io.h>

#define MENU_STATIC\
 "LOGIN\n"\
 "-----\n"\
 PROMPT_CANCEL_KEY_S\
 " Go Back\n\n"

int login_menu(user_t *user)
{
    while (!is_logged_in(user)) {
        display_menu(MENU_STATIC);
        char username[USERNAME_LEN];
        char password[PASSWORD_LEN];
        bool input_valid = false;
        int input_attempts = 0;
        do {
            if (input(username,  CLEAR_LN "Username: ", USERNAME_LEN, INPUT_USERNAME) == IO_STATUS_ESC)
                return;
            if (!(input_valid = verify_username(user, username))) {
                printf(
                    CUR_DOWN CLEAR_LN CLR_BG_YLW "User " CLR_TEXT_RED "%s" CLR_RESET CLR_BG_YLW " not found!" CLR_RESET
                    CUR_UP "\r", username);
            }
            input_attempts = 1;
        } while (!input_valid);
        printf(CUR_UP CUR_UP CLEAR_LN PROMPT_CANCEL_KEY_S " Cancel" "\033[3B" CLEAR_LN);
        input_valid = false;
        input_attempts = 0;
        do {
            if (input(password, CLEAR_LN "Password: ", PASSWORD_LEN, INPUT_PASSWORD) != EXIT_SUCCESS)
                break; /* using break; instead of return; to reprompt for password when ESC is pressed */
            if (!(input_valid = verify_password(user, password))) {
                printf(CUR_DOWN CLEAR_LN CLR_BG_YLW "Incorrect password! %d of %d attempts." CLR_RESET CUR_UP "\r", input_attempts + 1, PASSWORD_ATTEMPTS);
            }
            input_attempts++;
        } while (!input_valid && input_attempts < PASSWORD_ATTEMPTS);
    }
    return LOGIN_SUCCES;
}