#include <iostream>
#include <cstdlib>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

using namespace std;

long long cnt = 0;

void handler(int signo) {
    //cout << "我是一个进程，刚刚获取了一个信号：" << signo << cnt << endl;
    cout << "我是一个进程，刚刚获取了一个信号：" << signo << endl;
    //exit(1);
}

static void Usage(const std::string& proc) {
    cerr << "Usage:\n\t" << proc << " signo pid" << endl;
}

static void showPending(sigset_t *pendings) {
    for (int sig = 1;sig <= 31;sig++) {
        if (sigismember(pendings, sig)) {
            cout << "1";
        }
        else {
            cout << "0";
        }
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    //3. 屏蔽2号信号
    sigset_t bsig, obsig;
    sigemptyset(&bsig);
    sigemptyset(&obsig);

    //3.1 添加2号信号到信号屏蔽字中
    sigaddset(&bsig, 2);
    //3.2 设置用户级的信号屏蔽字到内核中，让当前信号屏蔽2号
    sigprocmask(SIG_SETMASK, &bsig, &obsig);

    //2. 捕捉
    signal(2, handler);
    //1. 不断地获取当前进程的pending信号集
    sigset_t pendings;
    while (true) {
        sigemptyset(&pendings);
        // 1.2 获取当前进程（谁调用就获取谁）的pending信号集
        if (sigpending(&pendings) == 0) { //获取信号集成功
            showPending(&pendings);
        }
        sleep(1);
    }

    return 0;
}
