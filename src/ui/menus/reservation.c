#include <management/reservations.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <libui/io.h>
#include "management/rooms.h"



#define RESERVATION_MENU \
"RESERVATION\n"\
"---------\n\n"

#define CHECKIN_MENU \
    "CHEKCIN\n" \
    "-------



#define CATEGORY_MENU \
"Sea View\n" \
"Garden View\n" \
"Lake View\n"


int reserve_room()
{
    /*customer name
     *national ID
     *email
     *mobile number
     *checkin date
     * # nights
     * category (sea, lake garden)
     * reservation ID
     */
    reservation_t reservation;
    display_menu(RESERVATION_MENU);
    bool input_valid = 0;

    char tmp[10];

    if (input(reservation.customer.name,   "\nCustomer name: ", 100, INPUT_ALPHABETICAL) == IO_STATUS_ESC)
        return;

    if (input(reservation.customer.nationalId,   "\nCustomer national ID: ", 15, INPUT_INT_ANY) == IO_STATUS_ESC)
        return;

    if (input(reservation.customer.email,   "\nCustomer email: ", 100, INPUT_EMAIL) == IO_STATUS_ESC)
        return;

    if (input(reservation.customer.phoneNum,   "\nCustomer mobile number: ", 15, INPUT_INT_POSITIVE) == IO_STATUS_ESC)
        return;

    // if (input(date,  CLEAR_LN "Customer mobile number: ", 15, INPUT_INT_POSITIVE) == IO_STATUS_ESC)
    //     return;

    if (input(tmp,   "\nNumber of nights: ", 3, INPUT_INT_POSITIVE) == IO_STATUS_ESC)
        return;
    reservation.n_nights = atoi(tmp);

    printf("Choose room Category: \n");
    reservation.room.view_category = choices(CATEGORY_MENU);
}


