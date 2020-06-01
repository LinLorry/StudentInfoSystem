#ifndef STUDENT_INFO_SYSTEM_STUDENT_H
#define STUDENT_INFO_SYSTEM_STUDENT_H

#include <stdio.h>

#include <student_info_system/base.h>
#include <student_info_system/types.h>

int init_student_infos(FILE *fp, const header *head);

const_student_info *get_students();

unsigned long get_student_number();

int add_student(const char *name);

int delete_student(const unsigned long id);

int update_student(const unsigned long id, const char *name);

void free_student_infos();

const_student_info *get_student(const unsigned long id);

#endif // STUDENT_INFO_SYSTEM_STUDENT_H