#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <student_info_system.h>

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
    else
    {
        printf("Usage: sis init\n");
        return 1;
    }

    return 0;
}
