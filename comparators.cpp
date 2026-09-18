#include "sort_algs.h"
#include <ctype.h>
#include <assert.h>

int compare_int_up(const void *val1, const void *val2)
{
    assert(val1);
    assert(val2);

    return *(const int *)val1 - *(const int *)val2;
}

int compare_int_down(const void *val1, const void *val2)
{
    assert(val1);
    assert(val2);

    return *(const int *)val2 - *(const int *)val1;
}

int sum_of_digits(int num)
{
    int sum = 0;
    num = (num < 0) ? -num : num;

    while (num > 0)
    {
        sum += num % 10;
        num /= 10;
    }

    return sum;
}

int compare_sod_up(const void *val1, const void *val2)
{
    assert(val1);
    assert(val2);

    return sum_of_digits(*(const int *)val1) - sum_of_digits(*(const int *)val2);
}

int compare_sod_down(const void *val1, const void *val2)
{
    assert(val1);
    assert(val2);

    return sum_of_digits(*(const int *)val2) - sum_of_digits(*(const int *)val1);
}

int compare_double_up(const void *val1, const void *val2)
{
    assert(val1);
    assert(val2);

    double a = *(const double *)val1;
    double b = *(const double *)val2;

    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

int compare_double_down(const void *val1, const void *val2)
{
    assert(val1);
    assert(val2);

    double a = *(const double *)val1;
    double b = *(const double *)val2;

    if (a < b) return 1;
    if (a > b) return -1;
    return 0;
}

int my_rewind_strcmp(const void *str1, const void *str2)
{
    assert(str1);
    assert(str2);

    const char *ptr1 = *(char * const *)str1;
    int len1 = (int)my_strlen(ptr1) - 1;
    const char *ptr2 = *(char * const *)str2;
    int len2 = (int)my_strlen(ptr2) - 1;

    while (1)
    {
        while (len1 >= 0 && !isalpha(ptr1[len1]))
            len1--;

        while (len2 >= 0 && !isalpha(ptr2[len2]))
            len2--;

        if (len1 < 0 || len2 < 0)
        {
            if (len1 < 0 && len2 < 0)
                return 0;

            return (len1 < 0) ? -1 : 1;
        }

        if (tolower(ptr1[len1]) != tolower(ptr2[len2]))
        {
            return tolower(ptr1[len1]) - tolower(ptr2[len2]);
        }

        len1--;
        len2--;
    }
}