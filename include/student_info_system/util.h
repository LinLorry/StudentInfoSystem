#ifndef STUDENT_INFO_SYSTEM_UTIL_H
#define STUDENT_INFO_SYSTEM_UTIL_H

#include <stddef.h>

struct Menu
{
    char *content;
    int (*funtion)();
};

typedef struct Menu menu;

int show_menu(menu *menus, size_t menu_num, char *exist_str);

#endif // STUDENT_INFO_SYSTEM_UTIL_H