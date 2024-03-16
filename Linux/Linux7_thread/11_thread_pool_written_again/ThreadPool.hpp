#include <pthread.h>

#include <queue>
#include <vector>

#include "Log.hpp"
#include "Task.hpp"
#include "Thread.hpp"

static const int MAX_THREAD = 4;

class ThreadPool {
 public:
  // 在类内定义，为了避免参数不匹配（多一个this），所以要定义为static
  static void* routine(void* args) {
    ThreadData* td = static_cast<ThreadData*>(args);
    ThreadPool* tp = static_cast<ThreadPool*>(td->args_);
    Task* t = nullptr;

    while (true) {
      pthread_mutex_lock(tp->mtx_);
      while (tp->task_queue_->empty()) {
        pthread_cond_wait(tp->cond_, tp->mtx_);
      }
      t = tp->task_queue_->front();
      tp->task_queue_->pop();
      pthread_mutex_unlock(tp->mtx_);

      t->callback();
    }

    return nullptr;
  }

  void pushTask(Task* t) {
    // callback
    pthread_mutex_lock(mtx_);
    task_queue_->push(t);
    pthread_cond_signal(cond_);
    pthread_mutex_unlock(mtx_);
  }

  static ThreadPool* getInstance() {
    if (tp_ == nullptr) {
      pthread_mutex_lock(&mtx_tp_);
      if (tp_ == nullptr) {
        tp_ = new ThreadPool();
      }
      pthread_mutex_unlock(&mtx_tp_);
    }
    return tp_;
  }

 private:
  ThreadPool() {
    pthread_mutex_init(mtx_, NULL);
    pthread_cond_init(cond_, NULL);
    for (int i = 0; i < MAX_THREAD; i++) {
      threads_->push_back(new Thread(i, routine, this));
    }
  }

  ThreadPool(const ThreadPool& rhs) = delete;
  const ThreadPool& operator=(const ThreadPool& rhs) = delete;

 private:
  std::vector<Thread*>* threads_;  // 暂存Thread
  std::queue<Task*>* task_queue_;
  pthread_mutex_t* mtx_;
  static pthread_mutex_t mtx_tp_;  // 全局锁，用于单例
  pthread_cond_t* cond_;
  static ThreadPool* tp_;
};

ThreadPool* ThreadPool::tp_ = nullptr;
pthread_mutex_t ThreadPool::mtx_tp_ = PTHREAD_MUTEX_INITIALIZER;