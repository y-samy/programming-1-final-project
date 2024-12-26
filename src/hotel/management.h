#pragma once
#include <stdbool.h>
#include <time.h>

typedef struct {
    char name[100];
    char nationalId[15];
    char email[100];
    char phoneNum[15];
} customer_t;

typedef struct {
    int reservation_id;
    bool checked_in;
    int nights_count;
    struct tm date;
    customer_t customer;
} reservation_t;

typedef enum { SeaView, LakeView, GardenView } room_view_t;

typedef struct {
    int id;
    reservation_t reservation;
    bool reserved;
    room_view_t view_category;
    int price;
} room_t;


typedef struct {
    room_t *rooms_p;
    size_t rooms_count;
} HotelSession;


void init_management_session(HotelSession **session);
void terminate_management_session(HotelSession *hotel_session);

reservation_t create_reservation(void);
room_t *get_available_room_by_category(HotelSession *hotel_session, room_view_t view_category);
room_t *get_available_rooms(HotelSession *hotel_session);
room_t *get_reserved_rooms(HotelSession *hotel_session);
reservation_t *get_reservation_by_id(HotelSession *hotel_session, int id);
room_t *get_room_by_id(HotelSession *hotel_session, int id);
room_t *get_room_by_reservation(HotelSession *hotel_session, reservation_t *reservation_p);
void cancel_reservation(HotelSession *hotel_session, int id);
int add_reservation(HotelSession *session, room_t *room, reservation_t reservation);
void edit_reservation(HotelSession *hotel_session, room_t *new_room, reservation_t new_reservation, int old_room_id);
char *stringify_availability(room_t *room);
char *stringify_view(room_t *room);
int get_room_id(room_t *room);
int get_price_per_night(room_t *room);


room_t *get_room_by_customer_name(HotelSession *session, char *name);
room_t *get_room_by_checkin_date(HotelSession *session, struct tm date);

void cull_expired_reservations(HotelSession *hotel_session);