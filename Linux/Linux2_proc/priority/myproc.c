#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    while (1)
    {
        printf("hello world\n");
        sleep(1);
    }
    return 0;
}
