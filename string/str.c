//
// Created by Electro98 on 21.03.2022.
//

#include "str.h"

str_t concatenate(str_t str1, str_t str2)
{
    str_t result = {
            .len = str1.len + str2.len - 1,
            .ptr = malloc((str1.len + str2.len - 1) * sizeof(char))
    };
    int i = 0;
    for (int j = 0; j < pure_length(str1); ++j, ++i)
        result.ptr[i] = str1.ptr[j];
    for (int j = 0; j < str2.len; ++j, ++i)
        result.ptr[i] = str2.ptr[j];
    return result;
}

uint32_t replace(str_t str, const char* pattern, const char* replace);

uint32_t replace_str(str_t str, const char* pattern, str_t replace);

uint32_t* kmp_table(str_t str)
{
    uint32_t* ptr = calloc(pure_length(str), sizeof(uint32_t));
    uint32_t cnd = 0;
    for (int i = 1; i < pure_length(str); ++i)
    {
        while ((cnd > 0) && (str.ptr[i] == str.ptr[cnd]))
            cnd = ptr[cnd - 1];
        if (str.ptr[i] == str.ptr[cnd])
            cnd += 1;
        ptr[i] = cnd;
    }
    return ptr;
}

uint32_t index_str(str_t string, str_t substring)
{
    uint32_t* prefix_table = kmp_table(string);
    int64_t result = STR_NOT_FOUND;
    uint32_t j = 0;
    for (int i = 0; i < string.len; ++i)
    {
        if ((j > 0) && (substring.ptr[j] != string.ptr[i]))
            j = prefix_table[j - 1];

        if (string.ptr[i] == substring.ptr[j])
            ++j;

        if (j == substring.len)
        {
            result = i - j + 1;
            break;
        }
    }
    free(prefix_table);
    return result;
}

bool check_str_in(str_t string, str_t substring)
{
    return index_str(string, substring) != STR_NOT_FOUND;
}

str_t upper(str_t str)
{
    str_t result = {
            .len = str.len,
            .ptr = malloc(str.len * sizeof(char)),
    };
    char* src = str.ptr;
    char* dst = result.ptr;
    for (int i = 0; i < str.len; ++i, ++src, ++dst)
    {
        *dst = *src;
#ifdef WINDOWS_1251
        if (('a' <= *src && *src <= 'z') || ('а' <= *src && *src <= 'я'))
            *dst -= 32;
#else
        if (('a' <= *src && *src <= 'z'))
            *dst -= 32;
#endif
    }
    return result;
}

str_t lower(str_t str)
{
    str_t result = {
            .len = str.len,
            .ptr = malloc(str.len * sizeof(char)),
    };
    char* src = str.ptr;
    char* dst = result.ptr;
    for (int i = 0; i < str.len; ++i, ++src, ++dst)
    {
        *dst = *src;
#ifdef WINDOWS_1251
        if (('A' <= *src && *src <= 'Z') || ('А' <= *src && *src <= 'Я'))
            *dst += 32;
#else
        if (('A' <= *src && *src <= 'Z'))
            *dst += 32;
#endif
    }
    return result;
}

str_t* split(str_t str, const char* separator);

bool isdigit(str_t str)
{
    for (char* ptr = str.ptr; *ptr; ++ptr)
        if (('0' > *ptr) || (*ptr > '9'))
            return false;
    return true;
}

bool isalpha(str_t str)
{
    for (char* ptr = str.ptr; *ptr; ++ptr)
    {
#ifdef WINDOWS_1251
        if (!((('a' <= *ptr && *ptr <= 'z') || ('A' <= *ptr && *ptr <= 'Z'))
               || (('а' <= *ptr && *ptr <= 'я') || ('А' <= *ptr && *ptr <= 'Я'))))
            return false;
#else
        if (!(('a' <= *ptr && *ptr <= 'z') || ('A' <= *ptr && *ptr <= 'Z')))
            return false;
#endif
    }
    return true;
}

bool equals(str_t str1, str_t str2)
{
    if (str1.len != str2.len)
        return false;
    char* str1_ptr = to_char(str1);
    for (char* str2_ptr = to_char(str2); *str2_ptr; ++str2_ptr, ++str1_ptr)
        if (*str2_ptr != *str1_ptr)
            return false;
    return true;
}

str_t multi_str(str_t str, uint32_t num)
{
    str_t result = {
            .ptr = malloc((pure_length(str) * num + 1) * sizeof(char)),
            .len = pure_length(str) * num + 1,
    };
    result.ptr[pure_length(result)] = '\0';
    char* dst = to_char(result);
    for (int i = 0; i < num; ++i)
        for (char* src = to_char(str); *src; ++src, ++dst)
            *dst = *src;
    return result;
}

void stfree(str_t str)
{
    free(str.ptr);
    str.ptr = NULL;
    str.len = 0;
}

/*
 * Input logic block
 */

uint32_t cstr_len(const char* str)
{
    if (str == NULL)
        return 0;
    for (int i = 0;; ++i)
        if (!str[i])
            return ++i;
}

char* copy_cstr(const char* str)
{
    uint32_t len = cstr_len(str);
    char* result = malloc(len * sizeof(char));
    for (int i = 0; i < len; ++i)
        result[i] = str[i];
    return result;
}

str_t from_cstr(char* str)
{
    return (str_t) {
            .ptr = copy_cstr(str),
            .len = cstr_len(str),
    };
}
