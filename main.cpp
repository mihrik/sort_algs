#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "sort_algs.h"

const int LENGTH = 8000;
const char *ONEGIN = "onegin.txt";

int main(void)
{
    size_t nlines = 0;
    char *text[LENGTH] = {};
    char *real_text[LENGTH] = {};
    nlines = read_text("onegin.txt", text);
    copy_arr(real_text, text, nlines);

    quick_sort(0, nlines - 1, text, my_strcmp, sizeof(text[0]));
    print_strings_array(text, nlines);

    qsort(text, nlines, sizeof(text[0]), my_rewind_strcmp);
    print_strings_array(text, nlines);

    print_strings_array(real_text, nlines);

    for (size_t i = 0; i <= nlines; i++)
    {
        free(text[i]);
    }

    return 0;
}

