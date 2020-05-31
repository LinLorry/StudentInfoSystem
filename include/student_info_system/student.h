#ifndef STUDENT_INFO_SYSTEM_STUDENT_H
#define STUDENT_INFO_SYSTEM_STUDENT_H

#include <stdio.h>

#include <student_info_system/base.h>

#define STUDENT_NAME_BUFFER_SIZE 256

#define STUDENT_NAME_MAX_LENGTH STUDENT_NAME_BUFFER_SIZE - 1

#define EXPAND_STUDENT_SIZE 5

struct StudentInfo
{
    unsigned long id;
    char name[STUDENT_NAME_BUFFER_SIZE];
};

typedef struct StudentInfo student_info;
typedef const struct StudentInfo const_student_info;

int init_student_infos(FILE *fp, const header *head);

const_student_info *get_students();

unsigned long get_student_number();

int add_student(const char *name);

int delete_student(const unsigned long id);

int update_student(const unsigned long id, const char *name);

void free_student_infos();

#endif // STUDENT_INFO_SYSTEM_STUDENT_H