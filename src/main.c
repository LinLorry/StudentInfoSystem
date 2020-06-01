#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <student_info_system.h>

#include <user_view.h>
#include <student_view.h>
#include <course_view.h>
#include <grade_view.h>

int main(int argc, char *args[])
{
    const menu menus[4] = {
        {"user manage", user_manage},
        {"student manage", student_manage},
        {"course manage", course_manage},
        {"grade manage", grade_manage},
    };
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

        show_menu(menus, 4, NULL);

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
