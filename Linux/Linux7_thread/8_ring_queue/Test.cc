#include "RingQueue.hpp"
#include <ctime>
#include <unistd.h>

void *producer(void *args) {
    RingQueue<int> *rqp = static_cast<RingQueue<int> *>(args);
    while (true) {
        int data = rand() % 10;
        rqp->push(data);
        cout << "pthread[" << pthread_self() << "]" << "生产了一个数据：" << data << endl;
        //sleep(2);
    }

}

void *consumer(void *args) {
    RingQueue<int> *rqp = static_cast<RingQueue<int> *>(args);
    while (true) {
        int data = rqp->pop();
        cout << "pthread[" << pthread_self() << "]" << "消费了一个数据：" << data << endl;
        sleep(2);
    }
}

int main() {
    srand((unsigned long)time(nullptr) ^ getpid());

    RingQueue<int> rq;

    pthread_t c1, c2, c3, p1, p2, p3;
    pthread_create(&p1, nullptr, producer, &rq);
    pthread_create(&p2, nullptr, producer, &rq);
    pthread_create(&p3, nullptr, producer, &rq);
    pthread_create(&c1, nullptr, consumer, &rq);
    pthread_create(&c2, nullptr, consumer, &rq);
    pthread_create(&c3, nullptr, consumer, &rq);

    pthread_join(c1, nullptr);
    pthread_join(c2, nullptr);
    pthread_join(c3, nullptr);
    pthread_join(p1, nullptr);
    pthread_join(p2, nullptr);
    pthread_join(p3, nullptr);

    return 0;
}