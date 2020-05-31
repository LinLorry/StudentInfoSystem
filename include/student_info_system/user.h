#ifndef STUDENT_INFO_SYSTEM_USER_H
#define STUDENT_INFO_SYSTEM_USER_H

#include <stdio.h>

#include <student_info_system/base.h>
#include <student_info_system/types.h>

int init_user_infos(FILE *fp, const header *head);

const_user_info *get_user_infos();

unsigned long get_user_number();

int add_user(const unsigned char level, const char *username, const char *password);

int delete_user(const unsigned long id);

int update_user(
    const unsigned long id, const unsigned char level,
    const char *username, const char *password
);

void free_user_infos();

#endif // STUDENT_INFO_SYSTEM_USER_H