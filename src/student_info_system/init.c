#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <student_info_system/base.h>
#include <student_info_system/init.h>
#include <student_info_system/user.h>

int init()
{
    FILE *fp;
    header h = {
        1, sizeof(header),
        0, sizeof(header) + sizeof(user_info),
        0, sizeof(header) + sizeof(user_info),
    };
    user_info admin_info = { 1, ADMIN_LEVEL_VALUE, "", "", };

    int tmp;
    size_t index = 0;

    CLEAR();
    printf("Initialize student info system...\n");

    if ((fp = fopen(DATA_TMP_FILE_NAME, "wb")) == NULL)
    {
        perror("Create tmp file failed: ");
        fprintf(stderr, "Initial student info system failed.\n"
                        "Exit.\n");
        exit(EXIT_FAILURE);
    }

    printf("Please input admin username: ");
    while (index < USERNAME_MAX_LENGTH && (tmp = getchar()) != '\n')
        admin_info.username[index++] = (char)tmp;

    while (index == USERNAME_MAX_LENGTH && getchar() != '\n')
    {
        CLEAR_STDIN();

        index = 0;

        fprintf(stderr, "Username length must less then %d\n", USERNAME_MAX_LENGTH);
        printf("Please input username again: ");
        while (index < USERNAME_MAX_LENGTH && (tmp = getchar()) != '\n')
            admin_info.username[index++] = (char)tmp;
    }
    admin_info.username[index] = '\0';

    index = 0;

    printf("Please input admin password: ");
    while (index < PASSWORD_MAX_LENGTH && (tmp = getchar()) != '\n')
        admin_info.password[index++] = (char)tmp;

    while (index == PASSWORD_MAX_LENGTH && getchar() != '\n')
    {
        CLEAR_STDIN();

        index = 0;

        fprintf(stderr, "Password length must less then %d\n", PASSWORD_MAX_LENGTH);
        printf("Please input password again: ");
        while (index < PASSWORD_MAX_LENGTH && (tmp = getchar()) != '\n')
            admin_info.password[index++] = (char)tmp;
    }
    admin_info.password[index] = '\0';

    fwrite(&h, sizeof(header), 1, fp);
    fwrite(&admin_info, sizeof(user_info), 1, fp);

    if (fclose(fp))
    {
        perror("Close tmp file error: ");
        fprintf(stderr, "Initial student info system failed.\n"
                        "Exit.\n");
        exit(EXIT_FAILURE);
    }

    printf("Save data tmp file success.\n");
    if (rename(DATA_TMP_FILE_NAME, DATA_FILE_NAME))
    {
        perror("Rename data tmp file to data file failed: ");
        fprintf(stderr, "Initial student info system failed.\n"
                        "Exit.\n");
        exit(EXIT_FAILURE);
    }
    printf("Rename data tmp file to data file success.\n"
           "Initial student info system success.\n");

    return 0;
}