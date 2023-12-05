#include "BlockQueue.hpp"
#include "Task.hpp"

////int队列
// void *consumer(void *args) {
//     BlockQueue<int> *bqp = static_cast<BlockQueue<int> *>(args);
//     while (true) {
//         int data = bqp->pop();
//         cout << "consumer 消费数据完成：" << data << endl;
//         sleep(2); //消费慢一点
//     }
// }
//
// void *producer(void *args) {
//     BlockQueue<int> *bqp = static_cast<BlockQueue<int> *>(args);
//     while (true) {
//         //1.制作数据
//         int data = rand()%10;
//         //2.生产数据
//         bqp->push(data);
//         cout << "producer 生产数据完成：" << data << endl;
//         //sleep(2); //生产慢一些
//     }
// }

const std::string ops = "+-*/%";

// Task队列
void *consumer(void *args) {
  BlockQueue<Task> *bqp = static_cast<BlockQueue<Task> *>(args);
  while (true) {
    Task t = bqp->pop();  // 消费任务
    int result = t();     // 处理消费的任务
    int one, two;
    char op;
    t.get(&one, &two, &op);
    cout << "consumer[" << pthread_self() << "]" << (unsigned long)time(nullptr)
         << "消费了一个任务" << one << op << two << "=" << result << endl
         << endl;
    // sleep(2); //消费慢一些
  }
}

void *producer(void *args) {
  BlockQueue<Task> *bqp = static_cast<BlockQueue<Task> *>(args);
  while (true) {
    // 1.制作任务
    int one = rand() % 10;
    int two = rand() % 20;
    char op = ops[rand() % ops.size()];
    Task t(one, two, op);
    // 2.生产任务
    bqp->push(t);
    cout << "producer[" << pthread_self() << "]" << (unsigned long)time(nullptr)
         << "生产了一个任务" << one << op << two << "=?" << endl;
    sleep(2);  // 生产慢一些
  }
}

int main() {
  srand((unsigned long)time(nullptr) ^ getpid());
  // 定义一个阻塞队列
  // 创建两个线程 producer，consumer
  // BlockQueue<int> bq;

  // queue中可以可以放任何类型的数据，那么就也可以放自己封装的任务
  // 生产者生产计算任务，消费者完成计算任务

  BlockQueue<Task> bq;

  pthread_t c, p;
  pthread_create(&c, nullptr, consumer, &bq);
  pthread_create(&p, nullptr, producer, &bq);

  pthread_join(c, nullptr);
  pthread_join(p, nullptr);

  return 0;
}