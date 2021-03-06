#include <stdio.h>

#include <student_info_system/util.h>
#include <student_info_system/user.h>

#include <util.h>
#include <user_view.h>

const char admin_str[] = "Admin";
const char user_str[] = "User";

int show_user();

int create_user();

int update_user_view();

int change_password_view();

int remove_user();

int user_manage()
{
    const menu menus[] = {
        {"show users", show_user},
        {"create user", create_user},
        {"update user", update_user_view},
        {"change password", change_password_view},
        {"remove user", remove_user},
    };

    if (ADMIN_LEVEL_VALUE == get_current_level())
    {
        return show_menu(menus, 5, NULL);
    }
    else
    {
        return show_menu(menus, 1, NULL);
    }
}

int show_user()
{
    CLEAR();
    printf("Show User:\n");
    print_users();
    printf("Press any key continue.");
    CLEAR_STDIN();

    return 0;
}

int create_user()
{
    int tmp;
    char tmp_str[256];
    int level;
    char username[USERNAME_BUFFER_SIZE];
    char password[PASSWORD_BUFFER_SIZE];

    CLEAR();
    printf("Create User:\n");

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

int update_user_view()
{
    int tmp;
    unsigned long id;
    char tmp_str[256];
    unsigned char level;
    char username[USERNAME_BUFFER_SIZE];
    const_user_info *user_info_p;

    CLEAR();
    printf("Update User:\n");
    print_users();

    printf("Please input user id which you want to update: ");
    tmp = scanf("%ld", &id);
    CLEAR_STDIN();

    while (tmp != 1 || id < 1 || (user_info_p = get_user(id)) == NULL)
    {
        printf("Please input valid id: ");

        tmp = scanf("%ld", &id);
        CLEAR_STDIN();
    }

    level = user_info_p->level;

    printf(
        "User original info:\nlevel: %s\nusername: %s\n",
        level == ADMIN_LEVEL_VALUE ? admin_str : user_str,
        user_info_p->username);

    if (level == ADMIN_LEVEL_VALUE)
    {
        printf("Change this user type to user[y/N]?");
        tmp = getchar();
        CLEAR_STDIN_WITH_PRE(tmp);
        if (tmp == 'y' || tmp == 'Y')
        {
            level = USER_LEVEL_VALUE;
        }
    }
    else
    {
        printf("Change this user type to admin[y/N]?");
        tmp = getchar();
        CLEAR_STDIN_WITH_PRE(tmp);
        if (tmp == 'y' || tmp == 'Y')
        {
            level = ADMIN_LEVEL_VALUE;
        }
    }

    sprintf(tmp_str, "Username length must less then %d\n", USERNAME_MAX_LENGTH);
    input_str(
        username, USERNAME_MAX_LENGTH,
        "Please input new username: ",
        "Please input new username again: ",
        tmp_str
    );

    if (!update_user(id, level, username, NULL))
    {
        printf("Update user success!\n");
    }

    printf("Press any key continue.");
    CLEAR_STDIN();

    return 0;
}

int change_password_view()
{
    int tmp;
    unsigned long id;
    char tmp_str[256];
    char password[PASSWORD_BUFFER_SIZE];

    CLEAR();
    printf("Change Password:\n");
    print_users();

    printf("Please input user id which you want to update: ");
    tmp = scanf("%ld", &id);
    CLEAR_STDIN();

    while (tmp != 1 || id < 1)
    {
        printf("Please input valid id: ");

        tmp = scanf("%ld", &id);
        CLEAR_STDIN();
    }

    sprintf(tmp_str, "Password length must less then %d\n", PASSWORD_MAX_LENGTH);
    input_str(
        password, PASSWORD_MAX_LENGTH,
        "Please input new password: ",
        "Please input new password again: ",
        tmp_str
    );

    if (!update_user(id, NULL_LEVEL_VALUE, NULL, password))
    {
        printf("Update password success!\n");
    }

    printf("Press any key continue.");
    CLEAR_STDIN();
    return 0;
}

int remove_user()
{
    int tmp;
    long id;
    const unsigned long current_id = get_current_id();

    CLEAR();
    printf("Remove User:\n");

    print_users();

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
