#include "login.h"
#include "status.h"
#include <libui/io.h>

#define MENU_STATIC\
 "LOGIN\n"\
 "-----\n\n"


int login_menu(LoginSession *session)
{
    display_menu(MENU_STATIC);
    char username[USERNAME_LEN] = {0};
    char password[PASSWORD_LEN] = {0};
    while (!is_logged_in(session)) {
        bool input_valid = false;
        int input_status;
        do {
            input_status = input(username, "Username: ", 0, USERNAME_LEN, INPUT_USERNAME, true);
            if (input_status == IO_STATUS_UNDO) {
                username[0] = '\0';
                continue;
            }
            if (input_status == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            if (input_status == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            if (!((input_valid = verify_username(session, username)))) {
                printf(CLEAR_LN ERROR_HIGHLIGHT "User " CLR_TEXT_BLACK "%s" CLR_RESET ERROR_HIGHLIGHT " not found!" CLR_RESET
                    CUR_UP "\r", username);
            }
        } while (!input_valid);
        input_valid = false;
        printf(CLEAR_LN);
        do {
            input_status = input(password, "Password: ", 0,PASSWORD_LEN, INPUT_PASSWORD, false);
            if (input_status == IO_STATUS_UNDO) {
                password[0] = '\0';
                continue;
            }
            if (input_status == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            if (input_status == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            if (!((input_valid = verify_password(session, password)))) {
                printf(CLEAR_LN ERROR_HIGHLIGHT "Incorrect password! %d attempts remaining." CLR_RESET CUR_UP CLEAR_LN, get_remaining_attempts(session));
                password[0] = '\0';
            }
        } while (!input_valid && can_attempt(session));
        if (!input_valid)
            return MENU_SIGNAL_EXIT;
    }
    return MENU_SIGNAL_PROCEED;
}