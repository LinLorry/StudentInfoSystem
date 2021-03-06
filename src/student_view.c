#include <stdio.h>

#include <student_info_system/util.h>
#include <student_info_system/student.h>

#include <util.h>
#include <student_view.h>

int show_student();

int create_student();

int update_student_view();

int remove_student();

int student_manage()
{
    const menu menus[] = {
        {"show students", show_student},
        {"create student", create_student},
        {"update student", update_student_view},
        {"remove student", remove_student},
    };

    if (ADMIN_LEVEL_VALUE == get_current_level())
    {
        return show_menu(menus, 4, NULL);
    }
    else
    {
        return show_menu(menus, 1, NULL);
    }
}

int show_student()
{
    CLEAR();
    printf("Show Student:\n");
    print_students();
    printf("Press any key continue.");
    CLEAR_STDIN();

    return 0;
}

int create_student()
{
    char tmp_str[256];
    char name[STUDENT_NAME_BUFFER_SIZE];

    CLEAR();
    printf("Create Student:\n");

    sprintf(tmp_str, "Student name length must less then %d\n", STUDENT_NAME_MAX_LENGTH);
    input_str(
        name, STUDENT_NAME_MAX_LENGTH,
        "Please input student name: ",
        "Please input student name again: ",
        tmp_str);

    if (!add_student(name))
    {
        printf("Create student success\n");
    }

    printf("Press any key continue.");
    CLEAR_STDIN();

    return 0;
}

int update_student_view()
{
    int tmp;
    unsigned long id;
    char tmp_str[256];
    char name[STUDENT_NAME_BUFFER_SIZE];
    const_student_info *student_info_p;

    CLEAR();
    printf("Update Student:\n");
    print_students();

    printf("Please input student id which you want to update: ");
    tmp = scanf("%ld", &id);
    CLEAR_STDIN();

    while (tmp != 1 || id < 1 || (student_info_p = get_student(id)) == NULL)
    {
        printf("Please input valid id: ");

        tmp = scanf("%ld", &id);
        CLEAR_STDIN();
    }

    printf("User original info:\nname: %s\n", student_info_p->name);

    sprintf(tmp_str, "Student name length must less then %d\n", STUDENT_NAME_MAX_LENGTH);
    input_str(
        name, STUDENT_NAME_MAX_LENGTH,
        "Please input new name: ",
        "Please input new name again: ",
        tmp_str);

    if (!update_student(id, name))
    {
        printf("Update student success!\n");
    }

    printf("Press any key continue.");
    CLEAR_STDIN();

    return 0;
}

int remove_student()
{
    int tmp;
    long id;

    CLEAR();
    printf("Remove Student:\n");

    if (!print_students())
    {
        printf("Please input student id which you want to remove: ");
        tmp = scanf("%ld", &id);
        CLEAR_STDIN();

        while (tmp != 1 || id < 1)
        {
            printf("Please input valid id: ");

            tmp = scanf("%ld", &id);
            CLEAR_STDIN();
        }

        if (!delete_student(id))
        {
            printf("Delete student success!\n");
        }
    }

    printf("Press any key continue.");
    CLEAR_STDIN();

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
