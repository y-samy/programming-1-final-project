#pragma once


typedef enum {
    January = 1, February, March, April, May, June, July, August, September, October, November, December
} month_t;

typedef struct {
    int day;
    month_t month;
    int year;
} date_t;

