#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("hello world\n");
    printf("MYVAL=%s\n", getenv("MYVAL"));
    return 0;
}
