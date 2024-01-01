#pragma once

#include <semaphore.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int gCap = 5;

template <class T>
class RingQueue {
 public:
  RingQueue(int cap = gCap)
      : _ringqueue(cap),
        _pIndex(0),
        _cIndex(0)  // 默认index都为0
  {
    // 生产者使用
    sem_init(&_roomSem, 0, _ringqueue.size());
    // 消费者使用
    sem_init(&_dataSem, 0, 0);
    pthread_mutex_init(&_pmutex, nullptr);
    pthread_mutex_init(&_cmutex, nullptr);
  }
  ~RingQueue() {
    sem_destroy(&_roomSem);
    sem_destroy(&_dataSem);
    pthread_mutex_destroy(&_pmutex);
    pthread_mutex_destroy(&_cmutex);
  }
  // 生产
  void push(const T &in) {
    // 信号量是一种预定机制，只要申请到了就一定会有，因此不用加锁
    sem_wait(&_roomSem);
    pthread_mutex_lock(&_pmutex);  // 锁用来保护写入
    _ringqueue[_pIndex] = in;      // 生产的过程
    _pIndex++;                     // 写入位置后移
    _pIndex %= _ringqueue.size();  // 更新下标，来保证环形特征
    pthread_mutex_unlock(&_pmutex);
    sem_post(&_dataSem);
  }
  // 消费
  T pop() {
    sem_wait(&_dataSem);
    pthread_mutex_lock(&_cmutex);
    T temp = _ringqueue[_cIndex];
    _cIndex++;
    _cIndex %= _ringqueue.size();  // 更新下标
    pthread_mutex_unlock(&_cmutex);
    sem_post(&_roomSem);
    return temp;
  }

 private:
  vector<T> _ringqueue;  // 环形队列
  sem_t _roomSem;        // producer关心的空间信号量计数器
  sem_t _dataSem;        // consumer关心的数据信号量计数器
  uint32_t _pIndex;  // 生产者当前读取位置的下标，若是多线程则为临界资源
  uint32_t _cIndex;  // 消费者当前读取位置的下标，若是多线程则为临界资源

  pthread_mutex_t _pmutex;
  pthread_mutex_t _cmutex;
};