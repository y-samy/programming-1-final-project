#include "ui.h"
#include "libui/io.h"
#include "login.h"
#include <stdlib.h>
#include <stdio.h>


#define MENU_ROOT\
 "Welcome to the hotel's reservation system.\n"\
 "------------------------------------------\n\n"\
 "[1] LOGIN\n"\
 "[*] EXIT\n\n\n\n\n\n"\
 "Manual\n"\
 "------\n"\
 "Press [KEY] to choose an option\n"\
 "Press [Ctrl] + [C] at any time to exit the program\n"\
 "Some menus will allow you to press " PROMPT_CANCEL_KEY_S " to go back one step\n"


#define MENU_LOGIN\
 "LOGIN\n"\
 "-----\n"\
 PROMPT_CANCEL_KEY_S\
 " Go Back\n\n"

#define MENU_MAIN\
 "MAIN MENU\n"\
 "---------\n\n"\
 "[1] Reserve a Room\n"\
 "[2] Check-in\n"\
 "[3] Cancel Reservation\n"\
 "[4] Check-out\n"\
 "[5] Check Room Availability\n"\
 "[6] View Customer Details\n"\
 "[7] Edit Reservation Details\n"\
 "[8] Query (search)\n"\
 "[9] Reservation Report\n"\
 "[ESC] Sign Out\n"\
 "[*] Exit\n"

void display_menu(char *menu)
{
    clear_screen();
    printf("%s", menu);
}

void main_menu(user_t user)
{
    display_menu(MENU_MAIN);
    char choice[2];
    while (1) {
        if (input(choice, "", 2, ECHO_OFF) != EXIT_SUCCESS)
            break;
        switch (choice[0]) {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                continue;
            case ESC_KEY:
                logout(&user);
                return;
            case '*':
                exit(0);
            default:
                continue;
        }
    }
}

void root_menu(void)
{
    char choice[2];
    while (1) {
        display_menu(MENU_ROOT);
        if (input(choice, "", 2, ECHO_OFF) != EXIT_SUCCESS)
            break;
        if (choice[0] == '1')
            login_menu();
        else if (choice[0] == '*')
            exit(EXIT_SUCCESS);
    }
}

void login_menu(void)
{
    user_t user = session();
    while (!is_logged_in(&user)) {
        display_menu(MENU_LOGIN);
        char username[USERNAME_LEN];
        char password[PASSWORD_LEN];
        bool input_valid = false;
        int input_attempts = 0;
        char prompt[50];
        do {
            sprintf(prompt, "%sUsername: ", CLEAR_LN);
            if (input(username, prompt, USERNAME_LEN, ECHO) == PROMPT_ERR_CANCEL)
                return;
            if (!(input_valid = verify_username(&user, username))) {
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
            if (!input_attempts)
                sprintf(prompt, "%sPassword: ", CLEAR_LN);
            else
                sprintf(prompt, "%sPassword (%d attempts): ", CLEAR_LN, input_attempts);
            if (input(password, prompt, PASSWORD_LEN, ECHO_MASK) != EXIT_SUCCESS)
                break; /* using break; instead of return; to reprompt for password when ESC is pressed */
            if (!(input_valid = verify_password(&user, password)) && !input_attempts) {
                printf(CUR_DOWN CLEAR_LN CLR_BG_YLW "Incorrect password!" CLR_RESET CUR_UP "\r");
            }
            input_attempts++;
        } while (!input_valid && input_attempts < PASSWORD_ATTEMPTS);
    }
    main_menu(user);
}
