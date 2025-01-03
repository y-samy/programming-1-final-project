#include "management.h"
#include <math.h>

#include <libparse.h>
#include <string.h>

#include "libdate.h"

#define RESERVATIONS_FILE "reservations.txt"
#define ROOMS_FILE "Room.txt"

static const reservation_t empty_reservation = {0};

void init_management_session(HotelSession **session_p)
{
    *session_p = malloc(sizeof(HotelSession));
    HotelSession *hotel_session = *session_p;
    size_t i, j;
    hotel_session->customers_overstaying = 0;
    FILE *rooms_file = fopen(ROOMS_FILE, "r");
    hotel_session->rooms_count = file_entry_count(rooms_file);
    fclose(rooms_file);
    rooms_file = fopen(ROOMS_FILE, "r");
    hotel_session->rooms_p = malloc(sizeof(room_t) * hotel_session->rooms_count);
    room_t *rooms_list = hotel_session->rooms_p;
    char availability_buffer[14];
    char room_category_buffer[11];
    for (i = 0; i < hotel_session->rooms_count; i++)
    {
        fscanf(rooms_file, "%d %s %s %d", &rooms_list[i].id, availability_buffer, room_category_buffer,
               &rooms_list[i].price);
        if (!strcmp(room_category_buffer, "SeaView"))
            rooms_list[i].view_category = SeaView;
        if (!strcmp(room_category_buffer, "LakeView"))
            rooms_list[i].view_category = LakeView;
        if (!strcmp(room_category_buffer, "GardenView"))
            rooms_list[i].view_category = GardenView;
        rooms_list[i].reserved = false;
        rooms_list[i].reservation = empty_reservation;
    }
    fclose(rooms_file);

    FILE *reservations_file = fopen(RESERVATIONS_FILE, "r");
    size_t total_reservations_count = file_entry_count(reservations_file);
    fclose(reservations_file);
    reservations_file = fopen(RESERVATIONS_FILE, "r");
    int room_id_buffer;
    int reservation_id_buffer;
    char status_buf[14];
    for (i = 0; i < total_reservations_count; i++)
    {
        fscanf(reservations_file, "%d,%d,", &reservation_id_buffer, &room_id_buffer);
        for (j = 0; j < hotel_session->rooms_count; j++)
        {
            if (room_id_buffer != rooms_list[j].id)
                continue;

            reservation_t reservation = empty_reservation;
            fscanf(reservations_file, "%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", status_buf,
                   reservation.customer.name, reservation.customer.nationalId,
                   &reservation.nights_count,
                   &reservation.date.tm_mday, &reservation.date.tm_mon,
                   &reservation.date.tm_year,
                   reservation.customer.email, reservation.customer.phoneNum);
            reservation.date.tm_year -= 1900;
            reservation.date.tm_mon -= 1;
            mktime(&reservation.date);
            sanitize_date(&reservation.date);
            reservation.checked_in = !(strcmp(status_buf, "confirmed")) ? true : false;
            reservation.reservation_id = reservation_id_buffer;
            rooms_list[j].reservation = reservation;
            rooms_list[j].reserved = true;
            break;
        }
    }
    fclose(reservations_file);
}

void discard_management_session(HotelSession *hotel_session)
{
    free(hotel_session->rooms_p);
    free(hotel_session);
}

