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
    char avaliablity[11];
    char view[16];
    int price;
} room_t;
