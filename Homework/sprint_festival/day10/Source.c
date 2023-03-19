#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//Problem 1
int Add(int num1, int num2) 
{
    while (num2 != 0)
    {
        int tmp = num1 ^ num2;
        num2 = (num1 & num2) << 1;
        num1 = tmp;
    }
    return num1;
}

int main()
{
    int num1 = 1;
    int num2 = 2;
    printf("%d", Add(num1, num2));
    return 0;
}


