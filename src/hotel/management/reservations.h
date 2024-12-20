#pragma once
#include "rooms.h"
#include <stdbool.h>
#include <libdate.h>

typedef struct {
    char name[100];
    char nationalId[15];
    char email[100];
    char phoneNum[15];
} customer_t;

typedef struct {
    int reservation_id;
    room_t room;
    bool status; /* unconfirmed: 0, confirmed: 1*/
    int n_nights;
    date_t date;
    customer_t customer;
} reservation_t;