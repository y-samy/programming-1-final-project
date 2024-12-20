#pragma once
#include "rooms.h"
#include <stdbool.h>
#include <libdate.h>

typedef struct {
    char name[100];
    char nationalId[15];
    date_t date;
    char email[100];
    int phoneNum;
} customer_t;

typedef struct {
    int reservation_id;
    room_t room;
    bool check_in_status;
    customer_t customer;
} reservation_t;
