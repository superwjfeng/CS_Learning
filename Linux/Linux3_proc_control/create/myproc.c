#include <stdio.h>
#include <unistd.h>

int main()
{
    const char* str = "aaa";
    const char* str1 = "aaa";

    printf("%p\n", str);
    printf("%p\n", str1);

    return 0;
}
