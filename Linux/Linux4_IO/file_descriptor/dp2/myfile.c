#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 2;
    }
    int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC);
    if (fd<0)
    {
        perror("open");
        return 1;
    }

    dup2(fd, 1);
    fprintf(stdout, "%s\n", argv[1]);
    close(fd);
    return 0;
}
