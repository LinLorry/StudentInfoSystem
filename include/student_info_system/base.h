#ifndef STUDENT_INFO_SYSTEM_BASE_H
#define STUDENT_INFO_SYSTEM_BASE_H

#define USERNAME_BUFFER_SIZE 256
#define PASSWORD_BUFFER_SIZE 256

#define USERNAME_MAX_LENGTH USERNAME_BUFFER_SIZE - 1
#define PASSWORD_MAX_LENGTH PASSWORD_BUFFER_SIZE - 1

#define CLEAR()          \
    printf("\033[2J");   \
    printf("\033[0;0H"); \
    printf("\n\n\n")

#define DATA_FILE_NAME "data.dat"
#define DATA_TMP_FILE_NAME "data.dat.tmp"

typedef unsigned char level;

struct Header
{
    unsigned int user_number;
    unsigned int user_list_index;

    unsigned int student_number;
    unsigned int student_list;

    unsigned int student_grade_number;
    unsigned int student_grade_list;
};

struct UserInfo
{
    level l;
    char username[USERNAME_BUFFER_SIZE];
    char password[PASSWORD_BUFFER_SIZE];
};

typedef struct Header header;
typedef struct UserInfo user_info;

#endif // STUDENT_INFO_SYSTEM_BASE_H