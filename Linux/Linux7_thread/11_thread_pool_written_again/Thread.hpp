#include <pthread.h>

#include <cstdio>
#include <string>

typedef void *(*routine)(void *);

// 封装callbcak参数
class ThreadData {
 public:
  void *args_;
  std::string name_;  // Thread name
};

class Thread {
 public:
  Thread(int num, routine tp_routine, void *args) : tp_routine_(tp_routine) {
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "Thread-%d", num);
    name_ = buffer;
    tdata_->args_ = args;
    tdata_->name_ = name_;
  }
  void thread_run() { pthread_create(&tid_, NULL, tp_routine_, tdata_); }

 private:
  std::string name_;  // 用name来更好的表示thread
  ThreadData *tdata_;
  routine tp_routine_;
  pthread_t tid_;
};