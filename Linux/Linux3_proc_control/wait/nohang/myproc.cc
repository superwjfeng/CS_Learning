#include <stdio.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef void (*handler)(); // 函数指针类型

std::vector<handler> handlers; // 函数指针数组

void fun_one()
{
    printf("Mission 1\n");
}

void fun_two()
{
    printf("Mission 2\n");
}

void Load()
{
    handlers.push_back(fun_one);
    handlers.push_back(fun_two);
}

int main()
{
    pid_t id = fork();
    if (id<0)
    {
        perror("fork failed\n");
        exit(1);
    }
    if (id==0)
    {
        int cnt = 3;
        while (cnt)
        {
            printf("cnt: %d. I am child preocess. PID: %d, PPID: %d\n", cnt, getpid(), getppid());
            sleep(1);
            cnt--;
        }
        exit(105); // 直接终止子进程
    }
    else
    { 
        int quit = 0;
        while(!quit)
        {
            int status = 0;
            pid_t res = waitpid(-1, &status, WNOHANG); // 以非阻塞方式等待
            if (res > 0)
            {
                // 等待成功 && 子进程退出
                printf("等待子进程退出成功，退出码：%d\n", WEXITSTATUS(status));
                quit = 1;
            }
            else if (res == 0)
            {
                // 等待成功 && 但子进程并未退出
                printf("子进程还在运行中，暂时还没有退出，父进程继续等待，同时父进程可以继续做其他事\n");
                if (handlers.empty()) Load();
                for (auto iter : handlers)
                {
                    // 父进程不挂起，执行其他任务
                    iter();
                }
            }
            else
            {
                // 等待失败
                printf("wait失败!\n");
                quit = 1;
            }
            sleep(1);
        }
    }
    return 0;
}
