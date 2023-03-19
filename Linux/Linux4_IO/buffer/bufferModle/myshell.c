#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

#define NUM 1024
#define SIZE 32
#define SEP " "

// 定义缓冲区
char* g_argv[SIZE]; // 保存打散之后的命令行字符串
char cmd_line[NUM]; // 保存完整的命令行字符串
char g_myval[64];// 写一个环境变量的buffer，用来测试

#define INPUT_REDIR 1
#define OUTPUT_REDIR 2
#define APPEND_REDIR 3
#define NONE_REDIR 0

int redir_status = NONE_REDIR;

char* CheckRedir(char* start)
{
    assert(start);
    char *end = start + strlen(start) - 1; // end指向了最后一个有效字符
    while (end >= start)
    {
        if (*end == '>') // > 输出重定向
        {
            if (*(end-1) == '>') // >> 追加重定向
            {
                redir_status = APPEND_REDIR;
                *(end-1) = '\0'; // 让"ls -al>>myfile.txt"变成"ls -al\0>myfile.txt" 两部分
                end++; // 让end指向myfile.txt的起始
                break;
            }
            redir_status = OUTPUT_REDIR;
            *end = '\0'; 
            end++;
            break;
        }
        else if (*end == '<') // cat < myfile.txt 输入重定向
        { 
             redir_status = INPUT_REDIR;
             *end = '\0';
             end++;
             break;
        }
        else
            end--;
    }
    if (end >= start) // 循环提前break了，说明是重定向
        return end; // 要打开的文件
    else // 没有遇到重定义操作符
        return NULL;
}

// shell运行原理：通过让子进程执行命令，父进程等待&&解析命令
int main()
{
    extern char** environ;
    // 0. 命令行解释器，一定是一个常驻内存的进程，不退出
    while (1)
    {
        // 1. 打印处提示信息 [root@localhost myshell]
        printf("[root@localhost myshell]# ");
        fflush(stdout);
        memset(cmd_line, '\0', sizeof(cmd_line));

        // 2. 获取用户键盘输入[输入的是各种指令和选项：如"ls -a -l -i"]
        if (fgets(cmd_line, sizeof(cmd_line), stdin) == NULL)
        {
            continue;
        }
        cmd_line[strlen(cmd_line)-1] =  '\0';
        // 2.1 分析是否有重定向，如ls -al > log.txt，将其转换为 "ls -al \0log.txt"
        char *sep = CheckRedir(cmd_line);
        //printf("echo: %s\n", cmd_line);
        
        // 3. 命令行字符串解析："ls -a -l -i" -> "ls", "-a", "-l", "-i"
        // 可以在每个空格处放置'\0'后依次拆开。也可以使用strtok函数 
        g_argv[0] = strtok(cmd_line, SEP); // strtok第一次调用要传入原始字符串
        int index = 1;
        if (strcmp(g_argv[0], "ls") == 0)
        {
            g_argv[index++] = "--color=auto";
        }
        if (strcmp(g_argv[0], "ll") == 0)
        {
            g_argv[0] = "ls";
            g_argv[index++] = "-1";
            g_argv[index++] = "--color=auto";

        }
        //while (1)
        //{
        //    g_argv[index] = strtok(NULL, SEP); // 第二次若还要解释原始字符串，则传入NULL
        //    index++;
        //}
        while (g_argv[index++] = strtok(NULL, SEP)); // 解析字符
        for (index=0; g_argv[index]; index++) 
            printf("g_argv[%d]: %s\n", index, g_argv[index]);
        
        // 4. 内置命令，让父进程（shell）自己执行的命令，我们叫做内置命令/内建命令
        // 内置命令本质就是shell中的一个函数调用，因此若拿到的是内置命令，则父进程直接执行
        if (strcmp(g_argv[0], "export") == 0 && g_argv[1] != NULL)
        {
            strcpy(g_myval, g_argv[1]);
            int ret = putenv(g_myval);
            if (ret == 0)
                printf("%s export success\n", g_argv[1]);
            for (int i=0; environ[i]; i++)
                printf("%d: %s\n", i, environ[i]);
            continue;
        }
        if (strcmp(g_argv[0], "cd") == 0)
        {
            if (g_argv[1] != NULL)
                chdir(g_argv[1]); // chdir系统调用
            continue;
        }
        // 5. fork()
        pid_t id = fork();
        if (id == 0)
        {
            // child
            if (sep != NULL)
            { // 说明命令曾经有重定向
                int fd = -1;
                switch(redir_status)
                {
                    case INPUT_REDIR:
                        break;
                    case OUTPUT_REDIR:
                        fd = open(sep, O_WRONLY | O_TRUNC | O_CREAT, 0666);
                        dup2(fd, 1);
                        break;
                    case APPEND_REDIR:
                        break;
                    default:
                        printf("bug\n");
                        break;
                }
            }
            printf("功能让子进程进行\n");
            printf("child, MYVAL: %s\n", getenv("MYVAL"));
            printf("child, PATH: %s\n", getenv("PATH"));
            //execvpe(g_argv[0], g_argv, environ);
            execvp(g_argv[0], g_argv);
            // 问题在于类似于cd这样的命令，这能作用在子进程中，并不能影响shell的路径
            exit(1);
        }
        // father
        int status = 0;
        pid_t ret = waitpid(id, &status, 0);
        if (ret > 0)
            printf("exit code: %d\n", WEXITSTATUS(status));
    }
    return 0;
}
