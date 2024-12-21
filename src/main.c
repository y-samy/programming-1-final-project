#include <ui.h>
#include <auth/login.h>
#include <management/reservations.h>
#include <management/rooms.h>

int main()
{

    reservation_t *reservation = loadReservation();

    printf("%d", reservation[0].n_nights);
    /* Unload serialized data */

    end_user_session();
    /* Deserialize */
    /*save_and_unload_rooms();*/
    return 0;
}
