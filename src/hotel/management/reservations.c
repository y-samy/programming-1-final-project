#include "reservations.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define RESERVATIONS_FILE "Reservation.txt"

/* List access */
static reservation_t *list_holder(reservation_t *new_list, bool unset)
{
    /*
     * Usage:
     * set to NULL: list_holder(NULL, true);
     * set to room_t ptr: list_holder(ptr, false);
     * get ptr: list_holder(NULL, false);
     */
    static reservation_t *reservation_list = NULL;
    if (unset)
        reservation_list = NULL;
    if (new_list != NULL)
        reservation_list = new_list;
    return reservation_list;
}

static size_t count_holder(size_t new_count, bool unset)
{
    /*
     * Usage:
     * set to 0: count_holder(0, true);
     * set to n > 0: count_holder(n, false);
     * get value: count_holder(0, false);
     */
    static size_t count = 0;
    if (unset)
        count = 0;
    else if (new_count)
        count = new_count;
    return count;
}

/* deserialize */

static size_t file_entry_count(void)
{
    FILE *reservations_file = fopen(RESERVATIONS_FILE, "r");
    size_t count = 0;
    char c, prev_c = 0;
    while (1) {
        c = fgetc(reservations_file);
        if (c == EOF) {
            if (prev_c != '\n')
                count++;
            break;
        }
        if (c == '\n')
            count++;
        prev_c = c;
    }
    fclose(reservations_file);
    return count;
}

static void load_from_file()
{
    size_t count = count_holder(file_entry_count(), false);
    if (count == 0)
        list_holder(NULL, true);
    FILE *reservations_file = fopen(RESERVATIONS_FILE, "r");
    reservation_t *reservations = malloc(count * sizeof(reservation_t));
    size_t i;
    int room_id_buf;
    char status_buf[14];
    for (i = 0; i < count; i++) {
        fscanf(reservations_file, "%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", &reservations[i].reservation_id,
               &room_id_buf, status_buf,
               reservations[i].customer.name, reservations[i].customer.nationalId, &reservations[i].n_nights,
               &reservations[i].date.tm_mday, &reservations[i].date.tm_mon, &reservations[i].date.tm_year,
               reservations[i].customer.email, reservations[i].customer.phoneNum);
        reservations[i].room_p = get_room_by_id(room_id_buf);
        reservations[i].confirmed = strcmp(status_buf, "confirmed") ? false : true;
    }
    list_holder(reservations, false);
    fclose(reservations_file);
}

/* runtime functions */
reservation_t *get_reservation_by_id(int id)
{
    reservation_t *reservations = get_reservations_list();
    size_t count = get_reservations_count();
    size_t i;
    for (i = 0; i < count; i++) {
        if ((reservations + i)->reservation_id == id)
            return reservations + i;
    }
    return NULL;
}

static int generate_id(void)
{
    time_t t;
    int id;
    do {
        t = time(NULL);
        srand(t);
        id = rand() % 10000;
    } while (get_reservation_by_id(id) == NULL);
}



size_t get_reservations_count(void)
{
    return count_holder(0, false);
}

reservation_t *get_reservations_list(void)
{
    return list_holder(NULL, false);
}

/* Manipulate memory */
static void remove_reservation(reservation_t *reservation)
{
    size_t new_count = count_holder(get_reservations_count() - 1, false);
    reservation_t *reservations_list = list_holder(NULL, false);
    size_t index;
    size_t i = 0, j = 0;
    for (i = 0; i < new_count+i; i++) {
        if (&reservations_list[i] == reservation) {
            index = i;
            break;
        }
    }
    reservation_t *new_reservation_list = NULL;
    new_reservation_list = malloc(new_count * sizeof(reservation_t));
   memcpy(new_reservation_list, reservations_list, index * sizeof(reservation_t));
    memcpy(new_reservation_list + index, reservations_list + index + 1, (new_count - index) * sizeof(reservation_t));
    free(reservations_list);
    list_holder(new_reservation_list, false);
}

static void append_reservation(reservation_t *new_reservation)
{
    size_t new_count = count_holder(get_reservations_count() + 1, false);
    reservation_t *reservations_list = list_holder(NULL, false);
    reservation_t *new_reservation_list = NULL;
    new_reservation_list = realloc(reservations_list, new_count * sizeof(reservation_t));
    if (new_reservation_list == NULL)
        return; /* Keeps old pointer */
    memcpy(new_reservation_list + new_count - 1, new_reservation, sizeof(reservation_t));
    list_holder(new_reservation_list, false);
}

void end_reservation(reservation_t *reservation)
{
    remove_reservation(reservation);

}

void add_reservation(reservation_t *new_reservation)
{
    new_reservation->reservation_id = generate_id();
    append_reservation(new_reservation);
}

void load_reservations()
{
    load_from_file();
}



/* serialize */
void save_and_unload_reservations(void)
{
    FILE *reservations_file = fopen(RESERVATIONS_FILE, "w");
    reservation_t *reservations = list_holder(NULL, false);
    size_t line_count = count_holder(0, false);
    size_t i;
    for (i = 0; i < line_count; i++) {
        fprintf(reservations_file, "%d,%d,%s,%s,%s,%d,%d-%d-%d,%s,%s\n", reservations[i].reservation_id,
                reservations[i].room_p->id, (reservations[i].confirmed ? "confirmed" : "unconfirmed"),
                reservations[i].customer.name, reservations[i].customer.nationalId, reservations[i].n_nights,
                reservations[i].date.tm_mday, reservations[i].date.tm_mon, reservations[i].date.tm_year,
                reservations[i].customer.email, reservations[i].customer.phoneNum);
    }
    free(reservations);
    list_holder(NULL, true);
    fclose(reservations_file);
}