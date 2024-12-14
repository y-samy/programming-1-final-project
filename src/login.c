#include "login.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t count;
    user_t users[100];
} user_list;

user_list *get_user_list()
{
    static user_list users_l;
    if (users_l.count)
        return &users_l;
    FILE *user_file = fopen("users.txt", "r");
    if (!user_file) {
        fprintf (stderr, "Error Opening Users File.\nfopen() in %s() failed.\n", __func__);
        exit(1);
    }
    while (!feof(user_file))
    {
        fscanf(user_file,"%99s %99s",&users_l.users[users_l.count].username,&users_l.users[users_l.count].password);
        users_l.count++;
    }
}

user_t session()
{
    user_t user;
    user.logged_in = false;
    get_user_list();
    return user;
}

bool is_logged_in(user_t *user)
{
    return user->logged_in;
}

bool verify_username(user_t *user, const char *username)
{
    size_t j = 0;
    bool valid = false;
    user_list *users_l = get_user_list();
    for (j = 0; j < users_l->count; j++) {
        if (!strcmp(username, users_l->users[j].username)) {
            valid = true;
            break;
        }
    }
    if (valid) {
        strcpy(user->username,users_l->users[j].username);
        strcpy(user->password,users_l->users[j].password);
    }
    return valid;
}

bool verify_password(user_t *user, const char *password)
{
    size_t j = 0;
    bool valid = false;
    valid = !(strcmp(password, user->password));
    if (valid) {
        user->logged_in = true;
        strcpy(user->password, password);
    }
    return valid;
}