#ifndef _THREAD_POOL_H_INCLUDED_
#define _THREAD_POOL_H_INCLUDED_

#include "thread.h"

#define DEFAULT_THREADS_NUM 4
#define DEFAULT_QUEUE_NUM 65535  // 任务队列长度

typedef unsigned long atomic_uint_t;
typedef struct thread_task_s thread_task_t;
typedef struct thread_pool_s thread_pool_t;

struct thread_task_s {
  thread_task_t *next;  // 队列中的下一个任务
  uint_t id;            // 任务编号
  void *ctx;  // context for tast，需要传递给下面的handler的参数/上下文
  void (*handler)(void *data);  // 需要被调用的处理函数的句柄
};

typedef struct {
  thread_task_t *first;  // 首节点
  thread_task_t **last;  // last用于尾插
} thread_pool_queue_t;

#define thread_pool_queue_init(q) \
  (q)->first = NULL;              \
  (q)->last = &(q)->first

struct thread_pool_s {
  pthread_mutex_t mtx;        // 互斥锁
  thread_pool_queue_t queue;  // 消息队列
  int_t waiting;              // 队列中在等待调度的任务数
  pthread_cond_t cond;        // 同步

  char *name;       // 线程池的名字
  uint_t threads;   // 线程池容量（最大线程数）
  int_t max_queue;  // 队列的最大长度
};

thread_task_t *thread_task_alloc(size_t size);  // 初始化任务，加入队列
int_t thread_task_post(thread_pool_t *tp, thread_task_t *task);  // 发布任务
thread_pool_t *thread_pool_init();            // 线程池初始化
void thread_pool_destroy(thread_pool_t *tp);  // 线程池销毁

#endif /* _THREAD_POOL_H_INCLUDED_ */
