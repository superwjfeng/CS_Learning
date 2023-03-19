#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

using namespace std;

//__thread int global_value = 100; //局部存储
int global_value = 100; //临界资源，可能会造成数据不一致问题

void *startRoutine(void *args) {
    //pthread_detach(pthread_self()); //线程自己分离
    //cout << "线程分离" << endl;
    //访问临界资源的代码称为临界区
    while (true) {
        cout << "thread: " << pthread_self() << " |global_value: " << global_value << 
            " |&global_value: " << &global_value << " |Inc: " << global_value++ <<
            " |lwp: " << syscall(SYS_gettid) << endl;
        sleep(1);
    }
}

int main() {
    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;
    pthread_create(&tid1, nullptr, startRoutine, (void*)"thread1");
    pthread_create(&tid2, nullptr, startRoutine, (void*)"thread1");
    pthread_create(&tid3, nullptr, startRoutine, (void*)"thread1");

    //线程执行自己的startRoutine，主线程继续往下执行
    //但我们不知道到底是create出来的线程还是主线程先被调度
    //有一种可能是create后先调度主线程然后直接被join了，所以让主线程sleep一会
    sleep(1);

    pthread_detach(tid1); //让主线程来分离
    pthread_detach(tid2);
    pthread_detach(tid3);

    int n = pthread_join(tid1, nullptr);
    cout << n << ": " << strerror(n) << endl;
    n = pthread_join(tid2, nullptr);
    cout << n << ": " << strerror(n) << endl;
    n = pthread_join(tid3, nullptr);
    cout << n << ": " << strerror(n) << endl;

    return 0;
}