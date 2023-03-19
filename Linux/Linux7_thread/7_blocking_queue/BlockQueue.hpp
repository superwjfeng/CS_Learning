#pragma once

#include <stdlib.h>
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <pthread.h>

using namespace std;

const uint32_t gDefaultCap = 5;

template<class T>
class BlockQueue { 
public:
    //同步式的阻塞队列：1需要有条件变量的方式来令双方在特定条件不满足的情况下进入不生产或不消费的情况
    //并且进入休眠，等待消费者在消费的时候唤醒生产者或者等待生产者在生产的时候唤醒消费者
    
    BlockQueue(uint32_t cap = gDefaultCap) :_cap(cap)
    {
        pthread_mutex_init(&_mutex, nullptr);
        pthread_cond_init(&_conCond, nullptr);
        pthread_cond_init(&_proCond, nullptr);
    }

    ~BlockQueue() {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_conCond);
        pthread_cond_destroy(&_proCond);
    }

    //生产函数
    void push(const T &in) { //const + &：纯输入
        lockQueue(); //加锁
        //判断是否适合生产，即判断bq是否满了

        //差错控制：虽然概率很低，但有可能被伪唤醒，所以条件判断不能用if，而是要用while多次检测
        while (isFull()) { //if (满) 不生产，休眠。若不休眠可能会不断的加锁解锁，可能会造成pop的饥饿
            //before：当等待的时候，会自动释放mutex
            proBlockWait(); //阻塞等待，等待被唤醒
            //after：当醒来的时候，是在临界区里醒来的，但此时没有锁了，会造成线程不安全吗？
            //不会！因为当阻塞结束返回到这里的时候，pthread_cond_wait，会自动重新获得mutex，然后才返回
            
        }
        pushCore(in); //else if (不满) 生产，唤醒消费者
        unlockQueue(); //解锁
        wakeupCon(); //唤醒消费者在解锁后还是解锁前没有影响
    }
    //消费接口
    T pop() { //输出型参数
        lockQueue();//加锁
        //判断是否适合消费，即判断bq是否为空
        while (isEmpty()) {//if(空) 不消费，休眠
            conBlockWait();            
        }
        //else if (有) 消费，唤醒生产者
        T tmp = popCore();
        unlockQueue();//解锁
        wakeupPro(); //唤醒生产者
        return tmp;
    }
//消费接口
private:
    void lockQueue() {
        pthread_mutex_lock(&_mutex);
    }

    void unlockQueue() {
        pthread_mutex_unlock(&_mutex);
    }
    
    bool isEmpty() {
        return _bq.empty();
    }

    bool isFull() {
        return _bq.size() == _cap;
    }

    void proBlockWait() { //生产者一定是在临界区中的
        //在阻塞线程的时候，会自动释放 &_mutex锁
        //因为在满足条件变量休眠等待时，一定在临界区中
        //若想让生产者被消费者唤醒，那么消费者必须要进入临界区中，那么消费者必须要拿到锁
        pthread_cond_wait(&_proCond, &_mutex); 

    }

    void conBlockWait() {
        //在阻塞线程的时候，会自动释放 &_mutex锁
        pthread_cond_wait(&_conCond, &_mutex);
    }

    void wakeupPro() { //唤醒生产者
        pthread_cond_signal(&_proCond);
    }
    
    void wakeupCon() { //唤醒消费者
        pthread_cond_signal(&_conCond);
    }

    void pushCore(const T& in) {
        _bq.push(in); //生产完成
    } 

    T popCore() {
        T tmp = _bq.front();
        _bq.pop();
        return tmp;
    }

private:
    queue<T> _bq; //blockqueue
    uint32_t _cap; //capacity
    pthread_mutex_t _mutex; //保护阻塞队列的互斥锁，生产消费用一把锁来达到二者互斥
    pthread_cond_t _conCond; //让消费者等待的条件变量
    pthread_cond_t _proCond; //让生产者等待的条件变量
};