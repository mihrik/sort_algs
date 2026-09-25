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

    const str_data *ptr1 = (const str_data *)str1;
    long len1 = ptr1->len;
    const str_data *ptr2 = (const str_data *)str2;
    long len2 = ptr2->len;

    while (1)
    {
        while (len1 >= 0 && !isalpha(ptr1->line[len1]))
            len1--;

        while (len2 >= 0 && !isalpha(ptr2->line[len2]))
            len2--;

        if (len1 < 0 || len2 < 0)
        {
            if (len1 < 0 && len2 < 0)
                return 0;

            return (len1 < 0) ? -1 : 1;
        }

        if (tolower(ptr1->line[len1]) != tolower(ptr2->line[len2]))
        {
            return tolower(ptr1->line[len1]) - tolower(ptr2->line[len2]);
        }

        len1--;
        len2--;
    }
}

int my_straight_strcmp(const void *str1, const void *str2)
{
    assert(str1);
    assert(str2);

    const str_data *ptr1 = (const str_data *)str1;
    long len1 = ptr1->len;
    long i = 0, j = 0;
    const str_data *ptr2 = (const str_data *)str2;
    long len2 = ptr2->len;

    while (1)
    {
        while (i < len1 && !isalpha(ptr1->line[i]))
            i++;

        while (j < len2 && !isalpha(ptr2->line[j]))
            j++;

        if (j >= len2 || i >= len1)
        {
            if (i >= len1 && j >= len2)
                return 0;

            return (i >= len1) ? -1 : 1;
        }

        if (tolower(ptr1->line[i]) != tolower(ptr2->line[j]))
        {
            return tolower(ptr1->line[i]) - tolower(ptr2->line[j]);
        }

        i++;
        j++;
    }
}

int compare_pointers_up(const void *val1, const void *val2)
{
    assert(val1);
    assert(val2);

    const str_data *ptr1 = (const str_data *)val1;
    const str_data *ptr2 = (const str_data *)val2;

    return int(ptr1->line - ptr2->line);
}