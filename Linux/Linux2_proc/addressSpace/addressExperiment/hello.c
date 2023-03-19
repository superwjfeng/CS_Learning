#include <stdio.h>
#include <unistd.h>

int g_val = 100;

int main()
{
    pid_t id = fork(); // id在父进程里面是子进程的PID，在子进程里面是0
    // fork 之后父子进程共享代码
    if (id == 0)
    {
        int count = 0;
        // Child process
        while (1)
        {
            printf("I am child, pid: %d, ppid: %d, g_val: %d, &g_val: %p\n", getpid(), getppid(), g_val, &g_val);
            printf("---------------------------------------\n");
            sleep(1);
            count++;
            if (count == 3)
            {
                g_val = 200;
                printf("child change g_val 100->200 success\n");
                printf("###################################\n");
            }
        }
    }
    else 
    {
        // Parent process 
        while (1)
        {
            printf("I am parent, pid: %d, ppid: %d, g_val: %d, &g_val: %p\n", getpid(), getppid(), g_val, &g_val);
            sleep(1);
        }
    }
    sleep(1);

    return 0;
}
