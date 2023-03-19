#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <string>

using namespace std;

void *callback1(void *args) {
    string name = (char*)args;
    while (true) {
        cout << name << endl;
        sleep(1);
    }    
}
void *callback2(void *args) {
    string name = (char*)args;
    while (true) {
        cout << name << endl;
        sleep(1);
    }    
}

int main() {
    pthread_t tid1;
    pthread_t tid2;

    pthread_create(&tid1, nullptr, callback1, (void*)"thread 1");
    pthread_create(&tid2, nullptr, callback2, (void*)"thread 2");

    while (true) {
        cout << "我是主线程" << endl;
        sleep(1);
    }    

    pthread_join(tid1, nullptr);
    pthread_join(tid2, nullptr);

    return 0;
}