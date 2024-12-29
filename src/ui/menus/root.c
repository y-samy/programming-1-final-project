#include "root.h"

#include <stdio.h>
#include <libui/io.h>
#include <libui/charcodes.h>

#include "../status.h"

#define MENU_STATIC \
"Welcome to the hotel's reservation system.\n"\
"------------------------------------------\n\n"\
CSI "3B" /* 3 Cursor down */ \
"User Manual\n"\
"-----------\n"\
"Keyboard Shortcuts:\n"\
PROMPT_UNDO_KEY_S " to undo last action (cannot traverse menus)\n"\
PROMPT_CANCEL_KEY_S " to return to previous menu or main menu\n"\
"[Ctrl-C] to save the data and exit the program\n"\
"[Enter] to submit\n"\
"Use arrow keys to navigate multiple-choice menus\n"\
CSI "11A" /* 11 Cursor up */

#define MENU_CHOICES \
"Login\n"\
"Exit\n"

int root_menu(void)
{
    int choice;
    display_menu(MENU_STATIC);
    while (1) {
        choice = choices(MENU_CHOICES);
        if (choice == 1)
            return MENU_SIGNAL_PROCEED;
        if (choice == IO_STATUS_UNDO)
            continue;
        if (choice == 2 || choice == IO_STATUS_ESC || choice == IO_STATUS_EXIT)
            return MENU_SIGNAL_EXIT;
    }
}
