/*
 * Pragma once to prevent the includes
 * from happening multiple times
 */
#pragma once
#include <stdio.h>
#include <stdbool.h>

#define USERNAME_LEN 100
#define PASSWORD_LEN 100
typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    bool logged_in;
} user_t;

#define LOGIN_SUCCES 0
#define LOGIN_ERROR 1

user_t session(void);
bool is_logged_in(user_t *user);
bool verify_username(user_t *user, const char *username);
bool verify_password(user_t *user, const char *password);
void auth_user(user_t *user);
