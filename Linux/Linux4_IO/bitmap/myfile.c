#include <stdio.h>
#include <unistd.h>
#include <string.h>

// 用int中的不重复的一个bit，就可以表示一种状态
#define ONE 0x1 // 0000 0001
#define TWO 0x2 // 0000 0010
#define THREE 0x4 // 0000 0100

void show(int flags)
{
    if (flags & ONE)
        printf("hello one\n");
    if (flags & TWO)
        printf("hello two\n");
    if (flags & THREE)
        printf("hello three\n");
}

int main()
{
    show(ONE);
    printf("-------------------------\n");
    show(TWO);
    printf("-------------------------\n");
    show(ONE | TWO);
    printf("-------------------------\n");
    show(ONE | TWO | THREE);
    printf("-------------------------\n");
    show(ONE | THREE);
    return 0;
}
