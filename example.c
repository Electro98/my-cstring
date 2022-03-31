#include <stdio.h>
//#define WINDOWS_1251
#include "str.h"

int main()
{
    printf("Hello, World!\n");
    str_t str = from_cstr("Naruto!");
    str_t result = multi_str(str, 5);
    printf("result: %s\n", to_char(result));
    printf("   len: %d\n", result.len);
    replace(&result, "Naruto", "Baka");
    printf("result: %s\n", to_char(result));
    printf("   len: %d\n", result.len);
    stfree(result);
    stfree(str);
    result = f_str("Scotobaza %d", 32);
    printf("result: %s\n", to_char(result));
    printf("   len: %d\n", result.len);
    stfree(result);
    return 0;
}
