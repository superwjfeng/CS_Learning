#pragma once

#include <pthread.h>
#include <unistd.h>

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <queue>

#include "Log.hpp"

using namespace std;

int gThreadNum = 5;
template <class T>
class ThreadPool {
 public:
  ThreadPool(int threadNum = gThreadNum)
      : _threadNum(threadNum), _isStart(false) {
    assert(_threadNum > 0);
    pthread_mutex_init(&_mutex, nullptr);
    pthread_cond_init(&_cond, nullptr);
  }

  ~ThreadPool() {
    pthread_mutex_destroy(&_mutex);
    pthread_cond_destroy(&_cond);
  }

 public:
  ////类内成员函数有this指针，所以实际上传了两个参数，所以不能这么写
  // void *threadRoutine(void *args) {
  //     while (1) {
  //         sleep(1);
  //         cout << "pthread[" << pthread_self() << "] running..." << endl;
  //     }
  // }

  static void *threadRoutine(void *args) {
    pthread_detach(pthread_self());
    ThreadPool<T> *tp = static_cast<ThreadPool<T> *>(args);
    while (1) {
      tp->lockQueue();           // 没有this指针，只能靠接口来获取
      while (!tp->haveTask()) {  // 没有任务的时候等待
        tp->waitForTask();
      }
      T t = tp->pop();
      // 任务被拿到了线程的上下文中
      tp->unlockQueue();
      // For debug
      int one, two;
      char oper;
      t.get(&one, &two, &oper);

      // 所有的任务都必须有一个run方法
      Log() << "新线程完成计算任务：" << one << oper << two << "=" << t.run()
            << endl;
    }
  }

  void start() {  // 所有线程跑起来
    assert(!_isStart);
    for (int i = 0; i < _threadNum; i++) {
      pthread_t temp;
      pthread_create(&temp, nullptr, threadRoutine, this);
    }
    _isStart = true;
  }

  void push(const T &in) {  // 放任务
    lockQueue();
    _taskQueue.push(in);
    chooseThreadForHandler();  // 选择线程执行
    unlockQueue();
  }

 private:
  void lockQueue() { pthread_mutex_lock(&_mutex); }
  void unlockQueue() { pthread_mutex_unlock(&_mutex); }
  bool haveTask() { return !_taskQueue.empty(); }
  void waitForTask() { pthread_cond_wait(&_cond, &_mutex); }
  void chooseThreadForHandler() {
    pthread_cond_signal(
        &_cond);  // 条件变量自带队列进行阻塞等待，实现轮询方案的负载均衡
  }
  T pop() {
    T temp = _taskQueue.front();
    _taskQueue.pop();
    return temp;
  }

 private:
  bool _isStart;
  int _threadNum;
  queue<T> _taskQueue;
  pthread_mutex_t _mutex;
  pthread_cond_t _cond;
};