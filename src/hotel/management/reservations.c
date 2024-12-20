#include "reservations.h"
#include <stdio.h>

customer_t* loadReservation(void)
{
    customer_t customerList[100];
    FILE* f=fopen("Reservation.txt","r");
    while(!feof(f)){
        int i=0;
        fscanf(f,"%d,%d,%19s,%d,%99s,%d,%12s,%99s,%d",&customerList[i].reservationId,&customerList[i].roomId,customerList[i].checkinStatus,customerList[i].name,&customerList[i].nationalId,customerList[i].date,customerList[i].email,&customerList[i].phoneNum);
        i++;
    }
    fclose(f);
}