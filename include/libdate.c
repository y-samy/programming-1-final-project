#include "libdate.h"

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