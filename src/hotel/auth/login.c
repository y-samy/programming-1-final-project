#include "login.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


size_t get_user_count(bool reset)
{
    static size_t count = 0;
    if (reset) { /* reset */
        count = 0;
        return count;
    }
    if (count)
        return count;
    int c;
    FILE *users_file = fopen("users.txt", "r");
    while ((c= fgetc(users_file)) != EOF) {
        if (c == '\n')
            count++;
    }
    fclose(users_file);
    return count;
}

user_t *get_user_list(size_t user_count, bool reset)
{
    static user_t *user_list = NULL;
    if (reset) { /* reset */
        free(user_list);
        return NULL;
    }
    if (user_list)
        return user_list;
    user_list = malloc(sizeof(user_t) * user_count);
    size_t i;
    FILE *users_file = fopen("users.txt", "r");
    for (i = 0; i < user_count; i++)
    {
        fscanf(users_file,"%99s %99s",&user_list[i].username,&user_list[i].password);
    }
    fclose(users_file);
    return user_list;
}

user_t new_user_session()
{
    user_t user;
    user.logged_in = false;
    get_user_list(get_user_count(false), false);
    return user;
}

void end_user_session(void)
{
    get_user_list(get_user_count(true), true);
}

bool is_logged_in(user_t *user)
{
    return user->logged_in;
}

bool verify_username(user_t *user, const char *username)
{
    size_t i = 0;
    bool valid = false;
    size_t user_count = get_user_count(false);
    user_t *user_list = get_user_list(user_count, false);
    for (i = 0; i < user_count; i++) {
        if (!strcmp(username, user_list[i].username)) {
            valid = true;
            break;
        }
    }
    if (valid) {
        strcpy(user->username,user_list[i].username);
        strcpy(user->password,user_list[i].password);
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

void logout(user_t *user)
{
    user->logged_in = false;
}