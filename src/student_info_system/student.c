#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <student_info_system/base.h>
#include <student_info_system/types.h>
#include <student_info_system/student.h>

unsigned long student_number = 0;
unsigned long students_size = 0;
student_info *students = NULL;

int init_student_infos(FILE *fp, const header *head)
{
    size_t read;
    const unsigned long tmp = head->student_number;
    const unsigned long original_position = ftell(fp);

    if (fseek(fp, sizeof(header) + head->user_number * sizeof(user_info), SEEK_SET))
    {
        perror("[Init students]\tseek file position failed: ");
        fseek(fp, original_position, SEEK_SET);
        return -1;
    }

    students = (student_info *)malloc(tmp * sizeof(student_info));

    if (NULL == students)
    {
        perror("[Init students]\tmalloc student info memory failed: ");
        fseek(fp, original_position, SEEK_SET);
        return -1;
    }
    read = fread(students, sizeof(student_info), tmp, fp);

    if (tmp != read)
    {
        fprintf(stderr, "[Init students]\tstudent number error.\n");
        free(students);
        students = NULL;
        fseek(fp, original_position, SEEK_SET);
        return -1;
    }

    student_number = tmp;
    students_size = tmp;
    fseek(fp, original_position, SEEK_SET);
    return 0;
}

const_student_info *get_students()
{
    return students;
}

unsigned long get_student_number()
{
    return student_number;
}

int expand_students()
{
    student_info *tmp;
    const unsigned long expand_user_infos_size = students_size + EXPAND_STUDENT_SIZE;

    tmp = (student_info *)malloc(expand_user_infos_size * sizeof(student_info));
    if (NULL == tmp)
    {
        perror("[Expand students]\tmalloc students memory failed: ");
        return -1;
    }
    memcpy(tmp, students, student_number * sizeof(student_info));

    free(students);
    students = tmp;
    students_size = expand_user_infos_size;

    return 0;
}

int add_student(const char *name)
{
    int tmp;
    student_info *student_p;
    const_student_info *last_student;

    if (student_number == students_size && (tmp = expand_students()))
    {
        fprintf(stderr, "[Add student]\tadd student fail.\n");
        return tmp;
    }
    student_p = students + student_number;
    last_student = student_p - 1;

    student_number++;
    student_p->id = last_student->id + 1;
    strcpy(student_p->name, name);

    return 0;
}

int delete_student(const unsigned long id)
{
    unsigned long position = 0;
    student_info *student_p = students;
    const_student_info *last_student = students + (student_number - 1);

    if (id > last_student->id)
    {
        fprintf(stderr,
                "[Delete student]\t"
                "delete student fail, student with ID %ld does not exist.\n",
                id);
        return -1;
    }

    while (student_p < last_student && id != student_p->id)
    {
        student_p++;
        position++;
    }

    if (last_student == student_p && id != student_p->id)
    {
        fprintf(stderr,
                "[Delete student]\t"
                "delete student fail, student with ID %ld does not exist.\n",
                id);
        return -1;
    }

    memcpy(student_p, student_p + 1, (student_number - position) * sizeof(student_info));
    student_number--;

    return 0;
}

int update_student(const unsigned long id, const char *name)
{
    student_info *student_p = students;
    const_student_info *last_student = students + (student_number - 1);

    if (id > last_student->id)
    {
        fprintf(stderr,
                "[Update student]\t"
                "update student fail, student with ID %ld does not exist.\n",
                id);
        return -1;
    }

    while (student_p < last_student && id != student_p->id)
    {
        student_p++;
    }

    if (last_student == student_p && id != student_p->id)
    {
        fprintf(stderr,
                "[Update student]\t"
                "update student fail, student with ID %ld does not exist.\n",
                id);
        return -1;
    }

    strcpy(student_p->name, name);

    return 0;
}

void free_student_infos() { free(students); }

const_student_info *get_student(const unsigned long id)
{
    student_info const *student_info_end = students + student_number;
    for (student_info *student_info_p = students; student_info_p != student_info_end; student_info_p++)
    {
        if (id == student_info_p->id)
        {
            return student_info_p;
        }
    }

    return NULL;
}
