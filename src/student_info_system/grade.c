#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <student_info_system/base.h>
#include <student_info_system/types.h>
#include <student_info_system/grade.h>

unsigned long grade_number = 0;
unsigned long grades_size = 0;
grade *grades = NULL;

int init_grades(FILE *fp, const header *head)
{
    size_t read;
    const unsigned long tmp = head->grade_number;
    const unsigned long original_position = ftell(fp);
    const unsigned long offset = sizeof(header) +
                                 head->user_number * sizeof(user_info) +
                                 head->student_number * sizeof(student_info) +
                                 head->course_number * sizeof(course);

    if (fseek(fp, offset, SEEK_SET))
    {
        perror("[Init grades]\tseek file position failed: ");
        fseek(fp, original_position, SEEK_SET);
        return -1;
    }

    grades = (grade *)malloc(tmp * sizeof(grade));

    if (NULL == grades)
    {
        perror("[Init grades]\tmalloc grade info memory failed: ");
        fseek(fp, original_position, SEEK_SET);
        return -1;
    }
    read = fread(grades, sizeof(grade), tmp, fp);

    if (tmp != read)
    {
        fprintf(stderr, "[Init grades]\tgrade number error.\n");
        free(grades);
        grades = NULL;
        fseek(fp, original_position, SEEK_SET);
        return -1;
    }

    grade_number = tmp;
    grades_size = tmp;
    fseek(fp, original_position, SEEK_SET);
    return 0;
}

const_grade *get_grades()
{
    return grades;
}

unsigned long get_grade_number()
{
    return grade_number;
}

int expand_grades()
{
    grade *tmp;
    const unsigned long expand_grade_infos_size = grades_size + EXPAND_GRADE_SIZE;

    tmp = (grade *)malloc(expand_grade_infos_size * sizeof(grade));
    if (NULL == tmp)
    {
        perror("[Expand grades]\tmalloc grades memory failed: ");
        return -1;
    }
    memcpy(tmp, grades, grade_number * sizeof(grade));

    free(grades);
    grades = tmp;
    grades_size = expand_grade_infos_size;

    return 0;
}

int add_grade(const unsigned long student_id, const unsigned long crouse_id, const double value)
{
    int tmp;
    grade *grade_p;
    const_grade *grade_end;

    if (grade_number == grades_size && (tmp = expand_grades()))
    {
        fprintf(stderr, "[Add grade]\tadd grade fail.\n");
        return tmp;
    }

    grade_end = grades + grade_number;

    for (grade_p = grades; grade_p != grade_end; grade_p++)
    {
        if (grade_p->student_id == student_id && grade_p->course_id == crouse_id)
        {
            break;
        }
    }

    if (grade_p == grade_end)
    {
        grade_number++;
        grade_p->student_id = student_id;
        grade_p->course_id = crouse_id;
        grade_p->value = value;
        return 0;
    }
    else
    {
        fprintf(stderr, "[Add grade]\tthis student already have this crouse grade.\n");
        return -1;
    }
}

int delete_grade(const unsigned long student_id, const unsigned long crouse_id)
{
    unsigned long position = 0;
    grade *grade_p = grades;
    const_grade *last_grade = grades + (grade_number - 1);

    while (grade_p != last_grade && (student_id != grade_p->student_id || crouse_id != grade_p->course_id))
    {
        grade_p++;
        position++;
    }

    if (last_grade == grade_p && (student_id != grade_p->student_id || crouse_id != grade_p->course_id))
    {
        fprintf(stderr,
                "[Delete grade]\t"
                "delete grade fail, student with ID %ld does have crouse with ID &ld.\n",
                student_id, crouse_id
        );
        return -1;
    }

    memcpy(grade_p, grade_p + 1, (grade_number - position) * sizeof(grade));
    grade_number--;

    return 0;
}

int update_grade(const unsigned long student_id, const unsigned long crouse_id, const double value)
{
    grade *grade_p = grades;
    const_grade *grade_end = grades + grade_number;

    for (grade_p = grades; grade_p != grade_end; grade_p++)
    {
        if (grade_p->student_id == student_id && grade_p->course_id == crouse_id)
        {
            break;
        }
    }

    if (grade_p == grade_end)
    {
        fprintf(stderr,
                "[Delete grade]\t"
                "delete grade fail, student with ID %ld does have crouse with ID %ld.\n",
                student_id, crouse_id
        );
        return -1;
    }

    grade_p->value = value;

    return 0;
}

void free_grades() { free(grades); }