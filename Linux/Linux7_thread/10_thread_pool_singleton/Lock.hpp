#pragma once

#include <pthread.h>

#include <iostream>

class Mutex {
  public:
    Mutex() { pthread_mutex_init(&_lock, nullptr); }
    void lock() { pthread_mutex_lock(&_lock); }
    void unlock() { pthread_mutex_unlock(&_lock); }
    ~Mutex() { pthread_mutex_destroy(&_lock); }

  private:
    pthread_mutex_t _lock;
};

// RAII 的加锁风格
class LockGuard {
  public:
    LockGuard(Mutex *mutex) : _mutex(mutex) {
        _mutex->lock();
        std::cout << "加锁成功..." << std::endl;
    }

    ~LockGuard() {
        _mutex->unlock();
        std::cout << "解锁成功...." << std::endl;
    }

  private:
    Mutex *_mutex;
};
