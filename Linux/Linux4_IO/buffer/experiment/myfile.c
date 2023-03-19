#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    // C语言提供的
    printf("hello printf\n");
    fprintf(stdout, "hello fprintf\n");
    const char *s = "hello fputs\n";
    fputs(s, stdout);

    // OS提供的
    const char *ss = "hello write\n";
    write(1, ss, strlen(ss));
    // 在最后才调用fork，上面的函数已经被执行完了
    fork();
    return 0;
}

