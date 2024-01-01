#include <pthread.h>
class Mutex {
 public:
  Mutex() { pthread_mutex_init(mtx_, NULL); }
  void lock() { pthread_mutex_lock(mtx_); }
  void unlock() { pthread_mutex_unlock(mtx_); }
  ~Mutex() { pthread_mutex_destroy(mtx_); }

 private:
  pthread_mutex_t *mtx_;
};

class LockGuard {
 public:
  LockGuard(Mutex *mutex) : mutex_(mutex) { mutex->lock(); }
  ~LockGuard() { mutex_->unlock(); }

 private:
  Mutex *mutex_;
};