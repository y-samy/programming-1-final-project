#include "login.h"
#include "status.h"
#include <libui/io.h>

#define MENU_STATIC\
 "LOGIN\n"\
 "-----\n"\
 PROMPT_CANCEL_KEY_S\
 " Previous Menu\n\n"

#define PASSWORD_ATTEMPTS 3

int login_menu(LoginSession *session)
{
    display_menu(MENU_STATIC);
    char username[USERNAME_LEN] = {0};
    char password[PASSWORD_LEN] = {0};
    while (!is_logged_in(session)) {
        bool input_valid = false;
        int input_status;
        int input_attempts = 0;
        do {
            input_status = input(username,  CLEAR_LN "Username: ", USERNAME_LEN, INPUT_USERNAME, true);
            if (input_status == IO_STATUS_UNDO) {
                username[0] = '\0';
                continue;
            }
            if (input_status == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            if (input_status == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            if (!((input_valid = verify_username(session, username)))) {
                printf(CLEAR_LN CLR_BG_YLW "User " CLR_TEXT_RED "%s" CLR_RESET CLR_BG_YLW " not found!" CLR_RESET
                    CUR_UP "\r", username);
            }
        } while (!input_valid);
        printf(CUR_UP CUR_UP CUR_UP CLEAR_LN PROMPT_UNDO_KEY_S " Cancel" CUR_DOWN CUR_DOWN CUR_DOWN CLEAR_LN);
        input_valid = false;
        input_attempts = 0;
        do {
            input_status = input(password, CLEAR_LN "Password: ", PASSWORD_LEN, INPUT_PASSWORD, false);
            if (input_status == IO_STATUS_UNDO && password[0] != '\0') {
                password[0] = '\0';
                continue;
            }
            if (input_status == IO_STATUS_UNDO) {
                printf(CUR_DOWN CLEAR_LN CUR_UP CLEAR_LN CUR_UP CLEAR_LN CUR_UP CUR_UP CLEAR_LN PROMPT_CANCEL_KEY_S " Main Menu\n\n");
                break; /* using break; instead of return; to reprompt for password when ESC is pressed */
            }
            if (input_status == IO_STATUS_ESC)
                return MENU_SIGNAL_CANCEL;
            if (input_status == IO_STATUS_EXIT)
                return MENU_SIGNAL_EXIT;
            if (!((input_valid = verify_password(session, password)))) {
                printf(CLEAR_LN CLR_BG_YLW "Incorrect password! %d of %d attempts." CLR_RESET CUR_UP "\r", input_attempts + 1, PASSWORD_ATTEMPTS);
            }
            input_attempts++;
        } while (!input_valid && input_attempts < PASSWORD_ATTEMPTS);
    }
    return MENU_SIGNAL_PROCEED;
}