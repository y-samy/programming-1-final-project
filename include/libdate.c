#include "libdate.h"

#include <stdio.h>

struct tm get_current_date(void)
{
    time_t t = time(NULL);
    struct tm date = *localtime(&t);
    date.tm_hour = 0;
    date.tm_min = 0;
    date.tm_sec = 0;
    return date;
}

void sanitize_date(struct tm *date)
{
    date->tm_hour = 0;
    date->tm_min = 0;
    date->tm_sec = 0;
}

char *stringify_date(struct tm *date)
{
    static char date_string[14];
    sanitize_date(date);
    sprintf(date_string, "%d / %d / %d", date->tm_mday, date->tm_mon + 1, date->tm_year + 1900);
    return date_string;
}