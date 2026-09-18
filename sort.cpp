#include <stdio.h>
#include <assert.h>
#include "sort_algs.h"
#include "colors.h"

size_t quick_alg(void *arr_part, size_t low, size_t high, int (*compare_func)(const void *val1, const void *val2), size_t elem_size)
{
    assert(arr_part);
    assert(compare_func);

    size_t pivot_position = (low + high) / 2;
    size_t len = high - low + 1;

    switch(len)
    {
        case 2: sort_two((char *)arr_part + low * elem_size, (char *)arr_part + high * elem_size, compare_func, elem_size);
                break;
        case 3: sort_three((char *)arr_part + low * elem_size, (char *)arr_part + (low + 1) * elem_size, (char *)arr_part + (low + 2) * elem_size, compare_func, elem_size);
                break;
       default: sort_more(low, high, arr_part, elem_size, &pivot_position, compare_func);
    }

    return pivot_position;
}

void quick_sort(size_t low, size_t high, void *to_sort, int (*compare_func)(const void *val1, const void *val2), size_t elem_size)
{
    assert(to_sort);
    assert(compare_func);

    if (low < high)
    {
        size_t pivot_position = quick_alg(to_sort, low, high, compare_func, elem_size);

        if (pivot_position > low)
            quick_sort(low, pivot_position - 1, to_sort, compare_func, elem_size);
        quick_sort(pivot_position + 1, high, to_sort, compare_func, elem_size);
    }
}

void quick_print(const int arr_part[], size_t low, size_t left, size_t right, size_t high, const char process[], size_t pivot_position)
{
    assert(arr_part);
    assert(process);

    for (size_t i = low; i <= high; i++)
    {
        printf("%-5lu ", i);
    }
    printf("  %s\n", process);


    for (size_t i = low; i <= left; i++)
    {
        if (i == left)
        {
            PRINT_COLOR(BOLD_BLUE, "%-5d ", arr_part[i]);
        }
        else
            PRINT_COLOR(BLUE, "%-5d ", arr_part[i]);
    }

    for(size_t i = left + 1; i <= right - 1; i++)
    {
        printf("%-5d ", arr_part[i]);
    }

    for(size_t i = right; i <= high; i++)
    {
        if (i == right)
        {
            PRINT_COLOR(BOLD_RED, "%-5d ", arr_part[i]);
        }
        else
            PRINT_COLOR(RED, "%-5d ", arr_part[i]);
    }

    printf("  Left = %lu, Right = %lu, Pivot = %d, Pivot Position = %lu\n",
            left, right, arr_part[pivot_position], pivot_position);

    for (size_t i = low; i <= high; i++)
    {
        if (i == left)
        {
            printf("L");
            printf("     ");
        }
        else if (i == pivot_position)
        {
            printf("P");
            printf("     ");
        }
        else if (i == right)
        {
            printf("R");
        }
        else
            printf("      ");
    }
    printf("\n");
    getchar();
}

void sort_two(void *val1, void *val2, int (*compare_func)(const void *val1, const void *val2), size_t elem_size)
{
    assert(val1);
    assert(val2);
    assert(compare_func);

    if ((*compare_func)(val1, val2) > 0)
    {
        swap_values(val1, val2, elem_size);
    }
}

void sort_three(void *val1, void *val2, void *val3, int (*compare_func)(const void *val1, const void *val2), size_t elem_size)
{
    assert(val1);
    assert(val2);
    assert(val3);
    assert(*compare_func);

    if ((*compare_func)(val1, val2) > 0)
        swap_values(val1, val2, elem_size);

    if ((*compare_func)(val2, val3) > 0)
        swap_values(val2, val3, elem_size);

    if ((*compare_func)(val1, val2) > 0)
        swap_values(val1, val2, elem_size);
}

void sort_more(size_t low, size_t high, void *arr_part, size_t elem_size, size_t *pivot_position, int (*compare_func)(const void *val1, const void *val2))
{
    assert(arr_part);
    assert(compare_func);
    assert(pivot_position);

    bool l_found = false;
    size_t bad_l = 0, bad_r = 0;
    size_t left = low;
    size_t right = high;

    while (left < right)
    {
        if (!l_found)
        {
            if (compare_func((char *)arr_part + left * elem_size,(char *)arr_part + *pivot_position * elem_size) >= 0)
            {
                l_found = true;
                bad_l = left;

                //quick_print((int *)arr_part, low, left, right, high, "Searching For Left Bad Element", *pivot_position);
            }
            else
                left++;
        }
        else
        {
            if (compare_func((char *)arr_part + right * elem_size, (char *)arr_part + *pivot_position * elem_size) <= 0)
            {
                //quick_print((int *)arr_part, low, left, right, high, "Searching For Right Bad Element", *pivot_position);

                l_found = false;
                bad_r = right;

                bool both_are_pivot = false;
                if (compare_func((char *)arr_part + bad_l * elem_size, (char *)arr_part + bad_r * elem_size) == 0 && compare_func((char *)arr_part + bad_l * elem_size, (char *)arr_part + *pivot_position * elem_size) == 0)
                {
                    right--;
                    both_are_pivot = true;
                }

                swap_values((char *)arr_part + bad_l * elem_size, (char *)arr_part + bad_r * elem_size, elem_size);
                if (!both_are_pivot)
                {
                    if (bad_r == *pivot_position)
                        *pivot_position = bad_l;
                    else if (bad_l == *pivot_position)
                        *pivot_position = bad_r;
                }
                else
                {
                    if (*pivot_position == bad_r)
                        *pivot_position = bad_l;
                }

                //quick_print((int *)arr_part, low, left, right, high, "Just Swapped", *pivot_position);
            }
            else
                right--;
        }
    }
}