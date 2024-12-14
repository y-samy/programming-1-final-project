#include "ui.h"

#include "libui.h"
#include "login.h"
#include <stdio.h>

#include "platform.h"

#define MENU_LOGIN\
 "Welcome to the hotel's reservation system.\n"\
 "------------------------------------------\n"\
 "LOGIN\n\n"

#define MENU_MAIN\
 "Reserve a Room\n"\
 "Check-in\n"\
 "Cancel Reservation\n"\
 "Check-out\n"\
 "Check Room Availability\n"\
 "View Customer Details\n"\
 "Edit Reservation Details\n"\
 "Query (search)\n"\
 "Reservation Report\n"\
 "Exit\n"\

void display_menu(char *menu)
{
    clear_screen();
    printf("%s", menu);
}

void ui_wait(int seconds)
{
    c_sleep(seconds);
}

void login_menu(void)
{
    user_t user = session();
    while(!is_logged_in(&user)) {
        display_menu(MENU_LOGIN);
        char username[USERNAME_LEN];
        char password[PASSWORD_LEN];
        bool input_valid = false;
        int input_attempts = 0;
        char prompt[20];
        do {
            sprintf(prompt, "%sUsername: ", CLEAR_LN);
            input(username, prompt, USERNAME_LEN, ECHO);
            if (!(input_valid = verify_username(&user, username)) && !input_attempts) {
                printf("%sUsername not found!\n", CLEAR_LN);
            }
            input_attempts = 1;
        } while (!input_valid);
        clear_screen();
        display_menu(MENU_LOGIN);
        printf("Username: %s\n", username);

        input_valid = false;
        input_attempts = 0;
        do {
            if (!input_attempts)
                sprintf(prompt, "%sPassword: ", CLEAR_LN);
            else
                sprintf(prompt, "%sPassword (%d attempts): ", CLEAR_LN, input_attempts);
            input(password, prompt, PASSWORD_LEN, ECHO_MASK);
            if (!(input_valid = verify_password(&user, password)) && !input_attempts) {
                printf("%sIncorrect password!\n", CLEAR_LN);
            }
            input_attempts++;
        } while (!input_valid && input_attempts < PASSWORD_ATTEMPTS);
    }
}