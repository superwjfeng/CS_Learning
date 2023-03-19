#include <iostream>
#include <unistd.h>

int main() {
    while (1) {
        sleep(1);
        std::cout << "我是一个进程：" << getpid() << std::endl;
    }
}