#include "sort_algs.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
        printf("%s\n", data[i]);
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

char * read_text(const char *name)
{
    assert(name);

    int file_num = open(name, O_RDONLY);
    if (file_num == -1)
        return NULL;

    struct stat file_info = {};
    stat(name, &file_info);

    long buf_size = file_info.st_size;
    char *buffer = (char *)calloc((size_t)buf_size + 1, sizeof(char));
    if (buffer == NULL)
        return NULL;

    read(file_num, buffer, (size_t)buf_size);
    buffer[buf_size] = '\0';

    if (close(file_num) == -1)
        return NULL;
    return buffer;
}

char ** getlines(char *text, size_t *len)
{
    assert(text);
    assert(len);

    size_t char_num = 0;
    size_t strings_num = 1;

    while(text[char_num])
    {
        if (text[char_num] == '\n')
        {
            strings_num++;
            text[char_num] = '\0';
        }

        char_num++;
    }

    char **onegin = (char **)calloc(strings_num, sizeof(char *));
    if (onegin == NULL)
        return NULL;
    onegin[0] = text;

    size_t pointer = 1;
    for (size_t j = 0; j < char_num; j++)
    {
        if (text[j] == '\0')
        {
            onegin[pointer++] = text + j + 1;
        }
    }

    *len = pointer;
    return onegin;
}

int check_error(void *arr)
{
    return arr == NULL;
}