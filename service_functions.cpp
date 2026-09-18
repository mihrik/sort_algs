#include "sort_algs.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void print_int_array(int data[], size_t len)
{
    assert(data);

    for (size_t i = 0; i < len; i++)
    {
        printf("%d ", data[i]);
    }
}

void print_double_array(double data[], size_t len)
{
    assert(data);

    for (size_t i = 0; i < len; i++)
    {
        printf("%lf ", data[i]);
    }
}

void print_strings_array(char *data[], size_t len)
{
    assert(data);

    for (size_t i = 0; i < len; i++)
    {
        printf("%s ", data[i]);
    }
}

void mem_exchange(void *val1, void *val2, size_t elem_size)
{
    assert(val1);
    assert(val2);

    for (size_t i = 0; i < elem_size; i++)
    {
        *((char *)val1 + i) = *((char *)val2 + i);
    }
}

void swap_values(void *val1, void *val2, size_t elem_size)
{
    assert(val1);
    assert(val2);

    void *temp = calloc(1, elem_size);
    for (size_t i = 0; i < elem_size; i++)
    {
        *((char *)temp + i) = *((char *)val2 + i);
    }
    mem_exchange(temp, val2, elem_size);
    mem_exchange(val2, val1, elem_size);
    mem_exchange(val1, temp, elem_size);

    free(temp);
}

size_t read_text(const char *name, char **text)
{
    assert(name);
    assert(text);

    FILE *file = NULL;
    assert(file = fopen(name, "r"));

    size_t nlines = 0;
    size_t string_len = 0;

    while(my_getline(&text[nlines], &string_len, file) != -1)
        nlines++;

    assert(!fclose(file));
    return nlines;
}

void copy_arr(char **dest, char **src, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        dest[i] = src[i];
    }
}