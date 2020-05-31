#include <stdio.h>
#include <string.h>

#include <student_info_system/base.h>
#include <student_info_system/util.h>

int show_menu(const menu *menus, size_t menu_num, char *exist_str)
{
    int tmp;
    int choose = 0;
    short invalid_input = 1;
    char _exist_str[255], hint[40], r_hint[40];

    if (exist_str == NULL)
        sprintf(_exist_str, "%d. quit\n", menu_num + 1);
    else
        sprintf(_exist_str, "%d. %s\n", menu_num + 1, exist_str);

    sprintf(hint, "Please input your select: (1-%d): ", menu_num + 1);
    sprintf(r_hint, "Please input valid select: (1-%d): ", menu_num + 1);

    while (choose != menu_num)
    {
        CLEAR();

        for (int i = 1; i <= menu_num; ++i)
        {
            printf("%d. %s\n", i, menus[i - 1].content);
        }
        printf(_exist_str);
        printf(hint);

        while (1)
        {
            choose = getchar();
            CLEAR_STDIN_WITH_PRE(choose);
            choose -= '1';

            if (choose < menu_num && choose >= 0)
            {
                tmp = menus[choose].funtion();
                if (tmp)
                    return tmp;
                break;
            }
            else if (choose == menu_num)
                break;
            else
                printf(r_hint);
        }
    }

    return 0;
}

int input_str(
    char *str, const unsigned int max_length,
    const char *first_remind,
    const char *last_remind,
    const char *warn_remind
)
{
    int tmp;
    size_t index = 0;
    printf(first_remind);
    while (index < max_length && (tmp = getchar()) != '\n')
        str[index++] = (char)tmp;

    while (index == max_length && getchar() != '\n')
    {
        CLEAR_STDIN();

        index = 0;

        fprintf(stderr, warn_remind);
        printf(last_remind);
        while (index < max_length && (tmp = getchar()) != '\n')
            str[index++] = (char)tmp;
    }
    str[index] = '\0';

    return 0;
}