void terminate_management_session(HotelSession *hotel_session)
{
    size_t i, j, k;
    FILE *reservations_file = fopen(RESERVATIONS_FILE, "w");
    FILE *rooms_file = fopen(ROOMS_FILE, "w");
    for (i = 0; i < hotel_session->rooms_count; i++)
    {
        room_t *room = &hotel_session->rooms_p[i];
        fprintf(rooms_file, "%d %s %s %d\n", room->id, stringify_availability(room),
                stringify_view(room), room->price);
    }

    int count = 0;
    for (i = 0; i < hotel_session->rooms_count; i++)
    {
        if (hotel_session->rooms_p[i].reserved)
            count++;
    }

    room_t *reserved_rooms = malloc(sizeof(room_t) * count);
    count = 0;

    for (i = 0; i < hotel_session->rooms_count; i++)
    {
        if (hotel_session->rooms_p[i].reserved)
            memcpy(&reserved_rooms[count++], &hotel_session->rooms_p[i], sizeof(room_t));
    }

    for (i = 0; i < count; i++)
    {
        for (j = 1; j < count; j++)
        {
            if (difftime(mktime(&reserved_rooms[j].reservation.date), mktime(&reserved_rooms[j - 1].reservation.date)) < 0)
            {
                room_t temp = reserved_rooms[j];
                reserved_rooms[j] = reserved_rooms[j - 1];
                reserved_rooms[j - 1] = temp;
            }
        }
    }

    for (i = 0; i < count; i++)
    {
        room_t temp_reservation = reserved_rooms[i];
        fprintf(reservations_file, "%d,%d,%s,%s,%s,%d,%d-%d-%d,%s,%s\n", temp_reservation.reservation.reservation_id,
                temp_reservation.id, (temp_reservation.reservation.checked_in ? "confirmed" : "unconfirmed"),
                temp_reservation.reservation.customer.name, temp_reservation.reservation.customer.nationalId,
                temp_reservation.reservation.nights_count,
                temp_reservation.reservation.date.tm_mday, temp_reservation.reservation.date.tm_mon + 1,
                temp_reservation.reservation.date.tm_year + 1900,
                temp_reservation.reservation.customer.email, temp_reservation.reservation.customer.phoneNum);
    }

    free(reserved_rooms);

    free(hotel_session->rooms_p);
    free(hotel_session);
    fclose(reservations_file);
    fclose(rooms_file);
}

reservation_t *get_reservation_by_id(HotelSession *hotel_session, int id)
{
    size_t i;
    for (i = 0; i < hotel_session->rooms_count; i++)
    {
        if (id == hotel_session->rooms_p[i].reservation.reservation_id && hotel_session->rooms_p[i].reserved)
            return &hotel_session->rooms_p[i].reservation;
    }
    return NULL;
}

static int generate_id(HotelSession *hotel_session)
{
    time_t t;
    int id;
    do
    {
        t = time(NULL);
        srand(t);
        id = rand() % 100000;
    } while (get_reservation_by_id(hotel_session, id) != NULL);
    return id;
}

room_t *get_available_room_by_category(HotelSession *hotel_session, room_view_t view_category)
{
    size_t i;
    for (i = 0; i < hotel_session->rooms_count; i++)
    {
        if (view_category == hotel_session->rooms_p[i].view_category && !hotel_session->rooms_p[i].reserved)
            return &hotel_session->rooms_p[i];
    }
    return NULL;
}

int add_reservation(HotelSession *session, room_t *room, reservation_t reservation)
{
    reservation.reservation_id = generate_id(session);
    room->reservation = reservation;
    room->reserved = true;
    return reservation.reservation_id;
}

void edit_reservation(HotelSession *hotel_session, room_t *new_room, reservation_t new_reservation, int old_room_id)
{
    new_room->reservation = new_reservation;
    new_room->reserved = true;
    room_t *old_room = get_room_by_id(hotel_session, old_room_id);
    old_room->reserved = false;
    old_room->reservation = create_reservation();
}

room_t *get_available_rooms(HotelSession *hotel_session)
{
    static HotelSession *internal_session = NULL;
    static size_t i = 0;
    if (hotel_session != NULL)
    {
        internal_session = hotel_session;
        i = 0;
    }
    while (i < internal_session->rooms_count)
    {
        if (!internal_session->rooms_p[i].reserved)
        {
            return &internal_session->rooms_p[i++];
        }
        i++;
    }
    return NULL;
}

room_t *get_reserved_rooms(HotelSession *hotel_session)
{
    static HotelSession *internal_session = NULL;
    static size_t i = 0;
    if (hotel_session != NULL)
    {
        internal_session = hotel_session;
        i = 0;
    }
    while (i < internal_session->rooms_count)
    {
        if (internal_session->rooms_p[i].reserved)
        {
            return &internal_session->rooms_p[i++];
        }
        i++;
    }
    return NULL;
}

