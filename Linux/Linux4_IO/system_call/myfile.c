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
    //int fd = open("log.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666); // 添加了权限码，用来创建文件
    //int fd = open("log.txt", O_WRONLY|O_CREAT|O_APPEND, 0666);
    int fd = open("log.txt", O_RDONLY); // 没有权限码，默认文件已经存在
    if (fd < 0)
    {
        perror("open");
        return 1;
    }
    printf("open success, fd: %d\n", fd);
    char buffer[64];
    memset(buffer, '\0', sizeof(buffer));
    read(fd, buffer, sizeof(buffer));
    printf("%s", buffer);
    //const char *s = "hello write\n";
    //const char *s = "aa\n";
    //write(fd, s, strlen(s)); // 系统调用不需要+1
    // open success
    return 0;
}
