#pragma once

typedef enum { Sunday = 1, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday } day_t;

typedef enum {
    January = 1, February, March, April, May, June, July, August, September, October, November, December
} month_t;

typedef struct {
    day_t day;
    month_t month;
    int year;
} date_t;

