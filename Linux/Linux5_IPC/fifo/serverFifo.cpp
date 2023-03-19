//读取
#include "comm.h"

using namespace std;
#define NUM 1024


int main() {
    extern int errno;

    //创建fifo文件，只要创建一份就够了
    umask(0);
    if (mkfifo(IPC_PATH, 0600) != 0) {
        cerr << "mkfifo error" << endl;
        return 1;
    }

    int pipeFd = open(IPC_PATH, O_RDONLY);
    if (pipeFd < 0) {
        cerr << "open fifo error" << endl;
        return 2;
    }

    //正常的通信过程
    char buffer[NUM];
    while (true) {
        ssize_t s = read(pipeFd, buffer, sizeof(buffer)-1);
        if (s > 0) {
            buffer[s] = '\0';
            cout << "客服端->服务器#" << buffer << endl;
        }
        else if (s==0) {
            cout << "客户退出了，我也退出" << endl;
            break;
        }
        else {
            // Do nothing
            cout << "read" << strerror(errno) << endl;
        }
    }

    close(pipeFd);
    cout << "服务端退出" << endl;
    unlink(IPC_PATH); //谁创建谁删除fifo文件
    return 0;
}