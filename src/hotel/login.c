#include "login.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libparse.h>

#define USERS_FILE "users.txt"


void init_login_session(LoginSession **session)
{

    *session = malloc(sizeof(LoginSession));
    LoginSession *login_session = *session;
    FILE *users_file = fopen(USERS_FILE, "r");
    login_session->users_count = file_entry_count(users_file);
    fclose(users_file);
    users_file = fopen(USERS_FILE, "r");
    login_session->users_list = malloc(sizeof(credentials_t) * login_session->users_count);
    login_session->user_id = 0;
    login_session->logged_in = false;
    size_t i;
    for (i = 0; i < login_session->users_count; i++)
        fscanf(users_file,"%99s %99s",login_session->users_list[i].username, login_session->users_list[i].password);
    fclose(users_file);
}

void terminate_login_session(LoginSession *login_session)
{
    free(login_session->users_list);
    free(login_session);
}

bool is_logged_in(LoginSession *login_session)
{
    return login_session->logged_in;
}

bool verify_username(LoginSession *login_session, const char *username)
{
    size_t i = 0;
    bool valid = false;
    for (i = 0; i < login_session->users_count; i++) {
        if (!strcmp(username,login_session->users_list[i].username)) {
            valid = true;
            login_session->user_id = i+1;
            break;
        }
    }
    return valid;
}

bool verify_password(LoginSession *login_session, const char *password)
{
    bool valid = false;
    valid = !(strcmp(password, login_session->users_list[login_session->user_id-1].password));
    if (valid) {
        login_session->logged_in = true;
    }
    return valid;
}

void logout(LoginSession *login_session)
{
    login_session->logged_in = false;
    login_session->user_id = 0;
}