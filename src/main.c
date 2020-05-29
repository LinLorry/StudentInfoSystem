#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <student_info_system.h>

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
            while (getchar() != '\n')
                continue;
            return init();
        }
    }
    else if (argc == 3)
    {
        if (open_system(args[1], args[2]))
        {
            printf("username: %s, password: %s\n", args[1], args[2]);
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

int main_view()
{
    const menu menus[1] = {
        {"user manage", user_manage}
    };
    return show_menu(menus, 1, NULL);
}

int show_user();

int create_user();

int user_manage()
{
    const menu menus[] = {
        {"show users", show_user},
        {"create user", create_user}
    };
    return show_menu(menus, 2, NULL);
}

int show_user()
{
    const unsigned long user_number = get_user_number();
    const_user_info *user_infos = get_user_infos();
    const_user_info *user_info_end = user_infos + user_number;
    const_user_info *user_info_p;

    const char admin_str[] = "Admin";
    const char user_str[] = "User";

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
    while (getchar() != '\n')
        continue;

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

    CLEAR_STDIN(tmp);

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

    tmp = add_user(level, username, password);
    if (tmp)
    {
        return tmp;
    }

    printf("Create user success\nPress any key continue.");
    while (getchar() != '\n')
        continue;

    return 0;
}