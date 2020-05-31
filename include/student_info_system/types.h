#ifndef STUDENT_INFO_SYSTEM_TYPES_H
#define STUDENT_INFO_SYSTEM_TYPES_H

#define USERNAME_BUFFER_SIZE 256
#define PASSWORD_BUFFER_SIZE 256

#define USERNAME_MAX_LENGTH USERNAME_BUFFER_SIZE - 1
#define PASSWORD_MAX_LENGTH PASSWORD_BUFFER_SIZE - 1

#define EXPAND_USER_INFOS_SIZE 5

#define USER_LEVEL_VALUE 0
#define ADMIN_LEVEL_VALUE 1

#define STUDENT_NAME_BUFFER_SIZE 256

#define STUDENT_NAME_MAX_LENGTH STUDENT_NAME_BUFFER_SIZE - 1

#define EXPAND_STUDENT_SIZE 5

#define COURSE_NAME_BUFFER_SIZE 256

#define COURSE_NAME_MAX_LENGTH COURSE_NAME_BUFFER_SIZE - 1

#define EXPAND_COURSE_SIZE 5

struct Header
{
    unsigned long user_number;
    unsigned long user_list_index;

    unsigned long student_number;
    unsigned long student_list_index;

    unsigned long course_number;
    unsigned long course_list_index;

    unsigned long student_grade_number;
    unsigned long student_grade_list_index;
};

struct UserInfo
{
    unsigned long id;
    unsigned char level;
    char username[USERNAME_BUFFER_SIZE];
    char password[PASSWORD_BUFFER_SIZE];
};

struct StudentInfo
{
    unsigned long id;
    char name[STUDENT_NAME_BUFFER_SIZE];
};

struct Course
{
    unsigned long id;
    char name[COURSE_NAME_BUFFER_SIZE];
};

typedef struct Header header;

typedef struct UserInfo user_info;
typedef const struct UserInfo const_user_info;

typedef struct StudentInfo student_info;
typedef const struct StudentInfo const_student_info;

typedef struct Course course;
typedef const struct Course const_course;

#endif // STUDENT_INFO_SYSTEM_TYPES_H
