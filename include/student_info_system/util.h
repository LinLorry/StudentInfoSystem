#ifndef STUDENT_INFO_SYSTEM_UTIL_H
#define STUDENT_INFO_SYSTEM_UTIL_H

#include <stddef.h>

struct Menu
{
    char *content;
    int (*funtion)();
};

typedef struct Menu menu;

int show_menu(const menu *menus, size_t menu_num, char *exist_str);

int input_str(
    char *str, const unsigned int max_length,
    const char *first_remind,
    const char *last_remind,
    const char *warn_remind
);

#endif // STUDENT_INFO_SYSTEM_UTIL_H