#include "reservation.h"
#include "management.h"
#include <stdlib.h>
#include <time.h>
#include <libui/io.h>


#define RESERVATION_MENU \
"RESERVATION\n"\
"---------\n\n"


int ID()
{
    int i = 0;
    {
        time_t t = time(NULL);
        srand(t);
        return rand() % 10000;
    }
}

void reserveRoom()
{
    loadReservation();
    display_menu(RESERVATION_MENU);
}

