#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "sort_algs.h"
#include <assert.h>

unsigned int my_strlen(const char *data)
{
    assert(data);

    unsigned int len = 0;
    const char *ptr = data;

    while (*ptr)
    {
        len++;
        ptr++;
    }

    return len;
}

int my_puts(const char *data)
{
    assert(data);

    const char *ptr = data;

    while (*ptr)
    {
        if (putchar(*ptr) == EOF)
        {
            return EOF;
        }

        ptr++;
    }

    return putchar('\n');
}

char *my_strcpy(char *dest, const char *src)
{
    assert(dest);
    assert(src);

    for (size_t i = 0; i < my_strlen(src) + 1; i++)
    {
        *(dest+i) = *(src+i);
    }

    return dest;
}

char *my_strcat(char *dest, const char *src)
{
    assert(dest);
    assert(src);

    char *ptr = dest;

    while (*ptr)
    {
        ptr++;
    }

    for (size_t i = 0; i < my_strlen(src) + 1; i++)
    {
        *(ptr + i) = *(src + i);
    }

    return dest;
}

int my_strcmp(const void *str1, const void *str2)
{
    assert(str1);
    assert(str2);

    const char *ptr1 = *(const char * const *)str1;
    const char *ptr2 = *(const char * const *)str2;

    while (1)
    {
        while (*ptr1 && !isalpha(*ptr1))
            ptr1++;

        while (*ptr2 && !isalpha(*ptr2))
            ptr2++;

        if (!*ptr1 || !*ptr2)
            return *ptr1 - *ptr2;

        if (tolower(*ptr1) != tolower(*ptr2))
            return tolower(*ptr1) - tolower(*ptr2);

        ptr1++;
        ptr2++;
    }
}

char *my_strdup(const char *str)
{
    assert(str);

    char *data = (char *) calloc(my_strlen(str) + 1, sizeof(char));

    return my_strcpy(data, str);
}

int my_atoi(const char *str)
{
    assert(str);

    int is_negative = 0;
    int num = 0;
    const char *ptr = str;

    if (*ptr == '-')
    {
        is_negative = 1;
        ptr++;
    }
    else if (*ptr == '+')
    {
        ptr++;
    }
    while (isdigit(*ptr))
    {
        num *= 10;
        num += *ptr - '0';
        ptr++;
    }

    if (is_negative)
    {
        num *= -1;
    }

    return num;
}

double my_atof(const char *str)
{
    assert(str);

    double num = 0;
    const char *ptr = str;
    int is_negative = 0;

    if (*ptr == '-')
    {
        is_negative = 1;
        ptr++;
    }
    else if (*ptr == '+')
    {
        ptr++;
    }
    while (isdigit(*str))
    {
        num *= 10;
        num += *ptr - '0';
        ptr++;
    }

    if (*ptr == '.')
    {
        ptr++;
        double exp = 1;

        while (isdigit(*ptr))
        {
            exp *= 10;
            num += (*ptr - '0') / exp;
        }
    }

    if (is_negative)
    {
        num *= -1;
    }

    return num;
}

size_t my_strnlen(const char *str, size_t maxlen)
{
    assert(str);

    unsigned int len = 0;
    const char *ptr = str;

    while (*ptr)
    {
        len++;
        ptr++;
    }

    if (len < maxlen)
    {
        return len;
    }
    return maxlen;
}

const char * my_strchr(const char *str, int ch)
{
    assert(str);

    const char *ptr = str;

    while (*ptr)
    {
        if (*ptr == ch)
        {
            return ptr;
        }

        ptr++;
    }

    return NULL;
}

const char * my_strrchr(const char *str, int ch)
{
    assert(str);

    const char *ptr = str;
    const char *answer = NULL;

    while (*ptr)
    {
        if (*ptr == ch)
        {
            answer = ptr;
        }

        ptr++;
    }

    return answer;
}

const char * my_strstr(const char *haystack, const char *needle)
{
    assert(haystack);
    assert(needle);

    const char *ptr_hay = haystack;
    const char *ptr_ndl = needle;
    int in_str = 0;

    while (*ptr_hay)
    {
        if (*ptr_hay == *ptr_ndl)
        {
            ptr_ndl++;
        }
        else
        {
            ptr_ndl = needle;
        }

        if (*ptr_ndl == '\0')
        {
            in_str = 1;
            break;
        }

        ptr_hay++;
    }


    if (in_str)
    {
        return ptr_hay - my_strlen(needle) + 1;
    }

    return NULL;
}

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
    assert(n);
    assert(stream);

    size_t counter = 0;
    size_t start_size = 2;
    int ch = '\0';
    int read = 0;

    char *arr = (char *)calloc(start_size, sizeof(char));

    while (!read)
    {
        start_size *= start_size;
        arr = (char *)realloc(arr, start_size * sizeof(char) + 1);

        while (counter < start_size)
        {
            ch = getc(stream);
            if (ch != EOF)
            {
                arr[counter] = (char)ch;
                counter++;

                arr[counter] = '\0';

                if (ch =='\n')
                {
                    read = 1;
                    break;
                }
            }
            else
            {
                read = 1;
                break;
            }
        }

        if (ch == EOF || ch == '\n')
        {
            *n = counter;
            *lineptr = arr;
            if (ch == EOF)
                return -1;
            return (ssize_t)*n;
        }
    }
    return -1;
}
