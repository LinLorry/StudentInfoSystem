#ifndef STUDENT_INFO_SYSTEM_COURSE_H
#define STUDENT_INFO_SYSTEM_COURSE_H

#include <stdio.h>

#include <student_info_system/base.h>
#include <student_info_system/types.h>

int init_courses(FILE *fp, const header *head);

const_course *get_courses();

unsigned long get_course_number();

int add_course(const char *name);

int delete_course(const unsigned long id);

int update_course(const unsigned long id, const char *name);

void free_courses();

const_course *get_course(const unsigned long id);

#endif // STUDENT_INFO_SYSTEM_COURSE_H