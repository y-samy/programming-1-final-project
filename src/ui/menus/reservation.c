#include <management/reservations.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <libui/io.h>


#define RESERVATION_MENU \
"RESERVATION\n"\
"---------\n\n"

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

    char date[10];

    if (input(reservation.customer.name,  CLEAR_LN "Customer name: ", 100, INPUT_ALPHABETICAL) == IO_STATUS_ESC)
        return;

    if (input(reservation.customer.nationalId,  CLEAR_LN "Customer national ID: : ", 15, INPUT_INT_ANY) == IO_STATUS_ESC)
        return;

    if (input(reservation.customer.email,  CLEAR_LN "Customer email: ", 100, INPUT_EMAIL) == IO_STATUS_ESC)
        return;

    if (input(reservation.customer.phoneNum,  CLEAR_LN "Customer mobile number: ", 15, INPUT_INT_POSITIVE) == IO_STATUS_ESC)
        return;

    if (input(date,  CLEAR_LN "Customer mobile number: ", 15, INPUT_INT_POSITIVE) == IO_STATUS_ESC)
        return;




}


