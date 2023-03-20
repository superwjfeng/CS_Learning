#include <iostream>
#include <sys/select.h>
#include "sock.hpp"

using namespace std;

static void usage(std::string process)
{
    cerr << "\nUsage: " << process << " port\n" << endl;
}

//select需要借助第三方的数组来保存所有历史上合法的fd
#define NUM (sizeof(fd_set) * 8)
#define DFL -1 //默认值是-1，也就是没有被使用
int fdsArray[NUM] = {0}; //用来保存历史上所有的合法fd，用vector更好，原生用的是普通数组
int gnum = sizeof(fdsArray)/sizeof(fdsArray[0]);

// readfds：包含已经就绪的fd
static void HandlerEvent(int listenSock, fd_set &readfds)
{
    //找出已经就绪的fd
    if (FD_ISSET(listenSock, &readfds))
    {
        //有了一个新连接
        cout << "已经有一个新连接到来了，需要读取（获取+拷贝）" << endl;
        string clientIp;
        uint16_t clientPort = 0;
        int sock = Sock::Accept(listenSock, &clientIp, &clientPort); //不会再阻塞了
        if (sock < 0) return;
        cout << "获取新连接成功：" << clientIp << ":" << clientPort << " | sock：" << sock << endl;
        //不能用read和write，因为它们不知道底层数据是否就绪，要用select
        //想办法把新的fd托管给select

    }
}

// ./selectServer 8080
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        usage(argv[0]);
        exit(1);
    }
    //fd_set fds; //fd_set是用位图表示多个fd的文件描述符集合
    //cout << sizeof(fds) << "Byte" << endl;
    int listenSock = Sock::Socket();
    Sock::Bind(listenSock, atoi(argv[1]));
    Sock::Listen(listenSock);

    for (int i=0; i < gnum; i++) fdsArray[i] = DFL; //default
    fdsArray[0] = listenSock;

    while (true)
    {
        int maxFd = DFL;
        fd_set readfds;
        FD_ZERO(&readfds); //清空
        for (int i = 0; i < gnum; i++)
        {
            if (fdsArray[i] == DFL) continue; //过滤不合法的fd
            FD_SET(fdsArray[i], &readfds); //添加所有的合法fd到readfds中，方便select统一进行就绪监听
            if (maxFd < fdsArray[i]) maxFd = fdsArray[i]; //找出最大值
        }
        //因为select使用的是输入输出参数，所以每次等待都需要重新设置参数
        //int maxFd = listenSock;
        FD_SET(listenSock, &readfds); //往集合里添加套接字fd
        struct timeval timeout = {100 , 0};

        //监听socket后，accept之前，需要完成三次握手，因此本质上也是IO的过程
        //握手完成的连接称为读事件就绪，listenSock也只关心读事件就绪
        //accept = 读+拷贝，所以用accpt之前用改用select等待
        int n = select(maxFd+1, &readfds, nullptr, nullptr, &timeout); //经过一段事件后往下走
        //int n = select(maxFd+1, &readfds, nullptr, nullptr, nullptr); //任何一个事件都没有就绪时，永久阻塞
        switch(n)
        {
        case 0:
            cout << "time out ... " << (unsigned long)time(nullptr) << endl;
            break;
        case -1:
        cerr << errno << " : " << strerror(errno) << endl;
            break;
        default:
            cout << "listensock event就绪" << endl;
            HandlerEvent(listenSock, readfds);
            //等待成功
            //1. 刚启动的时候，只有一个fd，即listenSock
            //2. server运行的时候，sock才会慢慢变多
            //3. select是使用位图，采用输入输出型参数的方式，来进行内核和用户之间的信息传递
            //所以每一次调用select，都要重新设置历史数据和sork
            //4. listenSock永远都要被设置进readfds中
            break;
        }
        //int sock = Sock::Accept(listenSock,)
    }

    return 0;
}