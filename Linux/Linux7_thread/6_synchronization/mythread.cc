#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <functional>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>


using namespace std;

pthread_cond_t cond; //定义一个条件变量

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //定义一个互斥锁，当前不用，但接口需要

volatile bool quit = false; //定义全局退出变量

void *waitCommand(void *args) {
    //pthread_detach(pthread_self());
    while (!quit) {
        //执行了下面的代码，就证明某一种条件不就绪，需要进行线程等待
        //三个线程，都会在条件变量下排队
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex); //让对应的线程进行等待，等待被唤醒
        pthread_mutex_unlock(&mutex);
        cout << "thread id: " << pthread_self() << " run..." << endl;
        
    }
    cout << "thread id: " << pthread_self() << " end..." << endl;
    pthread_exit(nullptr);
    return nullptr;
}

int main() {
    pthread_cond_init(&cond, nullptr);

    pthread_t t1, t2, t3;
    pthread_create(&t1, nullptr, waitCommand, nullptr);
    pthread_create(&t2, nullptr, waitCommand, nullptr);
    pthread_create(&t3, nullptr, waitCommand, nullptr);

    while (true) {
        char n = 0;
        cout << "请输入你的command(n/q)";
        cin >> n;
        if (n == 'n')
        {
            quit = true;
            //pthread_cond_signal(&cond); //唤醒线程
            pthread_cond_broadcast(&cond); //唤醒线程
            break;
        }
        else
        {
            quit = true;
            break;
        }
         
        sleep(1);
    }

    cout << "main thread quit" << endl;
    pthread_cond_broadcast(&cond); //唤醒线程
   // pthread_cancel(t1);
   // pthread_cancel(t2);
   // pthread_cancel(t3);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);
        
    pthread_cond_destroy(&cond);

    return 0;
}


//pthread_cond_t cond; //定义一个条件变量
//
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //定义一个互斥锁，当前不用，但接口需要
//
//volatile bool quit = false; //定义全局退出变量
//
//vector<function<void()>> funcs;
//
//void show() {
//    cout << "hello world" << endl;
//}
//
//void print() {
//    cout << "hello print" << endl;
//}
//
//void *waitCommand(void *args) {
//    while (!quit) {
//        pthread_detach(pthread_self());
//        //执行了下面的代码，就证明某一种条件不就绪，需要进行线程等待
//        //三个线程，都会在条件变量下排队
//        pthread_cond_wait(&cond, &mutex); //让对应的线程进行等待，等待被唤醒
//        cout << "thread id: " << pthread_self() << " run..." << endl;
//        for (auto &f : funcs) {
//            f();
//        }
//    }
//    cout << "thread id: " << pthread_self() << " end..." << endl;
//    return nullptr;
//}
//
//int main() {
//    funcs.push_back(show);
//    funcs.push_back(print);
//    funcs.push_back([](){
//        cout << "你好世界！" << endl;
//    });
//    pthread_cond_init(&cond, nullptr);
//
//    pthread_t t1, t2, t3;
//    pthread_create(&t1, nullptr, waitCommand, nullptr);
//    pthread_create(&t2, nullptr, waitCommand, nullptr);
//    pthread_create(&t3, nullptr, waitCommand, nullptr);
//
//    while (true) {
//        char n = 0;
//        cout << "请输入你的command(n/q)";
//        cin >> n;
//        if (n == 'n')
//            pthread_cond_signal(&cond);
//        else
//            break;
//         
//        sleep(1);
//    }
//
//    cout << "main thread quit" << endl;
//    //pthread_cond_broadcast(&cond); //唤醒线程
//   // pthread_cancel(t1);
//   // pthread_cancel(t2);
//   // pthread_cancel(t3);
//
//    //pthread_join(t1, nullptr);
//    //pthread_join(t2, nullptr);
//    //pthread_join(t3, nullptr);
//    
//    pthread_cond_destroy(&cond);
//
//    return 0;
//}
//