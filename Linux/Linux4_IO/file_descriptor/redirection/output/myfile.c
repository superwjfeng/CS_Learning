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
    // 这里的fd的分配规则是：优先分配最小的没有被占用的文件描述符
    int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666); // fd == 1
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    printf("fd: %d\n", fd);
    printf("fd: %d\n", fd);
    printf("fd: %d\n", fd);
    printf("fd: %d\n", fd);
    printf("fd: %d\n", fd);
    printf("fd: %d\n", fd);
    fprintf(stdout, "hello fprintf\n");
    const char *s = "hello fwrite";
    fwrite(s, strlen(s), 1, stdout);

    fflush(stdout);
   // stdout->_fileno == 1;
    close(fd);
    return 0;
}
