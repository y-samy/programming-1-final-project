#pragma once
#include <time.h>



struct tm get_current_date(void);
void sanitize_date(struct tm *date);
char *stringify_date(struct tm *date);