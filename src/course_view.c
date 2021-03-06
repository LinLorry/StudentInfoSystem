#include <stdio.h>

#include <student_info_system/util.h>
#include <student_info_system/course.h>

#include <util.h>
#include <course_view.h>

int show_course();

int create_course();

int update_course_view();

int remove_course();

int course_manage()
{
    const menu menus[] = {
        {"show courses", show_course},
        {"create course", create_course},
        {"update course", update_course_view},
        {"remove course", remove_course},
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

int show_course()
{
    CLEAR();
    printf("Show Course:\n");
    print_courses();
    printf("Press any key continue.");
    CLEAR_STDIN();

    return 0;
}

int create_course()
{
    char tmp_str[256];
    char name[COURSE_NAME_BUFFER_SIZE];

    CLEAR();
    printf("Create Course:\n");

    sprintf(tmp_str, "Course name length must less then %d\n", COURSE_NAME_MAX_LENGTH);
    input_str(
        name, COURSE_NAME_MAX_LENGTH,
        "Please input course name: ",
        "Please input course name again: ",
        tmp_str
    );

    if (!add_course(name))
    {
        printf("Create course success\n");
    }

    printf("Press any key continue.");
    CLEAR_STDIN();

    return 0;
}

int update_course_view()
{
    int tmp;
    unsigned long id;
    char tmp_str[256];
    char name[COURSE_NAME_BUFFER_SIZE];
    const_course *course_info_p;

    CLEAR();
    printf("Update Course:\n");
    print_courses();

    printf("Please input course id which you want to update: ");
    tmp = scanf("%ld", &id);
    CLEAR_STDIN();    

    while (tmp != 1 || id < 1 || (course_info_p = get_course(id)) == NULL)
    {
        printf("Please input valid id: ");

        tmp = scanf("%ld", &id);
        CLEAR_STDIN();
    }

    printf("User original info:\nname: %s\n", course_info_p->name);

    sprintf(tmp_str, "Course name length must less then %d\n", COURSE_NAME_MAX_LENGTH);
    input_str(
        name, COURSE_NAME_MAX_LENGTH,
        "Please input new name: ",
        "Please input new name again: ",
        tmp_str);

    if (!update_course(id, name))
    {
        printf("Update course success!\n");
    }

    printf("Press any key continue.");
    CLEAR_STDIN();

    return 0;
}

int remove_course()
{
    int tmp;
    long id;

    CLEAR();
    printf("Remove Course:\n");

    if (!print_courses())
    {
        printf("Please input course id which you want to remove: ");
        tmp = scanf("%ld", &id);
        CLEAR_STDIN();

        while (tmp != 1 || id < 1)
        {
            printf("Please input valid id: ");

            tmp = scanf("%ld", &id);
            CLEAR_STDIN();
        }

        if (!delete_course(id))
        {
            printf("Delete course success!\n");
        }
    }

    printf("Press any key continue.");
    CLEAR_STDIN();

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
