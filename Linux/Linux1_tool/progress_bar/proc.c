#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define NUM 101

int main()
{
    char bar[NUM];
    memset(bar, 0, sizeof(bar));
    const char *lable = "|/-\\"; //4个符号

    int cnt = 0;
    while (cnt <= 100)
    {
        printf("[%-100s][%d%%] %c\r", bar, cnt, lable[cnt%4]);
        bar[cnt++] = '#';
        fflush(stdout);

        usleep(30000);
    }
    printf("\n");

    return 0;
}
