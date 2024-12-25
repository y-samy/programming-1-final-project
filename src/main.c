#include <stdlib.h>

#include <ui.h>
#include <login.h>
#include <management.h>

#include "menus/check_out.h"
#include "menus/edit_reservation.h"

void exit_routine(LoginSession *login_session, HotelSession *hotel_session);

int main()
{
    LoginSession *login_session = NULL;
    HotelSession *hotel_session = NULL;
    init_login_session(&login_session);
    init_management_session(&hotel_session);
    int response;
    while (1) {
        /*
         * If not logged in:
         * Choose: Login/ Exit
         * If cancelled @ login, choose again
         */
        if (!is_logged_in(login_session)) {
            response = root_menu();
            if (response == MENU_SIGNAL_EXIT)
                exit_routine(login_session, hotel_session);

            response = login_menu(login_session);
            if (response == MENU_SIGNAL_EXIT)
                exit_routine(login_session, hotel_session);
            if (response == MENU_SIGNAL_CANCEL)
                continue;
        }

        response = main_menu();
        if (response == MENU_SIGNAL_EXIT)
            exit_routine(login_session, hotel_session);
        if (response == MENU_SIGNAL_CANCEL) {
            logout(login_session);
            continue;
        }

        switch (response) {
            case 1:
                response = reserve_room(hotel_session);
                if (response == MENU_SIGNAL_EXIT)
                    exit_routine(login_session, hotel_session);
                break;


            case 2:
                response = check_in(hotel_session);
                if (response == MENU_SIGNAL_EXIT)
                    exit_routine(login_session, hotel_session);
                break;


            case 3:
                response = cancel_reservation_menu(hotel_session);
                if (response == MENU_SIGNAL_EXIT)
                    exit_routine(login_session, hotel_session);
                break;


            case 4:
                response = check_out_menu(hotel_session);
                if (response == MENU_SIGNAL_EXIT)
                    exit_routine(login_session, hotel_session);
                break;


            case 5:
                response = availability_menu(hotel_session);
                if (response == MENU_SIGNAL_EXIT)
                    exit_routine(login_session, hotel_session);
                break;


            case 6:
                response = view_customer_details(hotel_session);
                if (response == MENU_SIGNAL_EXIT)
                    exit_routine(login_session, hotel_session);
                break;


            case 7:
                response = edit_reservation_menu(hotel_session);
                if (response == MENU_SIGNAL_EXIT)
                    exit_routine(login_session, hotel_session);
                break;

            
            case 8:
                response = query_menu(hotel_session);
                if (response == MENU_SIGNAL_EXIT)
                    exit_routine(login_session, hotel_session);
                break;

            case 9:
                response = reservation_report(hotel_session);
                if (response == MENU_SIGNAL_EXIT)
                    exit_routine(login_session, hotel_session);
                break;
        }
    }
}


void exit_routine(LoginSession *login_session, HotelSession *hotel_session)
{
    /* Unload user objects */
    terminate_login_session(login_session);
    /* Serialize and unload reservation, rooms and customer objects */
    terminate_management_session(hotel_session);
    exit(0);
}
