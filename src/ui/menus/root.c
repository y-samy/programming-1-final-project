#include "root.h"
#include <unistd.h>
#include <libui/io.h>

#define MENU_STATIC \
"Welcome to the hotel's reservation system.\n"\
"------------------------------------------\n\n"

#define MENU_CHOICES \
"Login\n"\
"Exit\n"

int root_menu(void)
{
    char choice;
    while (1) {
        display_menu(MENU_STATIC);
        choice = choices(MENU_CHOICES);
        if (choice == 1)
            return ROOT_M_CHOICE_LOGIN;
        if (choice == 2 || choice == IO_STATUS_ESC)
            return ROOT_M_CHOICE_EXIT;
    }
}
