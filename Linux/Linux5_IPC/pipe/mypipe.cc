#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

// 为什么不定义全局buffer来进行通信？因为有写时拷贝的存在，数据是父子进程各自私有的，无法更改通信

int main() {
    //1. 创建管道
    int pipefd[2] = {0}; // pipefd[0]：读端，pipefd[1]：写端
    int n = pipe(pipefd);
    assert(n != -1);
    (void)n; //在realease下assert无效，若此时n是-1，那么需要证明n被使用过，否则会有很多报警信息

#ifdef DEBUG //条件编译
    cout << "pipefd[0]: " << pipefd[0] << endl;
    cout << "pipefd[1]: " << pipefd[1] << endl;
#endif

    //2. 创建子进程
    pid_t id = fork();
    assert(id != -1);
    if (id==0) {
        //子进程
        //3. 构建单向通信的信道，父进程写入，子进程读取
        //3.1 关闭子进程不需要的写端fd
        close(pipefd[1]);
        char buffer[1024];
        while (true) {
            ssize_t s = read(pipefd[0], buffer, sizeof(buffer)-1);
            if (s > 0) {
                buffer[s] = '\0'; //约定读的是C字符串，因为read是系统调用不会自动添加\0，所以手动添加
                cout << "child get a message[" << getpid() << "] Father#" << buffer << endl;
            }
        }
        close(pipefd[0]); //可写可不写，退出了之后自动关闭
        exit(0);
    }
    //父进程
    //3. 构建单向通信的信道
    //3.1 关闭父进程不需要的读端fd
    close(pipefd[0]);
    string message = "我是父进程，正在发送信息";
    int count = 0; //计数器，记录发送信息的条数
    char send_buffer[1024];
    while (true) {
        //3.2 构建一个变化的字符串
        snprintf(send_buffer, sizeof(send_buffer), "%s[%d]: %d", message.c_str(), getpid(), count++);
        //3.3 写入
        write(pipefd[1], send_buffer, strlen(send_buffer));
        //3.4 故意sleep
        sleep(1);
    }
    pid_t ret = waitpid(id, nullptr, 0);
    assert(ret > 0);
    (void)ret;
    close(pipefd[1]);
    return 0;
}