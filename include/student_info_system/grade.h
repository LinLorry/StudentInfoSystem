#ifndef STUDENT_INFO_SYSTEM_GRADE_H
#define STUDENT_INFO_SYSTEM_GRADE_H

#include <stdio.h>

#include <student_info_system/base.h>
#include <student_info_system/types.h>

int init_grades(FILE *fp, const header *head);

const_grade *get_grades();

unsigned long get_grade_number();

int add_grade(const unsigned long student_id, const unsigned long crouse_id, const double value);

int delete_grade(const unsigned long student_id, const unsigned long crouse_id);

int update_grade(const unsigned long student_id, const unsigned long crouse_id, const double value);

void free_grades();

#endif // STUDENT_INFO_SYSTEM_GRADE_H