#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    close(0);
    int fd = open("log.txt", O_RDONLY);
    if (fd<0)
    {
        perror("open");
        return 1;
    }
    printf("fd: %d\n", fd);

    char buffer[64];
    fgets(buffer, sizeof buffer, stdin);

    printf("%s\n", buffer);
    return 0;
}
