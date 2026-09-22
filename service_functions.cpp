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

    long buf_size = get_file_size(name);
    char *buffer = (char *)calloc((size_t)buf_size + 1, sizeof(char));
    if (buffer == NULL)
        return NULL;

    read(file_num, buffer, (size_t)buf_size);
    buffer[buf_size] = '\0';

    if (close(file_num) == -1)
        return NULL;
    return buffer;
}

str_data * getlines(char *text, size_t *len)
{
    assert(text);
    assert(len);

    buf_data text_info = {.char_num = 0, .strings_num = 1};

    parse_string(&text_info, text);

    str_data *onegin = (str_data *)calloc(text_info.strings_num, sizeof(str_data));
    if (onegin == NULL)
        return NULL;
    onegin[0].line = text;

    *len = fill_onegin(onegin, text_info, text);
    return onegin;
}

int check_error(void *arr)
{
    return arr == NULL;
}

long get_file_size(const char *name)
{
    assert(name);

    struct stat file_info = {};
    stat(name, &file_info);

    return file_info.st_size;
}

void parse_string(buf_data *text_info, char *text)
{   assert(text_info);
    assert(text);


    while(text[text_info->char_num])
    {
        if (text[text_info->char_num] == '\n')
        {
            text_info->strings_num++;
            text[text_info->char_num] = '\0';
        }

        text_info->char_num++;
    }
}

size_t fill_onegin(str_data *onegin, buf_data text_info, char *text)
{
    assert(onegin);
    assert(text);

    size_t pointer = 1;
    for (size_t j = 0; j < text_info.char_num; j++)
    {
        if (text[j] == '\0')
        {
            onegin[pointer - 1].len = (text + j) - onegin[pointer - 1].line;
            onegin[pointer++].line = text + j + 1;
        }
    }

    onegin[pointer - 1].len = (long)(text + text_info.char_num) - (long)onegin[pointer - 1].line;
    return pointer;
}

void print_struct_array(str_data *data, size_t len)
{
    assert(data);

    for (size_t i = 0; i < len; i++)
    {
        printf("%s\n", (data[i]).line);
    }
}