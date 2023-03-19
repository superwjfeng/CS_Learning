#include "comm.hpp"
#include "log.hpp"
using namespace std;

//充当使用共享内存的角色
int main() {
    //准备管道
    int fd = Open(FIFO_FILE, WRITER);
    //创建相同的key值
    key_t key = CreateKey();
    Log() << "key: " << key << "\n";
    //获取共享内存
    int shmid = shmget(key, MEM_SIZE,  IPC_CREAT);
    if (shmid < 0) {
        Log() << "shmget: " << strerror(errno) << "\n";
        return 2;
    }
    //挂接
    char* str = (char*)shmat(shmid, nullptr, 0);
    //用它
    while (true) {
        printf("Please enter# ");
        fflush(stdout);
        ssize_t s = read(0, str, MEM_SIZE);
        if (s > 0) {
            str[s] = '\0';
        }
        Signal(fd);
    }
    //sleep(5);
    //int cnt  = 0;
    //while (cnt <= 26) {
    //    str[cnt] = 'A' + cnt;
    //    cnt++;
    //    str[cnt] = '\0';
    //    sleep(1);
    //}
    //去关联
    shmdt(str);
    //用户不需要删除
    return 0;
}