#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <student_info_system.h>

#include <util.h>

int main_view();

int main(int argc, char *args[])
{
    int input;
    if (argc == 2 && !strcmp("init", args[1]))
    {
        if (access(DATA_FILE_NAME, F_OK))
            return init();

        printf("Local data file exist, whether to override it?(y/N)");
        input = getchar();

        if (input == 'y' || input == 'Y')
        {
            CLEAR_STDIN();
            return init();
        }
    }
    else if (argc == 3)
    {
        if (open_system(args[1], args[2]))
        {
            fprintf(stderr, "[Login]: Access denied for user '%s'\n", args[1]);
            return -1;
        }

        main_view();

        close_system();
    }
    else
    {
        printf("Usage: sis init or\n"
               "       sis [username] [password]\n");
        return 1;
    }

    return 0;
}

int user_manage();

int student_manage();

int course_manage();

int main_view()
{
    const menu menus[3] = {
        {"user manage", user_manage},
        {"student manage", student_manage},
        {"course manage", course_manage}
    };
    return show_menu(menus, 3, NULL);
}

int show_user();

int create_user();

int remove_user();

int user_manage()
{
    const menu menus[] = {
        {"show users", show_user},
        {"create user", create_user},
        {"remove user", remove_user}
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

int show_user()
{
    const unsigned long user_number = get_user_number();
    const_user_info *user_infos = get_user_infos();
    const_user_info *user_info_end = user_infos + user_number;
    const_user_info *user_info_p;

    const char admin_str[] = "Admin";
    const char user_str[] = "User";

    CLEAR();

    printf("+-------------------------+\n");
    printf("| Id \t Type \t Username |\n");
    printf("+-------------------------+\n");

    for (user_info_p = user_infos; user_info_p != user_info_end; ++user_info_p)
    {
        printf(
            "|%4ld\t%6s\t%10s|\n",
            user_info_p->id,
            user_info_p->level == ADMIN_LEVEL_VALUE ? admin_str : user_str,
            user_info_p->username
        );
    }
    printf("+-------------------------+\n");

    printf("Press any key continue.");
    CLEAR_STDIN();

    return 0;
}

int create_user()
{
    int tmp;
    char tmp_str[256];
    size_t index;
    int level;
    char username[USERNAME_BUFFER_SIZE];
    char password[PASSWORD_BUFFER_SIZE];

    CLEAR();

    printf("What type user you want to create(Admin or User)? [a/U]: ");
    tmp = getchar();

    CLEAR_STDIN_WITH_PRE(tmp);

    if (tmp == 'a' || tmp == 'A')
    {
        level = ADMIN_LEVEL_VALUE;
    }
    else
    {
        level = USER_LEVEL_VALUE;
    }

    sprintf(tmp_str, "Username length must less then %d\n", USERNAME_MAX_LENGTH);
    input_str(
        username, USERNAME_MAX_LENGTH,
        "Please input new username: ",
        "Please input new username again: ",
        tmp_str);

    sprintf(tmp_str, "Password length must less then %d\n", PASSWORD_MAX_LENGTH);
    input_str(
        password, PASSWORD_MAX_LENGTH,
        "Please input new user password: ",
        "Please input new user password again: ",
        tmp_str);

    if (!add_user(level, username, password))
    {
        printf("Create user success\n");
    }

    printf("Press any key continue.");
    CLEAR_STDIN();

    return 0;
}

int remove_user()
{
    const unsigned long current_id = get_current_id();
    const unsigned long user_number = get_user_number();
    const_user_info *const user_infos = get_user_infos();
    const_user_info *const user_info_end = user_infos + user_number;
    const_user_info *user_info_p;

    const char admin_str[] = "Admin";
    const char user_str[] = "User";

    int tmp;
    long id;

    printf("+-------------------------+\n");
    printf("| Id \t Type \t Username |\n");
    printf("+-------------------------+\n");

    for (user_info_p = user_infos; user_info_p != user_info_end; ++user_info_p)
    {
        printf(
            "|%4ld\t%6s\t%10s|\n",
            user_info_p->id,
            user_info_p->level == ADMIN_LEVEL_VALUE ? admin_str : user_str,
            user_info_p->username
        );
    }
    printf("+-------------------------+\n");

    printf("Please input user id which you want to remove: ");
    tmp = scanf("%ld", &id);
    CLEAR_STDIN();

    while (tmp != 1 || id < 1 || id == current_id)
    {
        if (id == current_id)
        {
            printf("You can't delete yourself!\n");
        }

        printf("Please input valid id: ");

        tmp = scanf("%ld", &id);
        CLEAR_STDIN();
    }

    if (!delete_user(id))
    {
        printf("Delete user success!\n");
    }

    printf("Press any key continue.");
    CLEAR_STDIN();

    return 0;
}

int show_student();

int create_student();

int remove_student();

int student_manage()
{
    const menu menus[] = {
        {"show students", show_student},
        {"create student", create_student},
        {"remove student", remove_student}
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

int show_student()
{
    CLEAR();
    print_students();
    printf("Press any key continue.");
    CLEAR_STDIN();

    return 0;
}

int create_student()
{
    char tmp_str[256];
    size_t index;
    char name[STUDENT_NAME_BUFFER_SIZE];

    CLEAR();

    sprintf(tmp_str, "Student name length must less then %d\n", STUDENT_NAME_MAX_LENGTH);
    input_str(
        name, STUDENT_NAME_MAX_LENGTH,
        "Please input student name: ",
        "Please input student name again: ",
        tmp_str
    );

    if (!add_student(name))
    {
        printf("Create student success\n");
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

int show_course();

int create_course();

int remove_course();

int course_manage()
{
    const menu menus[] = {
        {"show courses", show_course},
        {"create course", create_course},
        {"remove course", remove_course}
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

int show_course()
{
    CLEAR();
    print_courses();
    printf("Press any key continue.");
    CLEAR_STDIN();

    return 0;
}

int create_course()
{
    char tmp_str[256];
    size_t index;
    char name[STUDENT_NAME_BUFFER_SIZE];

    CLEAR();

    sprintf(tmp_str, "Student name length must less then %d\n", STUDENT_NAME_MAX_LENGTH);
    input_str(
        name, STUDENT_NAME_MAX_LENGTH,
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

int remove_course()
{
    int tmp;
    long id;

    CLEAR();

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
