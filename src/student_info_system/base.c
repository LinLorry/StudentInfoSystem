#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <student_info_system/base.h>
#include <student_info_system/user.h>

FILE *fp;
header heade;

user_info login_user = {0, 0, "", ""};

int open_system(const char *username, const char *password)
{
    unsigned long user_number;
    const_user_info *user_infos;
    const_user_info *user_info_p;
    const_user_info *user_infos_end;

    if ((fp = fopen(DATA_FILE_NAME, "rb")) == NULL)
    {
        perror("[Open system]\tOpen data file failed: ");
        exit(EXIT_FAILURE);
    }

    fread(&heade, sizeof(header), 1, fp);

    init_user_infos(fp, &heade);

    user_number = get_user_number();
    user_infos = get_user_infos();
    user_infos_end = user_infos + user_number;

    for (user_info_p = user_infos; user_info_p != user_infos_end; ++user_info_p)
    {
        if (!strcmp(user_info_p->username, username))
        {
            break;
        }
    }

    if (user_infos_end == user_info_p || strcmp(user_info_p->password, password))
    {
        fclose(fp);
        free_user_infos();
        return -1;
    }
    else
    {
        login_user = *user_info_p;
    }

    return 0;
}

int close_system()
{
    if (fclose(fp))
    {
        perror("[Close system]\tClose data file error: ");
        exit(EXIT_FAILURE);
    }

    if ((fp = fopen(DATA_TMP_FILE_NAME, "wb")) == NULL)
    {
        perror("[Close system]\t"
               "Open data tmp file failed: ");
        free_user_infos();
        exit(EXIT_FAILURE);
    }

    heade.user_number = get_user_number();

    fwrite(&heade, sizeof(header), 1, fp);
    fwrite(get_user_infos(), sizeof(user_info), get_user_number(), fp);

    if (fclose(fp))
    {
        perror("[Close system]\t"
               "Close tmp file error: ");
        free_user_infos();
        exit(EXIT_FAILURE);
    }

    if (rename(DATA_TMP_FILE_NAME, DATA_FILE_NAME))
    {
        perror("[Close system]\t"
               "Rename data tmp file to data file failed: ");
        free_user_infos();
        exit(EXIT_FAILURE);
    }

    free_user_infos();
}
