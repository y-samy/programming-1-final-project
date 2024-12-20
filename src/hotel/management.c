#include "management.h"
#include <libui/charcodes.h>
#include <libui/io.h>
#include <stdio.h>
#include <string.h>

customer_t* loadReservation(void)
{
    customer_t customerList[100];
   FILE* f=fopen("Reservation.txt","r");
    int i=0;
   while(!feof(f)){
   fscanf(f,"%d,%d,%19s,%d,%99s,%d,%12s,%99s,%d",&customerList[i].reservationId,&customerList[i].roomId,customerList[i].checkinStatus,customerList[i].name,&customerList[i].nationalId,customerList[i].date,customerList[i].email,&customerList[i].phoneNum);
   i++;
   }
   fclose(f);
    return customerList;
} 

int loadRooms(room_t roomList[100])
{
    int i;
    static int roomCount=0;
    if (roomCount) return roomCount;
    FILE* f = fopen("Rooms.txt","r");
    for(i=0; !feof(f) ;i++){
        int scan = fscanf(f,"%d %10s %15s %d",&roomList[i].room_id,roomList[i].availability,roomList[i].view,&roomList[i].price);
        if (scan==4) roomCount++;
    }
    fclose(f);
    return roomCount;
}

void roomAvailability(int option) //option is either 0 for all rooms or //1 for avilable rooms or //-1 for reserved rooms
{
    clear_screen();
    static room_t rooms[100];
    int n = loadRooms(rooms);
    int i,j;
    char av[]="Available",re[]="Reserved";
    if (option==0)//print all rooms and their availability (sorted)
    {
        for (i=0; i<2 ;i++)
        {
            if (!i)
            {
                printf(CLR_BG_GREEN "\nAvailable Rooms:\n" CLR_RESET);
                for (j=0;j<n;j++)
                {
                    if(!strcmp(rooms[j].availability,av))
                    {
                        printf("%d %15s %d\n",rooms[j].room_id,rooms[j].view,rooms[j].price);
                    }
                }
            }    
            else
            { 
                printf(CLR_BG_RED "Reserved Rooms:\n" CLR_RESET);
                for (j=0;j<n;j++)
                {
                    if(!strcmp(rooms[j].availability,re))
                    {
                        printf("%d %15s %d\n",rooms[j].room_id,rooms[j].view,rooms[j].price);
                    }
                }
            }                
        }
    }
    else if (option == 1)
    {
        printf(CLR_TEXT_GREEN " Available Rooms:\n" CLR_RESET);
        for (j=0;j<n;j++)
        {   
            if(!strcmp(rooms[j].availability,av))
            {
                printf("%d %15s %d\n",rooms[j].room_id,rooms[j].view,rooms[j].price);
            }
        }
    }
    else
    {
        printf(CLR_TEXT_RED " Reserved Rooms:\n" CLR_RESET);
        for (j=0;j<n;j++)
        {
            if(!strcmp(rooms[j].availability,re))
            {
                printf("%d %15s %d\n",rooms[j].room_id,rooms[j].view,rooms[j].price);
            }
        }
    }
    //printf("Back\n");
}