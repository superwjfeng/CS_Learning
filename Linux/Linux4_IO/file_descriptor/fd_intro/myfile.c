#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    umask(0); // 覆盖系统的umask
    int fd1 = open("log1.txt", O_WRONLY|O_CREAT|O_APPEND, 0666);
    printf("open success, fd1: %d\n", fd1);
    int fd2 = open("log2.txt", O_WRONLY|O_CREAT|O_APPEND, 0666);
    printf("open success, fd2: %d\n", fd2);
    int fd3 = open("log3.txt", O_WRONLY|O_CREAT|O_APPEND, 0666);
    printf("open success, fd3: %d\n", fd3);
    int fd4 = open("log4.txt", O_WRONLY|O_CREAT|O_APPEND, 0666);
    printf("open success, fd4: %d\n", fd4);

    close(fd1);
    close(fd2);
    close(fd3);
    close(fd4);
    return 0;
}
