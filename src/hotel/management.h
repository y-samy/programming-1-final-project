typedef struct
{
    int reservationId;
    int roomId;
    char checkinStatus[20];
    char name[100];
    int nationalId;
    char date[13];
    char email[100];
    int phoneNum;
} customer_t;

typedef struct
{
    int room_id;
    char availability[11];
    char view[16];
    int price;
} room_t;

customer_t* loadReservation(void);

int loadRooms(room_t roomList[100]);

void roomAvailability(int option);
