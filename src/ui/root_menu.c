#include "root_menu.h"
#include "status_codes.h"
#include <libui/io.h>
#include <stdlib.h>

#define MENU_ROOT\
"Welcome to the hotel's reservation system.\n"\
"------------------------------------------\n\n"\
"[1] LOGIN\n"\
"[*] EXIT\n\n\n\n\n"\
"Manual\n"\
"------\n"\
"Press [KEY] to choose an option\n"\
"Some menus will allow you to press " PROMPT_CANCEL_KEY_S " to go back one step\n"

void root_menu(void)
{
    char choice[2];
    display_menu(MENU_ROOT);
    if (input(choice, "", 2, ECHO_OFF) != EXIT_SUCCESS)
        break;
    if (choice[0] == '1')

        else if (choice[0] == '*')
            exit(EXIT_SUCCESS);
}