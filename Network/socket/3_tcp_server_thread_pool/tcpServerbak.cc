#include "util.hpp"
#include "ThreadPool.hpp"
#include "Task.hpp"
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

class ServerTcp; //申明以下ServerTcp

class ThreadData
{
public:
    ThreadData(uint16_t port, std::string ip, int sock, ServerTcp *ts)
        :_clientPort(port), _clientIP(ip), _sock(sock), _this(ts)
    {}
public:
    uint16_t _clientPort;
    std::string _clientIP;
    int _sock;
    ServerTcp *_this;
};

class ServerTcp
{
public:
    ServerTcp(uint16_t port, const std::string &ip = "")
        :_port(port), _ip(ip), _listenSock(-1), _tp(nullptr)
    {}
    ~ServerTcp() {}
public:
    void init()
    {
        //1. 创建套接字
        _listenSock = socket(PF_INET, SOCK_STREAM, 0); //默认是流式服务
        if (_listenSock < 0)
        {
            logMessage(FATAL, "socket: %s", strerror(errno));
            exit(SOCKET_ERR);    
        }
        logMessage(DEBUG, "socket: %s, %d", strerror(errno), _listenSock);
        //2. bind
        //2.1 填充服务器信息
        struct sockaddr_in local; //用户栈上
        memset(&local, 0, sizeof(local)); //清空
        local.sin_family = PF_INET; //和AF_INET是一样的
        local.sin_port = htons(_port);
        _ip.empty() ?\
            (local.sin_addr.s_addr = INADDR_ANY) :\
            (inet_aton(_ip.c_str(), &local.sin_addr));

        //2.2 本地socket信息，写入_sock对应的内核区域
        if (bind(_listenSock, (const struct sockaddr*)&local, sizeof(local)) == -1)
        {
            logMessage(FATAL, "bind: %s", strerror(errno));
            exit(BIND_ERR);
        }
        logMessage(DEBUG, "bind: %s, %d", strerror(errno), _listenSock);
        
        //3. 监听socket，tcp是面向连接的。所谓面向的意思就是在做任何事情之前先干什么
        //比如面向对象就是先要创建对象
        if (listen(_listenSock, 5)<0)
        {
            logMessage(FATAL, "listen: %s", strerror(errno));
            exit(LISTEN_ERR);
        }
        logMessage(DEBUG, "listen: %s, %d", strerror(errno), _listenSock);

        //允许别人来连接了

        //4. 加载线程池
        _tp = ThreadPool<Task>::getInstance();
    }

    static void *threadRoutine(void *args)
    {
        pthread_detach(pthread_self()); //设置线程分离
        ThreadData *td = static_cast<ThreadData *>(args);
        td->_this->transService(td->_sock, td->_clientIP, td->_clientPort);
        delete td;
        return nullptr;
    }

    void loop()
    {
        _tp->start(); //启动线程池
        logMessage(DEBUG, "thread pool start success, thread num: %d", _tp->threadNum());

        while (true)
        {
            //测试
            //logMessage(DEBUG, "providing server service start ...");
            //sleep(1);
            
            //signal(SIGCHLD, SIG_IGN); //Only Linux valid
            ////SIG_IGN 忽略，子进程在终止时会自动清理掉,不会产生僵尸进程，也不会通知父进程

            struct sockaddr_in peer; //连接者信息
            socklen_t len = sizeof(peer);
            //5. 获取连接，accept的返回值是一个新的套接字文件描述符
            int serviceSock = accept(_listenSock, (struct sockaddr *)&peer, &len);

            if (serviceSock < 0)
            {//获取连接失败
                logMessage(WARNING, "accept: %s[%d]", strerror(errno), serviceSock);
                continue; //继续获取   
            }
            //5.1 获取客户端基本信息
            int peerPort = ntohs(peer.sin_port);
            std::string peerIP = inet_ntoa(peer.sin_addr);

            logMessage(DEBUG, "accept: %s | %s:%d, socket fd: %d",\
                strerror(errno), peerIP.c_str(), peerPort, serviceSock);

            //6 v3版本 threadPool
            //6.1 构建任务
            Task t(serviceSock, peerIP, peerPort,\
                std::bind(&ServerTcp::transService, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            _tp->push(t); //push进线程池，由线程池进行分发

        }
    }

    //提供大小写转换服务 
    //UDP和TCP都支持全双工通信
    void transService(int sock, const std::string &clientIP, uint16_t clientPort)
    {
        assert(sock >= 0);
        assert(!clientIP.empty());
        assert(clientPort >= 1024);
        
        char inbuffer[BUFFER_SIZE];

        while (true)
        { 
            //读取字节流直接用read
            ssize_t s = read(sock, inbuffer, sizeof(inbuffer)-1); //我们认为读到的都是字符串
            if (s > 0)
            {
                // read success
                inbuffer[s] = '\0';
                if (strcasecmp(inbuffer, "quit") == 0) //strcasecmp是无视大小写进行字符串比较
                {
                    logMessage(DEBUG, "client quit -- %s[%d]", clientIP.c_str(), clientPort);
                    break;
                }
                logMessage(DEBUG, "trans before: %s[%d]>>> %s", clientIP.c_str(), clientPort, inbuffer);
                //提供服务
                for (int i = 0; i < s; i++)
                {
                    if (isalpha(inbuffer[i]) && islower(inbuffer[i]))
                    {
                        inbuffer[i] = toupper(inbuffer[i]);
                    }
                }
                logMessage(DEBUG, "trans after: %s[%d]>>> %s", clientIP.c_str(), clientPort, inbuffer);
                write(sock, inbuffer, strlen(inbuffer));
            }
            //差错控制
            else if (s == 0)
            {
                // pipe: 读端一直在读，写端不写了，并且关闭了写端，会读到 s==0，代表对面端口关闭了
                // s==0 代表对方关闭，client退出
                logMessage(DEBUG, "client quit -- %s[%d]", clientIP.c_str(), clientPort);
                break;
            }
            else
            {
                //读取出错
                logMessage(DEBUG, "%s[%d] - read: %s", clientIP.c_str(), clientPort, strerror(errno));
                break;
            }
        }
        //只要走到这里，一定是client退出了，服务到此结束
        close(sock); //若一个进程对应的fd，打开了但没有被归还，称为文件描述符泄漏
        logMessage(DEBUG, "server close %d done", sock);
    }
private:
    int _listenSock; //套接字
    uint16_t _port; //端口号
    std::string _ip;
    ThreadPool<Task> *_tp;//线程池
};

static void Usage(std::string proc)
{
    std::cerr << "Usage:\n\t" << proc << "port ip" << std::endl;
    std::cerr << "Example:\n\t" << proc << "8080 127.0.0.1\n" << std::endl;
}

// ./tcpServer local_port local_ip
// local_ip 为空的时候会自己填充
int main(int argc, char *argv[])
{
    if (argc != 2 && argc !=3)
    {
        Usage(argv[0]);
        exit(USAGE_ERR);
    }

    uint16_t port = atoi(argv[1]);
    std::string ip;
    if (argc == 3)
    {
        ip = argv[2];
    }

    ServerTcp svr(8080);
    svr.init();
    svr.loop();
    return 0;
}