#include "comm.h"

#define NUM 1024

using namespace std;

int main() {
    int pipeFd = open(IPC_PATH, O_WRONLY);
    if (pipeFd < 0) {
        cerr << "open: " << strerror(errno) << endl;
        return 1;
    }

    char line[NUM];

    while (true) {
        printf("请输入你的消息# ");
        fflush(stdout);
        memset(line , 0, sizeof(line));
        //fgets是C语言接口，会给line结尾自动添加\0
        if (fgets(line, sizeof(line), stdin) != nullptr) {
            //abcd\n\0
            line[strlen(line) - 1] = '\0';
            write(pipeFd, line, strlen(line));
        }
        else {
            break;
        }
    }

    close(pipeFd);
    cout << "客户端退出" << endl;
    return 1;
}
