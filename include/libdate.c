#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libdate.h"

#define DATE_SIZE 12 //(2+2+4 int, +2 dash, +1 null, +1 newline) ex: 17-12-2024\0\n

int get_date(date_t *check_in_date,char chdate[DATE_SIZE]);
/*
int main()
{
#define NUM_OF_DATES 5
#define NUM_OF_RES 10
    char check_in[DATE_SIZE];
    struct Reservation res[NUM_OF_RES];
    for(int i=0; i<NUM_OF_DATES; i++)
    {
        printf("Enter date d-m-yy: ");
        int date_valid = get_date(&res[i].check_in_date,check_in);
        if (date_valid)
            printf("Day: %d\nMonth: %d\nYear: %d\n",res[i].check_in_date.day,res[i].check_in_date.month,res[i].check_in_date.year);
        else
        {
            printf("invalid date\n");
            --i;
        }                                               //IF YOU WANNA TEST IT
    }
    return 0;
}
*/
int get_date(date_t *check_in_date,char chdate[DATE_SIZE])
{
    fgets(chdate,12,stdin);
    char delim[1]= "-";
    void *DMY = strtok(chdate,delim);
    int d,m,y;
    for (int i = 0; i < 3; i++)
    {
        if (i==0) d = atoi(DMY);
        if (i==1) m = atoi(DMY);
        if (i==2) y = atoi(DMY);
        DMY = strtok(NULL,delim);
    }
    int leap = ((y%4==0 || y%100!=0) ||(y%400==0));
    if (y<2024) return 0;
    if (m<1 || m>12) return 0;
    if (y==2024 && m<12 ||( y==2024 && m==12 && d<30)) return 0; //current date el mona2sha
    if (leap)
    {
        if (m==2)
        {
            if(d>=1 && d<=29)
            {
                check_in_date->day = d;
                check_in_date->month = m;
                check_in_date->year = y;
                return 1;
            }
        }
        else if (m==1 || m== 3 || m== 5 || m==7 || m==8 || m==10 || m==12)
        {
            if(d>=1 && d<=31)
            {
                check_in_date->day = d;
                check_in_date->month = m;
                check_in_date->year = y;
                return 1;
            }
        }
        else if (d>=1 && d<=30)
        {
            check_in_date->day = d;
            check_in_date->month = m;
            check_in_date->year = y;
            return 1;
        }
    }
    else//not a leap year
    {
        if (m==2)
        {
            if(d>=1 && d<=28)
            {
                check_in_date->day = d;
                check_in_date->month = m;
                check_in_date->year = y;
                return 1;
            }
        }
        else if (m==1 || m== 3 || m== 5 || m==7 || m==8 || m==10 || m==12)
        {
            if(d>=1 && d<=31)
            {
                check_in_date->day = d;
                check_in_date->month = m;
                check_in_date->year = y;
                return 1;
            }
        }
        else if (d>=1 && d<=30)
        {
            check_in_date->day = d;
            check_in_date->month = m;
            check_in_date->year = y;
            return 1;
        }
    }
    return 0;
}
