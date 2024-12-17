#include "reservations.h"
#include <stdio.h>

customer_t* loadReservation(void)
{
    customer_t customerList[100];
   FILE* f=fopen("reservation.txt","r");
   while(!feof(f)){
    int i=0;
   fscanf("%d,%d,%d,%d,%99c,%d,%12c,%99c,%d",&customerList[i].reservationId,&customerList[i].roomId,&customerList[i].checkinStatus,customerList[i].name,&customerList[i].nationalId,customerList[i].date,customerList[i].email,&customerList[i].phoneNum);
   i++;
   }
} 