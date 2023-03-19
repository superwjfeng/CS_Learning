#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

using namespace std;

int tickets = 10000; //临界资源，可能会造成数据不一致问题
pthread_mutex_t mutex; //全局锁

void *getTickets(void *args) {
    //访问临界资源的代码称为临界区
    pthread_mutex_lock(&mutex); //给临界区加锁
    const char* name = static_cast<const char*>(args);
    while (true) {
        if (tickets > 0) {
            cout << "thread[" << name << "] 抢到了票，票的编号" << tickets << endl;
            tickets--;
            pthread_mutex_unlock(&mutex); //解锁
            //当前线程重新申请锁的成本远低于唤醒其他线程，因此一直在跑这个线程
            //若想要其他线程也来申请，可以在临界区后面用usleep模拟唤醒其他线程
            usleep(123); //休眠微秒
        }
        else {
            cout << "thread[" << name << "] 已经放弃抢票了，因为没票了" << endl;
            pthread_mutex_unlock(&mutex); //解锁
            break;
        }
        //也不能在这里解锁，会造成死锁
        //pthread_mutex_unlock(&mutex); //解锁
    }
    //不能在while循环外面解锁，粒度太高，没人抢得到第一个线程
    //pthread_mutex_unlock(&mutex); //解锁
    return nullptr;
}

int main() {
    pthread_mutex_init(&mutex, nullptr); //初始化锁
    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;
    pthread_create(&tid1, nullptr, getTickets, (void*)"thread1");
    pthread_create(&tid2, nullptr, getTickets, (void*)"thread2");
    pthread_create(&tid3, nullptr, getTickets, (void*)"thread3");

    //线程执行自己的startRoutine，主线程继续往下执行
    //但我们不知道到底是create出来的线程还是主线程先被调度
    //有一种可能是create后先调度主线程然后直接被join了，所以让主线程sleep一会
    sleep(1);

    pthread_detach(tid1); //让主线程来分离
    pthread_detach(tid2);
    pthread_detach(tid3);
    pthread_mutex_destroy(&mutex); //释放锁

    return 0;
}