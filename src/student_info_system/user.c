#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <student_info_system/base.h>
#include <student_info_system/types.h>
#include <student_info_system/user.h>

unsigned long user_number = 0;
unsigned long user_infos_size = 0;
user_info *user_infos = NULL;

int init_user_infos(FILE *fp, const header *head)
{
    size_t read;
    const unsigned long tmp = head->user_number;
    const unsigned long original_position = ftell(fp);

    if (fseek(fp, sizeof(header), SEEK_SET))
    {
        perror("[Init user info]\tseek file position failed: ");
        fseek(fp, original_position, SEEK_SET);
        return -1;
    }

    user_infos = (user_info *)malloc(tmp * sizeof(user_info));

    if (NULL == user_infos)
    {
        perror("[Init user info]\tmalloc user info memory failed: ");
        fseek(fp, original_position, SEEK_SET);
        return -1;
    }
    read = fread(user_infos, sizeof(user_info), tmp, fp);

    if (tmp != read)
    {
        fprintf(stderr, "[Init user info]\tuser number error.\n");
        free(user_infos);
        user_infos = NULL;
        fseek(fp, original_position, SEEK_SET);
        return -1;
    }

    user_number = tmp;
    user_infos_size = tmp;
    fseek(fp, original_position, SEEK_SET);
    return 0;
}

const_user_info *get_user_infos()
{
    return user_infos;
}

unsigned long get_user_number()
{
    return user_number;
}

int expand_user_infos()
{
    user_info *tmp;
    const unsigned long expand_user_infos_size = user_infos_size + EXPAND_USER_INFOS_SIZE;

    tmp = (user_info *)malloc(expand_user_infos_size * sizeof(user_info));
    if (NULL == tmp)
    {
        perror("[Expand user info]\tmalloc user info memory failed: ");
        return -1;
    }
    memcpy(tmp, user_infos, user_number * sizeof(user_info));

    free(user_infos);
    user_infos = tmp;
    user_infos_size = expand_user_infos_size;

    return 0;
}

int add_user(const unsigned char level, const char *username, const char *password)
{
    int tmp;
    user_info *user_info_p;
    user_info *last_user;

    if (user_number == user_infos_size && (tmp = expand_user_infos()))
    {
        fprintf(stderr, "[Add user]\tadd user fail.\n");
        return tmp;
    }
    last_user = user_infos + (user_number - 1);
    user_info_p = user_infos + user_number;

    user_number++;
    user_info_p->id = last_user->id + 1;
    user_info_p->level = level;
    strcpy(user_info_p->username, username);
    strcpy(user_info_p->password, password);

    return 0;
}

int delete_user(const unsigned long id)
{
    unsigned long position = 0;
    user_info *user_info_p = user_infos;
    const user_info *user_info_end = user_infos + user_number - 1;

    if (id > user_info_end->id)
    {
        fprintf(stderr,
                "[Delete user]\t"
                "delete user fail, user with ID %ld does not exist.\n",
                id);
        return -1;
    }

    while (user_info_p < user_info_end && id != user_info_p->id)
    {
        user_info_p++;
        position++;
    }

    if (user_info_end == user_info_p && id != user_info_p->id)
    {
        fprintf(stderr,
                "[Delete user]\t"
                "delete user fail, user with ID %ld does not exist.\n",
                id);
        return -1;
    }

    memcpy(user_info_p, user_info_p + 1, (user_number - position) * sizeof(user_info));
    user_number--;

    return 0;
}

int update_user(
    const unsigned long id, const unsigned char level,
    const char *username, const char *password)
{
    user_info *user_info_p = user_infos;
    const user_info *user_info_end = user_infos + user_number - 1;

    if (id > user_info_end->id)
    {
        fprintf(stderr,
                "[Update user]\t"
                "update user fail, user with ID %ld does not exist.\n",
                id);
        return -1;
    }

    while (user_info_p < user_info_end && id != user_info_p->id)
    {
        user_info_p++;
    }

    if (user_info_end == user_info_p && id != user_info_p->id)
    {
        fprintf(stderr,
                "[Update user]\t"
                "update user fail, user with ID %ld does not exist.\n",
                id);
        return -1;
    }

    user_info_p->level = level;
    strcpy(user_info_p->username, username);
    strcpy(user_info_p->password, password);

    return 0;
}

void free_user_infos() { free(user_infos); }
