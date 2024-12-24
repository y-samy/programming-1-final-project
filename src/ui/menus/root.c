#include "root.h"
#include <libui/io.h>

#include "status.h"

#define MENU_STATIC \
"Welcome to the hotel's reservation system.\n"\
"------------------------------------------\n\n"

#define MENU_CHOICES \
"Login\n"\
"Exit\n"

int root_menu(void)
{
    int choice;
    while (1) {
        display_menu(MENU_STATIC);
        choice = choices(MENU_CHOICES);
        if (choice == 1)
            return MENU_SIGNAL_PROCEED;
        if (choice == 2 || choice == IO_STATUS_ESC || choice == IO_STATUS_EXIT)
            return MENU_SIGNAL_EXIT;
    }
}
