#include <iostream>
#include <assert.h>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <cstdlib>
#include <unistd.h>
using namespace std;

typedef void(*functor)(); //函数指针
vector<functor> functors; //方法集合

//for debug
unordered_map<uint32_t, string> info;

void f1() {
    cout << "这是一个处理日志的任务，执行的PID为：[" << getpid() <<
     "]" << "执行时间是[" << time(nullptr) << endl;
    //实际的任务代码
}

void f2() {
    cout << "这是一个备份数据任务，执行的PID为：[" << getpid() <<
     "]" << "执行时间是[" << time(nullptr) << endl;
}

void f3() {
    cout << "这是一个处理网络链接的任务，执行的PID为：[" << getpid() <<
     "]" << "执行时间是[" << time(nullptr) << endl;
}

void loadFunctor() {
    info.insert({functors.size(), "处理日志任务"});
    functors.push_back(f1);   
    info.insert({functors.size(), "备份数据任务"});
    functors.push_back(f2);   
    info.insert({functors.size(), "处理网路连接的任务"});
    functors.push_back(f3);
}

//int32_t：进程pid，int32_t：该进程对应的管道写端fd
typedef pair<int32_t, int32_t> elem;
vector<elem> assignMap;
int processNum = 5;

void work(int blockFd) {
    cout << "进程[" << getpid() << "]" << "开始工作" << endl;
    //子进程核心工作代码
    while (true) {
        //a. 阻塞等待 b.获取 任务信息
        uint32_t operatorCode = 0;
        ssize_t s = read(blockFd, &operatorCode, sizeof(uint32_t));
        if (s==0) break;
        assert(s == sizeof(uint32_t));
        (void)s;
        //c. 处理任务
        if (operatorCode < functors.size()) {
            functors[operatorCode]();
        }
    }
    cout << "进程[" << getpid() << "]" << "结束工作" << endl;
}

//[子进程pid，子进程管道fd]
void balanceSendTask(const vector<elem> &processFds) {
    srand((long long)time(nullptr));
    while (true) {
        sleep(1);
        //选择一个进程，选择进程是随机的，没有专挑一个进程给任务
        //较为均匀的将任务给所有的子进程 -- 负载均衡
        uint32_t pick = rand() % processFds.size();
        //选择一个任务
        uint32_t task = rand( )% functors.size();
        //把任务给一个指定的进程
        write(processFds[pick].second, &task, sizeof(task));
        //打印对应的提示信息
        cout << "父进程指派任务：" << info[task] << "给进程：" << processFds[pick].first << "编号：" << pick << endl;
    }
}

int main() {
    //加载任务列表
    loadFunctor();
    //创建processNum个进程
    for (int i = 0; i< processNum; i++) {
        //定义保存管道fd的对象
        int pipefd[2] = {0};
        //创建管道
        pipe(pipefd);
        //创建子进程
        pid_t id = fork();
        if (id == 0) {
            close(pipefd[1]);
            //子进程执行
            work(pipefd[0]);
            exit(0);
        }
        //父进程收集子进程的pid和管道fd
        close(pipefd[0]);
        elem e(id, pipefd[1]); //得到子进程的pid和管道id
        assignMap.push_back(e);
    }
    cout << "creawte all process success!" << endl;
    //父进程派发任务
    balanceSendTask(assignMap);
    
    //回收资源
    for (int i=0; i<processNum; i++) {
        if (waitpid(assignMap[i].first, nullptr, 0)) {
            cout << "wait for: pid=" << assignMap[i].first << "wait success!"
            << "number: " << i << endl;
        }
        close(assignMap[i].second);
    }
    return 0;
}