#include "management.h"
#include <stdio.h>

customer_t* loadReservation(void)
{
    customer_t customerList[100];
   FILE* f=fopen("Reservation.txt","r");
   while(!feof(f)){
    int i=0;
   fscanf("%d,%d,%19c,%d,%99c,%d,%12c,%99c,%d",&customerList[i].reservationId,&customerList[i].roomId,customerList[i].checkinStatus,customerList[i].name,&customerList[i].nationalId,customerList[i].date,customerList[i].email,&customerList[i].phoneNum);
   i++;
   }
} 

room_t* loadRooms(void)
{
    room_t roomList[100];
    FILE* f=fopen("Rooms.txt","r");
    while(!feof(f)){
        int i=0;
        fscanf("%d,%10c,%15c,%d",roomList[i].room_id,roomList[i].avaliablity,roomList[i].view,roomList[i].price);
        i++;
    }
}
