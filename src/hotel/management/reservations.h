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
    room_t *room_p;
    bool confirmed; /* unconfirmed: 0, confirmed: 1*/
    int n_nights;
    struct tm date;
    customer_t customer;
} reservation_t;

void save_and_unload_reservations(void);

void load_reservations(void);

size_t get_reservations_count(void);

reservation_t *get_reservations_list(void);
void add_reservation(reservation_t *new_reservation);