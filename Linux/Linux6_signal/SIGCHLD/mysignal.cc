#include <iostream>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <wait.h>

using namespace std;

void FreeChild(int signo) {
    assert(signo == SIGCHLD);
        while (true) {
        pid_t id = waitpid(-1, nullptr, WNOHANG); //非阻塞等待，否则父进程可能会卡死在这里
        if (id > 0) {
            cout << "父进程等待成功，chld pid: " << id << endl;
        }
        else if (id == 0) { //还有子进程，但是现在没有退出
            cout << "还有子进程，但是没有退出，父进程要去忙自己的事情" << endl;
            break;
        }
        else {
            cout << "父进程等待子进程结束" << endl;
            break;
        }
    }
}

int main() {
    signal(SIGCHLD, FreeChild);
    for (int i = 0; i < 10; i++) {
        pid_t id = fork();
        if (id == 0) {
            int cnt = 10;
            while (cnt--) {
                cout << "子进程，PID：" << getpid() << "，PPID："<< getppid() << 
                "cnt: "<< cnt << endl;
                sleep(1);
            }
            exit(0);
        }
        //sleep(1);
    }    
    //父进程
    while (true) {
        cout << "父进程，PID：" << getpid() << endl;
        sleep(1);
    }
    return 0;
}