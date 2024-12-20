#include "reservations.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

reservation_t* loadReservation(void)
{
    FILE* f_reservation = fopen("Reservation.txt","r");
    int c;
    int count = 0;
    while ((c= fgetc(f_reservation)) != EOF) {
        if (c == '\n')
            count++;
    }

    reservation_t *reservations = malloc(count * sizeof(reservation_t));

    int i;
    for (i = 0; i <= count; i++)
    {
        /*
        Reservation_ID,
        Room number,
        Room Reservation Status,

        Customer Name,
        Customer National ID,
        no. of nights,

        check-in date,

        customer email,
        mobile number
        */

        char temp[99];

        fscanf(f_reservation,"%d,%d,",
           &reservations[i].reservation_id,
           &reservations[i].room.id
           );

        fscanf(f_reservation, "%19s,", temp);
        reservations[i].status = strcmp(temp, "confirmed") ? 0 : 1;

        fscanf(f_reservation,"%99s,%15s,%d,",
            reservations[i].customer.name,
            reservations[i].customer.nationalId,
            &reservations[i].n_nights);

        fscanf(f_reservation,"%2d-%2d-%4d,",
            &reservations[i].date.tm_mday,
            &reservations[i].date.tm_mon,
            &reservations[i].date.tm_year)
        ;

        fscanf(f_reservation, "%99s, %14s",
           reservations[i].customer.email,
           reservations[i].customer.phoneNum
           );
    }
    fclose(f_reservation);
    return reservations;
}


int ID()
{
    time_t t = time(NULL);
    srand(t);
    return rand() % 10000;
}

