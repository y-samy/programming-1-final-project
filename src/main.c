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
        response = root_menu();
        if (response == MENU_SIGNAL_EXIT)
            exit_routine(login_session, hotel_session);

        response = login_menu(login_session);
        if (response == MENU_SIGNAL_EXIT)
            exit_routine(login_session, hotel_session);
        if (response == MENU_SIGNAL_CANCEL)
            continue;


        response = main_menu();
        if (response == MENU_SIGNAL_EXIT)
            exit_routine(login_session, hotel_session);
        if (response == MENU_SIGNAL_CANCEL) {
            logout(login_session);
            continue;
        }
        if (response == 1)
            reserve_room(hotel_session);
        if (response == 2)
            check_in(hotel_session);
        if (response == 3)
            cancel_reservation_menu(hotel_session);
        if (response == 4)
            check_out_menu(hotel_session);
        if (response == 5)
            availability_menu(hotel_session);
        if (response == 6)
            view_customer_details(hotel_session);
        if (response == 7)
            edit_reservation_menu(hotel_session);
        if (response == 8)
            query_menu(hotel_session); 
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