#include "libdate.h"

struct tm get_current_date(void)
{
    time_t t = time(NULL);
    return *localtime(&t);
}