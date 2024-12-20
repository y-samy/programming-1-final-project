#include "reservations.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <libui/io.h>

#define RESERVATION_MENU \
"RESERVATION\n"\
"---------\n\n"

reservation_t* loadReservation(void)
{
    FILE* f_reservation =fopen("Reservation.txt","r");
    int c;
    int count = 0;
    while ((c= fgetc(f_reservation)) != EOF) {
        if (c == '\n')
            count++;
    }

    reservation_t *reservations = malloc(count * sizeof(reservation_t));

    for (int i = 0; i <= count; i++)
    {
           fscanf(f_reservation,"%d,%d,%19s,%d,%99s,%d,%12s,%99s,%d",
               &reservations[i].reservation_id,
               &reservations[i].room.room_id
               );
               reservations[i].status,
               reservations[i].customer.name,
               &reservations[i].customer.nationalId,
               reservations[i].n_nights,
               reservations[i].date,
               reservations[i].customer.email,
               &reservations[i].customer.phoneNum
               );
    }
    fclose(f_reservation);
}





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
    display_menu(RESERVATION_MENU);
}

