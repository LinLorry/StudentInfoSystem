#include <stdio.h>

#include <student_info_system/user.h>
#include <student_info_system/student.h>
#include <student_info_system/course.h>
#include <student_info_system/grade.h>

#include <util.h>

const char admin_str[] = "Admin";
const char user_str[] = "User";

int print_users()
{
    const unsigned long user_number = get_user_number();
    const_user_info *user_infos = get_user_infos();
    const_user_info *user_info_end = user_infos + user_number;
    const_user_info *user_info_p;

    printf("+-------------------------+\n");
    printf("|  id\t  type\t  username|\n");
    printf("+-------------------------+\n");

    for (user_info_p = user_infos; user_info_p != user_info_end; ++user_info_p)
    {
        printf(
            "|%4ld\t%6s\t%10s|\n",
            user_info_p->id,
            user_info_p->level == ADMIN_LEVEL_VALUE ? admin_str : user_str,
            user_info_p->username);
    }
    printf("+-------------------------+\n");

    return 0;
}

int print_students()
{
    const unsigned long student_number = get_student_number();
    const_student_info *const students = get_students();
    const_student_info *const student_end = students + student_number;
    const_student_info *student_p;

    if (student_number == 0)
    {
        printf("Don't have student!\n");
        return -1;
    }

    printf("+-----------------+\n");
    printf("|  Id\t      Name|\n");
    printf("+-----------------+\n");

    for (student_p = students; student_p != student_end; ++student_p)
    {
        printf("|%4ld\t%10s|\n", student_p->id, student_p->name);
    }
    printf("+-----------------+\n");

    return 0;
}

int print_courses()
{
    const unsigned long course_number = get_course_number();
    const_course *courses = get_courses();
    const_course *course_end = courses + course_number;
    const_course *course_p;

    if (course_number == 0)
    {
        printf("Don't have course!\n");
        return -1;
    }

    printf("+-----------------+\n");
    printf("|  Id\t      Name|\n");
    printf("+-----------------+\n");

    for (course_p = courses; course_p != course_end; ++course_p)
    {
        printf("|%4ld\t%10s|\n", course_p->id, course_p->name);
    }
    printf("+-----------------+\n");
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
