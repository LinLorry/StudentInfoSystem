#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <student_info_system/base.h>
#include <student_info_system/types.h>
#include <student_info_system/user.h>
#include <student_info_system/student.h>
#include <student_info_system/course.h>

FILE *fp;
header heade;

user_info login_user = {0, 0, "", ""};

void free_all()
{
    free_user_infos();
    free_student_infos();
    free_courses();
}

int open_system(const char *username, const char *password)
{
    int tmp;
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

    tmp = init_user_infos(fp, &heade);

    if (tmp)
    {
        fprintf(stderr, "[Open system] init user info fail.\n");
        fclose(fp);
        free_user_infos();
        exit(EXIT_FAILURE);
    }

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
    tmp = init_student_infos(fp, &heade);
    if (tmp)
    {
        fprintf(stderr, "[Open system] init student info fail.\n");
        fclose(fp);
        free_all();
        exit(EXIT_FAILURE);
    }
    tmp = init_courses(fp, &heade);
    if (tmp)
    {
        fprintf(stderr, "[Open system] init course info fail.\n");
        fclose(fp);
        free_all();
        exit(EXIT_FAILURE);
    }

    return 0;
}

unsigned char get_current_level() { return login_user.level; }

unsigned long get_current_id() { return login_user.id; }

int close_system()
{
    if (fclose(fp))
    {
        perror("[Close system]\tClose data file error: ");
        return -1;
    }

    if ((fp = fopen(DATA_TMP_FILE_NAME, "wb")) == NULL)
    {
        perror("[Close system]\t"
               "Open data tmp file failed: ");
        free_user_infos();
        return -1;
    }

    heade.user_number = get_user_number();
    heade.student_number = get_student_number();
    heade.course_number = get_course_number();

    if (fwrite(&heade, sizeof(header), 1, fp) != 1)
    {
        fprintf(stderr, "[Close system]\twrite head fail: %s\n", strerror(ferror(fp)));
        fclose(fp);
        free_all();
        return -1;
    }
    if (fwrite(get_user_infos(), sizeof(user_info), heade.user_number, fp) != heade.user_number)
    {
        fprintf(stderr, "[Close system]\twrite user info fail: %s\n", strerror(ferror(fp)));
        fclose(fp);
        free_all();
        return -1;
    }
    if (fwrite(get_students(), sizeof(student_info), heade.student_number, fp) != heade.student_number)
    {
        fprintf(stderr, "[Close system]\twrite student info fail: %s\n", strerror(ferror(fp)));
        fclose(fp);
        free_all();
        return -1;
    }
    if (fwrite(get_courses(), sizeof(course), heade.course_number, fp) != heade.course_number)
    {
        fprintf(stderr, "[Close system]\twrite course info fail: %s\n", strerror(ferror(fp)));
        fclose(fp);
        free_all();
        return -1;
    }

    if (fclose(fp))
    {
        perror("[Close system]\t"
               "Close tmp file error: ");
        free_all();
        return -1;
    }

    if (rename(DATA_TMP_FILE_NAME, DATA_FILE_NAME))
    {
        perror("[Close system]\t"
               "Rename data tmp file to data file failed: ");
        free_all();
        return -1;
    }

    free_all();
    return 0;
}
