#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <student_info_system/base.h>
#include <student_info_system/types.h>
#include <student_info_system/course.h>

unsigned long course_number = 0;
unsigned long courses_size = 0;
course *courses = NULL;

int init_courses(FILE *fp, const header *head)
{
    size_t read;
    const unsigned long tmp = head->course_number;
    const unsigned long original_position = ftell(fp);
    const unsigned long offset = sizeof(header) +
                                 head->user_number * sizeof(user_info) +
                                 head->student_number * sizeof(student_info);

    if (fseek(fp, offset, SEEK_SET))
    {
        perror("[Init courses]\tseek file position failed: ");
        fseek(fp, original_position, SEEK_SET);
        return -1;
    }

    courses = (course *)malloc(tmp * sizeof(course));

    if (NULL == courses)
    {
        perror("[Init courses]\tmalloc course info memory failed: ");
        fseek(fp, original_position, SEEK_SET);
        return -1;
    }
    read = fread(courses, sizeof(course), tmp, fp);

    if (tmp != read)
    {
        fprintf(stderr, "[Init courses]\tcourse number error.\n");
        free(courses);
        courses = NULL;
        fseek(fp, original_position, SEEK_SET);
        return -1;
    }

    course_number = tmp;
    courses_size = tmp;
    fseek(fp, original_position, SEEK_SET);
    return 0;
}

const_course *get_courses()
{
    return courses;
}

unsigned long get_course_number()
{
    return course_number;
}

int expand_courses()
{
    course *tmp;
    const unsigned long expand_course_infos_size = courses_size + EXPAND_COURSE_SIZE;

    tmp = (course *)malloc(expand_course_infos_size * sizeof(course));
    if (NULL == tmp)
    {
        perror("[Expand courses]\tmalloc courses memory failed: ");
        return -1;
    }
    memcpy(tmp, courses, course_number * sizeof(course));

    free(courses);
    courses = tmp;
    courses_size = expand_course_infos_size;

    return 0;
}

int add_course(const char *name)
{
    int tmp;
    course *course_p;
    const_course *last_course;

    if (course_number == courses_size && (tmp = expand_courses()))
    {
        fprintf(stderr, "[Add course]\tadd course fail.\n");
        return tmp;
    }
    course_p = courses + course_number;
    last_course = course_p - 1;

    course_number++;
    course_p->id = last_course->id + 1;
    strcpy(course_p->name, name);

    return 0;
}

int delete_course(const unsigned long id)
{
    unsigned long position = 0;
    course *course_p = courses;
    const_course *last_course = courses + (course_number - 1);

    if (id > last_course->id)
    {
        fprintf(stderr,
                "[Delete course]\t"
                "delete course fail, course with ID %ld does not exist.\n",
                id);
        return -1;
    }

    while (course_p < last_course && id != course_p->id)
    {
        course_p++;
        position++;
    }

    if (last_course == course_p && id != course_p->id)
    {
        fprintf(stderr,
                "[Delete course]\t"
                "delete course fail, course with ID %ld does not exist.\n",
                id);
        return -1;
    }

    memcpy(course_p, course_p + 1, (course_number - position) * sizeof(course));
    course_number--;

    return 0;
}

int update_course(const unsigned long id, const char *name)
{
    course *course_p = courses;
    const_course *last_course = courses + (course_number - 1);

    if (id > last_course->id)
    {
        fprintf(stderr,
                "[Update course]\t"
                "update course fail, course with ID %ld does not exist.\n",
                id);
        return -1;
    }

    while (course_p < last_course && id != course_p->id)
    {
        course_p++;
    }

    if (last_course == course_p && id != course_p->id)
    {
        fprintf(stderr,
                "[Update course]\t"
                "update course fail, course with ID %ld does not exist.\n",
                id);
        return -1;
    }

    strcpy(course_p->name, name);

    return 0;
}

void free_courses() { free(courses); }
