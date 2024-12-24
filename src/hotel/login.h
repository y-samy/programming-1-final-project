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
} credentials_t;

typedef struct {
    credentials_t *users_list;
    size_t users_count;
    bool logged_in;
    size_t user_id;
} LoginSession;

void init_login_session(LoginSession **session);
void terminate_login_session(LoginSession *login_session);
bool is_logged_in(LoginSession *login_session);
bool verify_username(LoginSession *login_session, const char *username);
bool verify_password(LoginSession *login_session, const char *password);
void logout(LoginSession *login_session);