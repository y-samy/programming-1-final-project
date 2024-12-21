#include "cancel_reservation.h"
#include <libui/io.h>
#include <management/reservations.h>

#define MENU_STATIC \
    "CANCEL RESERVATION\n"\
    "------------------\n\n"

int cancel_reservation_menu()
{
    display_menu(MENU_STATIC);
    int id;
    int id_buff[13];
    input(id_buff, "Reservation ID: ", 10, INPUT_INT_POSITIVE);
    id = atoi(id_buff);
    end_reservation(get_reservation_by_id(id));
}