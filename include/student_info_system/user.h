#ifndef STUDENT_INFO_SYSTEM_USER_H
#define STUDENT_INFO_SYSTEM_USER_H

#include <stdio.h>

#include <student_info_system/base.h>

#define USERNAME_BUFFER_SIZE 256
#define PASSWORD_BUFFER_SIZE 256

#define USERNAME_MAX_LENGTH USERNAME_BUFFER_SIZE - 1
#define PASSWORD_MAX_LENGTH PASSWORD_BUFFER_SIZE - 1

#define EXPAND_USER_INFOS_SIZE 5

#define USER_LEVEL_VALUE 0
#define ADMIN_LEVEL_VALUE 1

struct UserInfo
{
    unsigned long id;
    unsigned char level;
    char username[USERNAME_BUFFER_SIZE];
    char password[PASSWORD_BUFFER_SIZE];
};

typedef struct UserInfo user_info;
typedef const struct UserInfo const_user_info;

int init_user_infos(FILE *fp, const header *head);

const_user_info *get_user_infos();

unsigned long get_user_number();

int add_user(const unsigned char level, const char *username, const char *password);

int delete_user(const unsigned long id);

int update_user(
    const unsigned long id, const unsigned char level,
    const char *username, const char *password
);

int free_user_infos();

#endif // STUDENT_INFO_SYSTEM_USER_H