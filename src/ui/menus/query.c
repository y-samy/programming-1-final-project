#include "query.h"
#include <libui/io.h>
#include <unistd.h>
#include <stdio.h>

#define MENU_OPTIONS\
"By Customer Name\n"\
"By Room Number\n"\
"By Room Status\n"

#define MENU_STATIC\
"QUERY MENU\n"\
"----------\n"

int query_menu(HotelSession *session)
{
  display_menu(MENU_STATIC);
  char buffer[100];
  int choice=choices(MENU_OPTIONS);
  if(choice==1)
  {
    input(buffer,"\nCustomer name: ",100,INPUT_ALPHABETICAL,false);
    room_t *room = get_room_by_customer_name(session,buffer);
    while(room != NULL)
    {
        printf("\n%s",room->reservation.customer.name);
        fflush(stdout);
        room = get_room_by_customer_name(NULL,buffer);
    }
    sleep(5);
  }
}