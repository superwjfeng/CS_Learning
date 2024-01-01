#include <ctime>

#include "Task.hpp"
#include "ThreadPool.hpp"

int main() {
  const string operators = "+-*/%";
  unique_ptr<ThreadPool<Task>> tp(new ThreadPool<Task>());
  tp->start();

  srand((unsigned long)time(nullptr) ^ getpid() ^ pthread_self());
  // 派发任务的线程
  while (true) {
    int one = rand() % 50;
    int two = rand() % 10;
    char oper = operators[rand() % operators.size()];
    Log() << "主线程派发计算任务：" << one << oper << two << "=?" << endl;
    Task t(one, two, oper);
    tp->push(t);
    sleep(1);
  }

  return 0;
}