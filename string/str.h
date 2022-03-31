//
// Created by Electro98 on 21.03.2022.
//

#ifndef STRING_STR_H
#define STRING_STR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define pure_len(str) (str.len - 1)
#define len(str) (str.len)
#define get_char(str, i) (str.ptr[i])
#define to_char(str) (str.ptr)

#define SUCCESS 0
#define STR_NOT_FOUND -1
#define bool uint8_t
#define true 1
#define false 0

typedef struct {
    uint32_t len;
    char* ptr;
} str_t;

str_t concatenate(str_t str1, str_t str2);
int32_t replace(str_t *str, const char* pattern, const char* replace);
int32_t replace_str(str_t *str, const char* pattern, str_t replace);
uint32_t index_str(str_t string, str_t substring);
bool check_str_in(str_t string, str_t substring);
str_t upper(str_t str);
str_t lower(str_t str);
str_t* split(str_t str, const char* separator);
bool isdigit(str_t str);
bool isalpha(str_t str);
bool equals(str_t str1, str_t str2);
str_t multi_str(str_t str, uint32_t num);

void stfree(str_t str);

// input logic

uint32_t cstr_len(const char* str);
str_t from_cstr(const char *str);
str_t get_str();
str_t get_fstr(FILE* stream);

#endif //STRING_STR_H
