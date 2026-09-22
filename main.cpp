#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "sort_algs.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "colors.h"

int main(int argc, const char * const argv[])
{
    if (argc < 2)
    {
        PRINT_COLOR(EXTRA_RED, "Не указано имя файла\n");
        return ABSENCE_OF_FILE;
    }
    // TODO char **onegin to struct
    // TODO assert security
    // TODO argv security
    // TODO KR у меня срабатывает автодоплнение скобок и кавычек применял настройк из гайда для новичков помогите
    // TODO readme

    size_t len = 0;
    char *text = NULL;
    if (check_error(text = read_text(argv[1])))
    {
        PRINT_COLOR(EXTRA_RED, "Ошибка обработки входного файла либо выделения памяти\n");
        return MAKE_FILE_ERROR;
    }
    str_data *onegin = NULL;
    if (check_error(onegin = getlines(text, &len)))
    {
        PRINT_COLOR(EXTRA_RED, "Ошибка выделения памяти\n");
        return MEMORY_ALLOCATION_ERROR;
    }

    quick_sort(0, len - 1, onegin, my_straight_strcmp, sizeof(onegin[0]));

    print_struct_array(onegin, len);

    qsort(onegin, len, sizeof(onegin[0]), my_rewind_strcmp);

    print_struct_array(onegin, len);

    quick_sort(0, len - 1, onegin, compare_pointers_up, sizeof(onegin[0]));

    print_struct_array(onegin, len);

    free(onegin);
    onegin = NULL;
    free(text);
    text = NULL;

    return 0;
}

