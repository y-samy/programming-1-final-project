#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct login{
    char username[100];
    char password[100];
}users[100];

int main()
{
    int i=0,j=0;
    struct login current;
    FILE *userf=fopen("users.txt","r+");
    if (!userf)
    {
        printf("Error opening users file!");
        exit(1);
    }
    else
    while (!feof(userf))
    {
        fscanf(userf,"%99s %99s",users[i].username,users[i].password);
        i++;
    }
    printf("Enter login data:\n");

    printf(">Username: ");
    scanf("%99s",current.username);

    printf(">Password: ");
    scanf("%99s",current.password);

    int valid = 0;
    for (j = 0; j < i; j++) {
        if (!strcmp(current.username, users[j].username) && !strcmp(current.password, users[j].password))
        {
            valid = 1;
            break;
        }
    }

    if (valid) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
        exit(1);
    }

    printf("\nMAIN MENU\n");
    printf("1.Reserve a Room\
            \n2.Check-in\
            \n3.Cancel Reservation\
            \n4.Check-out\
            \n5.Check Room Availability\
            \n6.View Customer Details\
            \n7.Edit Reservation Details\
            \n8.Search\
            \n9.Reservation Report\
            \n10.Exit\
            \n>Choose an Option: ");
    int menu;scanf("%d",&menu);
    while (menu<0 || menu>10)
    {
        printf("please enter valid input: ");
        scanf("%d",&menu);
    }
    if(menu==10)
    {
        printf("ByeBye!");
        exit(1);
    }

    return 0;
}
