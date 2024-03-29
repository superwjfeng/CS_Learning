#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t id = fork(); // id在父进程里面是子进程的PID，在子进程里面是0
    // fork 之后父子进程共享代码
    if (id<0)
    {
    //    // 创建失败
        perror("fork");
        return 1;
    }
    else if (id == 0)
    {
        // fork产生的两个进程会同时执行
        // Child process
        while (1)
        {
            printf("I am child, pid: %d, ppid:%d\n", getpid(), getppid());
            sleep(1);
        }
    }
    else 
    {
        // Parent process 
        int time = 3;
        while (time)
        {
            printf("I am father, pid: %d, ppid:%d\n", getpid(), getppid());
            sleep(1);
            time--;
        }
    }

    printf("You can see me!\n");
    sleep(1);

    return 0;
}
