#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

#define NUM 1024

typedef struct MyFILE_
{
    int fd;
    char buffer[1024];
    int end; // 当前缓冲区的结尾
} MyFILE;

MyFILE *fopen_(const char *pathname, const char *mode)
{
    assert(pathname && mode);
    MyFILE *fp = NULL;
    if (strcmp(mode, "r") == 0)
    {

    }
    else if (strcmp(mode, "r+") == 0)
    {

    }

    else if (strcmp(mode, "w") == 0)
    {
        int fd = open(pathname, O_WRONLY | O_TRUNC | O_CREAT ); // 封装系统调用
        if (fd >= 0) // 若打开文件失败返回<0，则什么都没有发生，直接退出else if后返回fp == NULL
        {
            fp = (MyFILE*)malloc(sizeof(MyFILE));
            memset(fp, 0, sizeof(MyFILE));
            fp->fd = fd;
        }
    }
    
    else if (strcmp(mode, "w+") == 0)
    {

    }
    else if (strcmp(mode, "a") == 0)
    {

    }
    else if (strcmp(mode, "a+") == 0)
    {

    }
    else{}
    
    return fp;

}

void fputs_(const char *message, MyFILE *fp)
{
    assert(message && fp);
    strcpy(fp->buffer + fp->end, message); // 若buffer里已经有数据了，则end!=0
    fp->end += strlen(message);

    printf("%s\n", fp->buffer); // 用来debug
    
    // 暂时没有刷新，刷新策略是用户通过执行C标准库中的代码逻辑来完成刷新动作的
    // 因为C提供了缓冲区，通过刷新策略，减少了IO的执行次数（数据量不变），IO的本质就是write和read等系统接口
    if (fp->fd == 0){} // stdin 涉及到键盘等硬件的IO比较复杂
    else if (fp->fd == 1)
    { // stdout
        if (fp->buffer[fp->end - 1] == '\n')
        {
            fprintf(stderr, "fflush: %s", fp->buffer);
            write(fp->fd, fp->buffer, fp->end);
            fp->end = 0;
        }
    }
    else if (fp->fd == 2)
    { // stderr

    }
    else
    { // 其他文件

    }
}

void fflush_(MyFILE *fp)
{
    assert(fp);
    if (fp->end != 0) //end!=0就说明缓冲区里有数据
    {
        // 暂且认为刷新了 -- 其实是把数据刷新到了内核
        // 若想把数据手动写到外设里，要用sync
        write(fp->fd, fp->buffer, fp->end);
        syncfs(fp->fd);
        fp->end = 0;
    }
}

void fclose_(MyFILE *fp)
{
    assert(fp);
    fflush_(fp);
    close(fp->fd); // 封装系统调用
    free(fp);
}

int main()
{
    close(1);
    MyFILE *fp = fopen_("./log.txt", "w");
    if (fp == NULL)
    {
        printf("open file error");
        return 1;
    }
    fputs_("one: hello world", fp);
    sleep(1);
    fputs_(" two: hello world\n", fp);
    sleep(1);
    fputs_(" three: hello world", fp);
    sleep(1);
    fputs_(" four: hello world\n", fp);
    sleep(1);

    fclose_(fp);
    return 0;
}
