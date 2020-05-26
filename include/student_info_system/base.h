#ifndef STUDENT_INFO_SYSTEM_BASE_H
#define STUDENT_INFO_SYSTEM_BASE_H

#define CLEAR()        \
    printf("\033[2J"); \
    printf("\033[0;0H");

#define CLEAR_STDIN(input) \
    if (input != '\n')     \
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

#endif // STUDENT_INFO_SYSTEM_BASE_H