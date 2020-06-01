#include <stdio.h>

#include <student_info_system/util.h>
#include <student_info_system/student.h>
#include <student_info_system/course.h>
#include <student_info_system/grade.h>

#include <util.h>
#include <grade_view.h>

int show_grade();

int create_grade();

int remove_grade();

int grade_manage()
{
    const menu menus[] = {
        {"show grades", show_grade},
        {"create grade", create_grade},
        {"remove grade", remove_grade}
    };

    if (ADMIN_LEVEL_VALUE == get_current_level())
    {
        return show_menu(menus, 3, NULL);
    }
    else
    {
        return show_menu(menus, 1, NULL);
    }
}

int show_grade()
{
    CLEAR();
    print_grades();
    printf("Press any key continue.");
    CLEAR_STDIN();

    return 0;
}

int create_grade()
{
    int tmp;
    unsigned long student_id, course_id;
    double value;
    size_t index;

    CLEAR();
    printf("Students:\n");
    print_students();
    printf("Please student id: ");

    tmp = scanf("%ld", &student_id);
    CLEAR_STDIN();

    while (tmp != 1 || student_id < 1)
    {
        printf("Please input valid student id: ");

        tmp = scanf("%ld", &student_id);
        CLEAR_STDIN();
    }

    printf("Course:\n");
    print_courses();
    printf("Please course id: ");

    tmp = scanf("%ld", &course_id);
    CLEAR_STDIN();

    while (tmp != 1 || course_id < 1)
    {
        printf("Please input valid course id: ");

        tmp = scanf("%ld", &course_id);
        CLEAR_STDIN();
    }

    printf("Please input his grade: ");
    tmp = scanf("%lf", &value);
    CLEAR_STDIN();

    while (tmp != 1 || value < 0)
    {
        printf("Please input valid value: ");

        tmp = scanf("%lf", &value);
        CLEAR_STDIN();
    }

    if (!add_grade(student_id, course_id, value))
    {
        printf("Create grade success\n");
    }

    printf("Press any key continue.");
    CLEAR_STDIN();

    return 0;
}

int remove_grade()
{
    unsigned long student_id, course_id;

    int tmp;
    long id;

    CLEAR();

    if (!print_grades())
    {
        printf("Please input student id: ");

        tmp = scanf("%ld", &student_id);
        CLEAR_STDIN();

        while (tmp != 1 || student_id < 1)
        {
            printf("Please input valid student id: ");

            tmp = scanf("%ld", &student_id);
            CLEAR_STDIN();
        }

        printf("Please input course id: ");

        tmp = scanf("%ld", &course_id);
        CLEAR_STDIN();

        while (tmp != 1 || course_id < 1)
        {
            printf("Please input valid course id: ");

            tmp = scanf("%ld", &course_id);
            CLEAR_STDIN();
        }

        if (!delete_grade(student_id, course_id))
        {
            printf("Delete grade success!\n");
        }
    }

    printf("Press any key continue.");
    CLEAR_STDIN();

    return 0;
}

int print_grades()
{
    const unsigned long grade_number = get_grade_number();
    const_grade *grades = get_grades();
    const_grade *grade_end = grades + grade_number;
    const_grade *grade_p;
    const_student_info *student_info_p;
    const_course *course_p;

    if (grade_number == 0)
    {
        printf("Don't have grade!\n");
        return -1;
    }

    printf("+---------------------------------------------------------------------+\n");
    printf("| student id\t  student name\tcourse id\tcourse name\t grade|\n");
    printf("+---------------------------------------------------------------------+\n");

    for (grade_p = grades; grade_p != grade_end; ++grade_p)
    {
        student_info_p = get_student(grade_p->student_id);
        course_p = get_course(grade_p->course_id);
        printf("|%11ld\t%14s\t%9ld\t%11s\t%6.2lf|\n",
               student_info_p->id, student_info_p->name,
               course_p->id, course_p->name,
               grade_p->value);
    }
    printf("+---------------------------------------------------------------------+\n");

    return 0;
}
