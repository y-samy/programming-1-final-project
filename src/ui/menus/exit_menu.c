#include "exit_menu.h"
#include <stdlib.h>
#include <libui/io.h>
#include <status.h>

#define MENU_STATIC \
    "EXIT\n"\
    "----\n\n"

#define MENU_CHOICES \
    "Save and exit\n" \
    "Discard all session data and exit\n" \
    "Return to Main Menu\n"

static void save(LoginSession *login_session, HotelSession *hotel_session)
{
    /* Unload user objects */
    terminate_login_session(login_session);
    /* Serialize and unload reservation, rooms and customer objects */
    terminate_management_session(hotel_session);
}

static void discard(LoginSession *login_session, HotelSession *hotel_session)
{
    terminate_login_session(login_session);
    discard_management_session(hotel_session);
}

int exit_menu(LoginSession *login_session, HotelSession *hotel_session)
{
    while (1) {
        display_menu(MENU_STATIC);
        int choice = choices(MENU_CHOICES);
        switch (choice) {
            case 1:
                save(login_session, hotel_session);
                exit(0);
            case 2:
            case IO_STATUS_EXIT:
                discard(login_session, hotel_session);
                exit(0);
            case 3:
            case IO_STATUS_ESC:
                return MENU_SIGNAL_CANCEL;
            case IO_STATUS_UNDO:
                continue;
        }
    }
}
