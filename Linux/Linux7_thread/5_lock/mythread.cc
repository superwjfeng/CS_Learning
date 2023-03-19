#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

#include "Lock.hpp"

using namespace std;



//int tickets = 1000; //临界资源，可能会造成数据不一致问题
//Mutex mutex;
//
//////定义要传入的线程数据组
////#define NAMESIZE 64
////typedef struct threadData {
////    char name[NAMESIZE];
////    pthread_mutex_t *mutexp;
////}threadData;
////
////
////void *startRoutine(void *args) {
////    //pthread_mutex_t *mutex_p = static_cast<pthread_mutex_t *>(args);
////    threadData *td = static_cast<threadData *>(args);
////    while (true) {
////        pthread_mutex_lock(td->mutexp); //阻塞锁
////        
////    }
////    return nullptr;
////}
//
//// 函数本质是一个代码块
//bool getTickets() {
//    bool ret = false;
//    //加锁
//    LockGuard lockGuard(&mutex); 
//    if (tickets > 0) {
//        usleep(10000);
//        cout << "thread: " << pthread_self() << " gets a ticket: " << tickets << endl;
//        tickets--;
//        ret = true;
//    }
//    return ret;
//    // 除了代码块之后就会自动调用LockGuard的析构来解锁，这是一种RAII风格
//}
//
//
//void *startRoutine(void *args) {
//    const char *name = static_cast<const char *>(args);
//    while (true) {
//        if (!getTickets()) {
//            break;
//        }
//        cout << name << " get tickets success" << endl;
//        //做其他事情
//        sleep(1);
//    }
//}
//
//
//int main() {
//    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//    pthread_t t1, t2, t3, t4;
////    threadData *td = new threadData();
////    strcpy(td->name, "thread 1");
////    td->mutexp = &mutex;
//    
//    pthread_create(&t1, nullptr, startRoutine, (void *)"thread 1");
//    pthread_create(&t2, nullptr, startRoutine, (void *)"thread 2");
//    pthread_create(&t3, nullptr, startRoutine, (void *)"thread 3");
//    pthread_create(&t4, nullptr, startRoutine, (void *)"thread 4");
//    //pthread_create(&t2, nullptr, startRoutine, (void*)&mutex);
//    //pthread_create(&t3, nullptr, startRoutine, (void*)&mutex);
//    //pthread_create(&t4, nullptr, startRoutine, (void*)&mutex);
//
//    pthread_join(t1, nullptr);
//    pthread_join(t2, nullptr);
//    pthread_join(t3, nullptr);
//    pthread_join(t4, nullptr);
//    //pthread_mutex_destroy(&mutex); //释放锁
//
////    delete td;
//    return 0;
//}


//一把锁是否会有死锁问题？
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int cnt = 100;

void *startRoutine(void *args) {
    string name = static_cast<char *>(args);
    while (true) {
        pthread_mutex_lock(&mutex);
        pthread_mutex_lock(&mutex); //被自己锁死了
        cout << "count: " << cnt-- << endl;
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

int main() {
    pthread_t t1;
    pthread_t t2;
    pthread_create(&t1, nullptr, startRoutine, (void*)"thread 1");
    pthread_create(&t2, nullptr, startRoutine, (void*)"thread 2");
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    return 0;
}