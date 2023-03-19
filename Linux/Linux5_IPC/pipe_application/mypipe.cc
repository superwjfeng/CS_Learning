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

int main() {
    //0. 加载任务列表
    loadFunctor();
    //1. 创建管道
    int pipefd[2] = {0};
    if (pipe(pipefd) != 0) {
        cerr << "pipe error" << endl;
        return 1;
    }

    // 2.创建子进程
    pid_t id = fork();
    if (id < 0) {
        cerr << "fork error" << endl;
        return 2;
    }
    else if (id == 0) {
        //child
        //3.关闭不需要的文件fd，关闭写端
        close(pipefd[1]);
        //4.业务处理
        while (true) {
            //若管道里有数据就读取，若没有任务就会阻塞在管道的read，等待任务的到来
            uint32_t operatorType = 0;
            ssize_t s = read(pipefd[0], &operatorType, sizeof(uint32_t));

            if (s == 0) {
                cout << "退出" << endl;
                break;
            }
            
            assert(s == sizeof(uint32_t)); //必须保证读取的字节数无误   
            //debug模式，assert有效，release中assert就无效了
            //一旦断言没有了，相当于s就没有被使用过，此时在release中就会报warning
            //因此要进行强转使用
            (void)s;
            if (operatorType < functors.size()) {
                functors[operatorType](); //执行任务
            }
            else {
                cerr << "bug? operatorType = " << operatorType << endl;
            }
        }

        close(pipefd[0]);
        exit(0);
    }
    else {
        //parent
        srand((long long)time(nullptr));
        //3.关闭不需要的文件fd，关闭读端
        close(pipefd[0]);

        //4.指派任务
        int num = functors.size();
        int cnt = 10;
        while (cnt--) {
            //5.形成任务码后
            uint32_t commandCode = rand() % num;
            cout << "父进程指派任务完成，任务是：" << info[commandCode] << "任务的编号是" << cnt << endl;
            //通过管道向指定的进程发送任务指令
            write(pipefd[1], &commandCode, sizeof(uint32_t));
            sleep(1);
        }
        close(pipefd[1]);
        pid_t res = waitpid(id, nullptr, 0); //等待子任务
        if(res)
            cout << "wait success" << endl;
    }

    return 0;
}