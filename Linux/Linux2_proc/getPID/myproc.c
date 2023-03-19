#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    while (1)
    {
        pid_t id = getpid(); // 获取的是自己的进程PID
        printf("hello world, pid: %d, ppid: %d\n", id, getppid());
        sleep(1);
    }
    return 0;
}
