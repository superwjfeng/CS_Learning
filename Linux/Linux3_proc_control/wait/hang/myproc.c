#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t id = fork();
    if (id<0)
    {
        perror("fork failed\n");
        exit(1);
    }
    else if (id==0)
    {
        int cnt = 5;
        while (cnt)
        {
            printf("cnt: %d. I am child preocess. PID: %d, PPID: %d\n", cnt, getpid(), getppid());
            sleep(1);
            cnt--;
            //int a = 10;
            //a /= 0;
        }
        exit(105); // 直接终止子进程，仅用作测试
    }
    else
    { 
        printf("I am father preocess. PID: %d, PPID: %d\n", getpid(), getppid());
        //sleep(5);
        //pid_t ret = wait(NULL); // 阻塞式等待
        int status = 0;
        // 只有子进程退出的时候，父进程才会waitpid函数进行返回，此时父进程还存在
        // waitpid/wait 可以在目前的情况下，让进程退出具有一定的顺序性
        // 将来可以让父进程进行更多的收尾工作
        pid_t ret = waitpid(id, &status, 0); // 阻塞式等待
        if (ret>0)
        {
            // 可以不这么二进制处理
            // printf("等待子进程成功。ret：%d，status: %d，子进程收到的低7位信号：%d，子进程退出码: %d\n", ret, status, status&0x7f, (status>>8)&0xff);
            if (WIFEXITED(status))
            {
                // 子进程是正常退出的
                printf("子进程执行完毕，子进程的退出码为：%d\n",WEXITSTATUS(status));
            }
            else
            {
                printf("子进程异常退出：%d\n", WIFEXITED(status));
            }
        }
       // while (1)
       // {
       //     printf("I am father preocess. PID: %d, PPID: %d\n", getpid(), getppid());
       //     sleep(1);
       // }
    }
    return 0;
}
