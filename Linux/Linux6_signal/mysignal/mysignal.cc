#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

using namespace std;

void handler(int signo) {
    cout << "获取到一个信号" << signo << endl;
    cout << "pid: " << getpid() << endl;
    sleep(20);
}

int main() {
    struct sigaction act, oact;
    act.sa_handler = handler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(2, &act, &oact);

    while (true) {
        sleep(1);
    }

    return 0;
}