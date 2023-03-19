#include "comm.hpp"
#include "log.hpp"

using namespace std;

const int flags = IPC_CREAT | IPC_EXCL;

//充当创建共享内存的角色
int main() {
    //创建管道
    CreateFifo();
    int fd = Open(FIFO_FILE, READER);
    assert(fd >= 0);


    key_t key = CreateKey();
    Log() << "key: " << key << std::endl;
    Log() << "create share memory begin\n" << key << std::endl;
    sleep(5);
    int shmid = shmget(key, MEM_SIZE, flags | 0666);
    if (shmid < 0) {
        Log() << "shmget: " << strerror(errno) << "\n";
        return 2;
    }
    Log() << "create shm success, shmid: " << shmid << "\n";
    //使用共享内存
    //1. 将共享内存和自己的进程关联起来
    char *str = (char*)shmat(shmid, nullptr, 0);
    Log() << "attach shm success, shmid: " << shmid << "\n";
    //sleep(5);

    //使用
    while (true) {
        //让读端进行等待
        if (Wait(fd) <= 0) break; //0 means EOF
        printf("%s\n", str);
        sleep(1);
    }


    //2.去关联
    shmdt(str);
    Log() << "dettach shm success, shmid: " << shmid << "\n";
    sleep(5);
    //删除共享内存
    shmctl(shmid, IPC_RMID, nullptr);
    Log() << "delete shm: \n" << shmid << std::endl;


    Close(fd, FIFO_FILE);
    return 0;
}

//while :; do ipcs -m; sleep 1; echo “#################”; done