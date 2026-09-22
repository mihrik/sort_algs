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

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        PRINT_COLOR(EXTRA_RED, "Не указано имя файла\n");
        return 13;
    }

    size_t len = 0;
    char *text = NULL;
    if (check_error(text = read_text(argv[1])))
        {
            PRINT_COLOR(EXTRA_RED, "Ошибка обработки входного файла либо выделения памяти\n");
            return 13;
        }
    char **onegin = NULL;
    if (check_error(onegin = getlines(text, &len)))
        {
            PRINT_COLOR(EXTRA_RED, "Ошибка выделения памяти\n");
            return 13;
        }

    quick_sort(0, len - 1, onegin, my_strcmp, sizeof(onegin[0]));

    print_strings_array(onegin, len);

    qsort(onegin, len, sizeof(onegin[0]), my_rewind_strcmp);

    print_strings_array(onegin, len);

    quick_sort(0, len - 1, onegin, compare_int_up, sizeof(char **));

    print_strings_array(onegin, len);

    free(onegin);
    onegin = NULL;
    free(text);
    text = NULL;

    return 0;
}

