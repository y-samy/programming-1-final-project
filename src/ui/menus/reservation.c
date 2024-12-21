#include <stdlib.h>
#include <stdio.h>
#include <libui/io.h>
#include <management/rooms.h>
#include <management/reservations.h>


#define MENU_STATIC \
"RESERVATION\n"\
"---------\n\n"

#define CATEGORY_CHOICES \
"Sea View\n" \
"Garden View\n" \
"Lake View\n"


int reserve_room()
{
    reservation_t *reservation = malloc(sizeof(reservation_t));
    display_menu(MENU_STATIC);
    bool input_valid = 0;

    char tmp[10];

    if (input(reservation->customer.name,   "Customer name: ", 100, INPUT_ALPHABETICAL) == IO_STATUS_ESC)
        return 0;

    if (input(reservation->customer.nationalId,   "\nCustomer national ID: ", 15, INPUT_INT_ANY) == IO_STATUS_ESC)
        return 0;

    if (input(reservation->customer.email,   "\nCustomer email: ", 100, INPUT_EMAIL) == IO_STATUS_ESC)
        return 0;

    if (input(reservation->customer.phoneNum,   "\nCustomer mobile number: ", 15, INPUT_INT_POSITIVE) == IO_STATUS_ESC)
        return 0;

    putchar('\n');
    input_date(&reservation->date);

    if (input(tmp,"\nNumber of nights: ", 3, INPUT_INT_POSITIVE) == IO_STATUS_ESC)
        return 0;
    reservation->n_nights = atoi(tmp);
    reservation->confirmed = false;
    reservation->room_p = NULL;
    putchar('\n');
    do {
        printf(CLEAR_LN "Choose room Category:\n");
        room_view_t room_category = choices(CATEGORY_CHOICES)-1;
        room_t *rooms = get_room_list();
        size_t rooms_count = get_room_count();
        size_t i;
        for (i = 0; i < rooms_count; i++) {
            if (get_room_view(rooms + i) == room_category && is_available(rooms + i)) {
                reservation->room_p = rooms + i;
                set_available(rooms+i, false);
                break;
            }
        }
        if (reservation->room_p == NULL)
            printf(CLEAR_LN "Sorry, there is no room with the chosen view available. \033[4A");
    } while (reservation->room_p == NULL);
    add_reservation(reservation);
}