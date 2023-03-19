#include <iostream>
#include <cstdlib>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

using namespace std;

////这里不是调用handler方法，这里只是设置了一个回调，当SIGINT产生的时候，该方法才会被调用
////若不产生SIGINT，该方法不会被调用
////ctrl + c：本质就是给前台进程产生了2号信号，发送给目标进程
////目标进程默认对2号信号的处理是终止自己
////现在通过signal发生一个handler设置了用户对2号信号的自定义处理方法
//void handler(int signo) {
//    cout << "我是一个进程，刚刚获取了一个信号：" << signo << endl;
//}
//
//int main() {
//    signal(SIGQUIT, handler);
//    sleep(3);
//    cout << "我已经设置完了" << endl;
//    sleep(3);
//    while (true) {
//        cout << "我是一个正在运行中的程序" << getpid() << endl;
//        sleep(1);
//    }
//    return 0;
//}

long long cnt = 0;

void handler(int signo) {
    //cout << "我是一个进程，刚刚获取了一个信号：" << signo << cnt << endl;
    cout << "我是一个进程，刚刚获取了一个信号：" << signo << endl;
    exit(1);
}

static void Usage(const std::string& proc) {
    cerr << "Usage:\n\t" << proc << " signo pid" << endl;
}

int main(int argc, char* argv[]) {
    pid_t id = fork();
    if (id <= 0) {
        //子进程
        int *p = nullptr;
        *p = 1000; //野指针问题
        exit(1);
    }
    //父进程
    int status = 0;
    waitpid(id, &status, 0);
    printf("exitcode: %d, signo: %d, core dump flag: %d\n",
        (status>>8) & 0xff, status & 0x7f, (status>>7) &0x1);

    //for (int sig=1; sig<=31; sig++) {
    //    signal(sig, handler);
    //}
    
    //int a[10];
    //a[10000] = 100;

    //int a = 10;
    //a /= 0;

    //signal(SIGALRM, handler);
    //alarm(1);
    //while (1) {
    //    cout << cnt << endl;
    //    cnt++;
    //}

    //if (argc != 3) {
    //    Usage(argv[0]);
    //    exit(1);
    //}
    
    //if (kill(static_cast<pid_t>(atoi(argv[2])), atoi(argv[1])) == -1) {
    //    cerr << "kill: " << strerror(errno) << endl;
    //    exit(2);
    //}
}