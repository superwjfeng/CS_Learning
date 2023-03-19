#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

#define NUM 16

//const char* myfile = "/home/WJFeng/Linux3_proc_control/substitution/mycmd";
const char* myfile = "./mycmd";

int main(int argc, char* argv[], char* env[])
{
    // 为什么要创建子进程？为了不影响父进程
    // 我们想让父进程的功能聚焦在读取数据，解析数据，指派进程子进程执行代码上
    // 若不创建，那么我们替换的进程就只能是父进程；若创建了，替换的进程就是子进程，而不影响父进程
 
    const char* _env[NUM] = {
        (char*)"MY_105_VAL=123456",
        NULL
    };
    pid_t id = fork();
    if (id==0)
    {
        printf("子进程开始运行，pid: %d\n", getpid());
        sleep(3);
        char *const _argv[NUM] = {
            (char*)"ls",
            (char*)"-a",
            (char*)"-l",
            (char*)"-i",
            NULL
        };
        //execlp("python", "python", "pythonTest.py", NULL);
        //execlp("bash", "bash", "shellTest.sh", NULL);
        //execl(myfile, "mycmd", "-a", NULL);
        //execl("/usr/bin/ls", "ls", "-l", "-a", NULL); // 结尾以NULL结尾？回忆main函数和环境表的关系
        //// 就是传递给了main函数的形参
        //execv("/usr/bin/ls", _argv); // 和execl函数只有传参方式的区别
        execlp("ls", "ls", "-a", "-l", NULL);
        //execvp("ls", _argv);
        //execle(myfile, "mycmd", "-a", NULL, _env);
        //sysexecle(myfile, "mycmd", "-a", NULL, env);
        exit(1);
    }
    else
    {
        printf("父进程开始运行，pid: %d\n", getpid());
        int status = 0;
        pid_t id = waitpid(-1, &status, 0); // 阻塞等待，一定是子进程先运行完毕，然后父进程获取之后才退出
        if (id>0)
        {
            printf("wait success, exit code: %d\n", WEXITSTATUS(status));
        }
    }


    return 0;
}
