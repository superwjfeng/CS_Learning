#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

int global_value = 100;

static void printTid(const char* name, const pthread_t &tid) {
    printf("%s is running, thread ID: 0X%x, global_value :%d\n",
    name, tid, global_value);
}

void* startRoutine(void* args) {
    const char* name = static_cast<const char*>(args);
    int cnt = 5;
    while (true) {
        printTid(name, pthread_self());
        sleep(1);
        if (!(cnt--)) {
            global_value = 200;
        }
    }
    int *p = new int(10);
    cout << "线程退出" << endl;
    return (void*)p;
    //1. 线程退出的方式，return
    //return (void*)111;
    //2. 线程退出的方式，pthread_exi
    //pthread_exit((void*)111);
}

int main() {
    pthread_t tid;
    int n = pthread_create(&tid, nullptr, startRoutine, (void*)"thread1");
    ////cout << "new thread id: " << tid << endl;    
    ////sleep(10);

    //sleep(2);

    //3.线程退出的方式，给线程发送取消请求，若线程是被取消的，则退出结果为-1
    //3.1 main thread cancel new thread，反过来是不推荐的
    //pthread_cancel(tid);
    (void)n;
    cout << "new thread been canceld" << endl;

    
    while (true) {
        printTid("main thread", pthread_self());
        sleep(1);
    }

    void* ret = nullptr;
    pthread_join(tid, &ret);
    cout << "main thread join success, *ret: " << *((int*)ret) << endl;
    delete (int*)ret;
    pthread_attr_t
    return 0;
}
