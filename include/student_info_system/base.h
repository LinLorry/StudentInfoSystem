#ifndef STUDENT_INFO_SYSTEM_BASE_H
#define STUDENT_INFO_SYSTEM_BASE_H

#define CLEAR()        \
    printf("\033[2J"); \
    printf("\033[0;0H");

#define CLEAR_STDIN() while (getchar() != '\n')

#define CLEAR_STDIN_WITH_PRE(input) \
    if (input != '\n')              \
        while (getchar() != '\n')

#define DATA_FILE_NAME "data.dat"
#define DATA_TMP_FILE_NAME "data.dat.tmp"

struct Header
{
    unsigned long user_number;
    unsigned long user_list_index;

    unsigned long student_number;
    unsigned long student_list;

    unsigned long student_grade_number;
    unsigned long student_grade_list;
};

typedef struct Header header;

int open_system(const char *username, const char *password);

unsigned char get_current_level();

unsigned long get_current_id();

int close_system();

#endif // STUDENT_INFO_SYSTEM_BASE_H