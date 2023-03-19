#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    close(1);
    int fd = open("log.txt", O_WRONLY | O_APPEND | O_CREAT);
    if (fd<0)
    {
        perror("open");
        return 1;
    }
    fprintf(stdout, "success\n");
    return 0;
}