int get_room_id(room_t *room)
{
    return room->id;
}

char *stringify_availability(room_t *room)
{
    return (room->reserved) ? "Unavailable" : "Available";
}

room_view_t get_room_view(room_t *room)
{
    return room->view_category;
}

char *stringify_view(room_t *room)
{
    switch (room->view_category)
    {
    case SeaView:
        return "SeaView";
        break;
    case LakeView:
        return "LakeView";
        break;
    case GardenView:
        return "GardenView";
        break;
    }
}

int get_price_per_night(room_t *room)
{
    return room->price;
}

static void remove_reservation(HotelSession *hotel_session, reservation_t *reservation)
{
    size_t i;
    for (i = 0; i < hotel_session->rooms_count; i++)
    {
        if (&hotel_session->rooms_p[i].reservation == reservation)
        {
            if (hotel_session->rooms_p[i].reserved)
                hotel_session->rooms_p[i].reserved = false;
            hotel_session->rooms_p[i].reservation = empty_reservation;
            break;
        }
    }
}

void cancel_reservation(HotelSession *hotel_session, int id)
{
    remove_reservation(hotel_session, get_reservation_by_id(hotel_session, id));
}

room_t *get_room_by_reservation(HotelSession *hotel_session, reservation_t *reservation_p)
{
    size_t i;
    for (i = 0; i < hotel_session->rooms_count; i++)
    {
        if (hotel_session->rooms_p[i].reserved && &hotel_session->rooms_p[i].reservation == reservation_p)
        {
            return &hotel_session->rooms_p[i];
        }
    }
    return NULL;
}

reservation_t create_reservation(void)
{
    return empty_reservation;
}

room_t *get_room_by_id(HotelSession *hotel_session, int id)
{
    size_t i;
    for (i = 0; i < hotel_session->rooms_count; i++)
    {
        if (hotel_session->rooms_p[i].id == id)
        {
            return &hotel_session->rooms_p[i];
        }
    }
    return NULL;
}

room_t *get_room_by_customer_name(HotelSession *session, char *name)
{
    static HotelSession *internal_session = NULL;
    static size_t i = 0;
    if (session != NULL)
    {
        internal_session = session;
        i = 0;
    }
    while (i < internal_session->rooms_count)
    {
        if (internal_session->rooms_p[i].reserved && strstr(internal_session->rooms_p[i].reservation.customer.name,
                                                            name) != NULL)
        {
            return &internal_session->rooms_p[i++];
        }
        i++;
    }
    return NULL;
}

room_t *get_room_by_checkin_date(HotelSession *session, struct tm date)
{
    static HotelSession *internal_session = NULL;
    static size_t i = 0;
    if (session != NULL)
    {
        internal_session = session;
        i = 0;
    }
    while (i < internal_session->rooms_count)
    {
        if (internal_session->rooms_p[i].reserved && internal_session->rooms_p[i].reservation.checked_in && abs((int)ceil(difftime(mktime(&date), mktime(&internal_session->rooms_p[i].reservation.date)))) < 86400)
        {
            return &internal_session->rooms_p[i++];
        }
        i++;
    }
    return NULL;
}

void cull_expired_reservations(HotelSession *hotel_session)
{
    size_t i;
    int customers_overstaying = 0;
    struct tm current_date = get_current_date(), res_date = {0};
    for (i = 0; i < hotel_session->rooms_count; i++)
    {
        if (hotel_session->rooms_p[i].reserved)
        {
            res_date = hotel_session->rooms_p[i].reservation.date;
            res_date.tm_mday += hotel_session->rooms_p[i].reservation.nights_count;
            if ((int)ceil(difftime(mktime(&current_date), mktime(&res_date))) > 0)
            {
                if (hotel_session->rooms_p[i].reservation.checked_in)
                {
                    customers_overstaying++;
                    continue;
                }
                hotel_session->rooms_p[i].reserved = false;
                hotel_session->rooms_p[i].reservation = empty_reservation;
            }
        }
    }
    hotel_session->customers_overstaying = customers_overstaying;
}
