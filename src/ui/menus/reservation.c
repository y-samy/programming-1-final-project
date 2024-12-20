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
    "CHECKC-IN\n" \
    "-------\n\n"

#define CHECKOUT_MENU \
    "CHECK-OUT\n" \
    "---------\n\n"

#define CANCEL_RESERVATION \
    "CACNEL RESERVATION\n" \
    "------------------\n\n"

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
        return 0;

    if (input(reservation.customer.nationalId,   "\nCustomer national ID: ", 15, INPUT_INT_ANY) == IO_STATUS_ESC)
        return 0;

    if (input(reservation.customer.email,   "\nCustomer email: ", 100, INPUT_EMAIL) == IO_STATUS_ESC)
        return 0;

    if (input(reservation.customer.phoneNum,   "\nCustomer mobile number: ", 15, INPUT_INT_POSITIVE) == IO_STATUS_ESC)
        return 0;

    putchar('\n');
    input_date(&reservation.date);

    if (input(tmp,   "\nNumber of nights: ", 3, INPUT_INT_POSITIVE) == IO_STATUS_ESC)
        return 0;
    reservation.n_nights = atoi(tmp);

    printf("\nChoose room Category: \n");
    reservation.room.view_category = choices(CATEGORY_MENU);
}


int cancel_reservation()
{
    display_menu(CANCEL_RESERVATION);
    char ID[5];
    input(ID, "Enter ID", 5, INPUT_INT_POSITIVE);

}

int checkin()
{
    //change room satus to confirmed
}

int checkout()
{

}