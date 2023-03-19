#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <unordered_map>
#include <ctype.h> //toupper
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Log.hpp"

static void Usage(const std::string proc)
{
    std::cout << "Usage:\n\t" << proc << " port [ip]" << std::endl; 
}

//@brief: 写一个简单的updServer
//云服务器有一些特殊情况
//1. 禁止bind云服务器上的任何确定IP，只能使用INADDR_ANY
class UdpServer {
public:
    UdpServer(int port, std::string ip=""):_port((uint16_t)port), _ip(ip), _sockfd(-1)//初始化列表设为1，用init接口进行创建
    {

    }
    ~UdpServer() {}
public:
    void init() 
    {
        //1. 创建socket套接字 相当于打开了一个文件
        _sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
        if (_sockfd < 0)
        {
            logMessage(FATAL, "socket: %s:%d", strerror(errno), _sockfd);
            exit(1);
        }
        logMessage(DEBUG, "socket create success: %d", _sockfd);
        
        //2. 绑定网路信息，指定ip:port
        //2.1 先填充基本信息到 struct sockaddr_in

        //local是在用户栈开辟的临时变量，要进行bind写入到内核中
        struct sockaddr_in local;
        bzero(&local, sizeof(local)); //初始化，也可以用memset
        
        //填充协议家族
        local.sin_family = AF_INET; 

        //填充服务器对应的端口号信息，端口号一定要相互传输，所以要转大端
        local.sin_port = htons(_port);         

        //服务器必须具有IP地址，"xx.yy.zz.aaa" 字符串风格的点分十进制
        //若使用字符串要用十多个字节，一般要转换为4字节IP地址 uint32_t ip
        //struct ip //位段
        //{
        //    uint32_t part1:8;
        //    uint32_t part2:8;
        //    uint32_t part3:8;
        //    uint32_t part4:8;
        //}
        //struct ip ip_;
        //ip._part1 = substr(ip);

        //INADDR_ANY(0)：程序员不关心会bind到哪一个ip，有些时候host会有多个ip
        //任意地址bind，强烈推荐的做法，所有服务器一般的做法
        //inet_addr 进行指定绑定到具体的ip，特殊用途，或者测试时使用。除了做转化，还自动进行hton
        local.sin_addr.s_addr = _ip.empty() ? htonl(INADDR_ANY) : inet_addr(_ip.c_str());

        //2.2 绑定网络信息
        if (bind(_sockfd, (const struct sockaddr*)&local, sizeof(local)) == -1)
        {
            logMessage(FATAL, "bind: %s:%d", strerror(errno), _sockfd);
            exit(2);
        }
        //对于udp服务器完成了
        logMessage(DEBUG, "socket bind success: %d", _sockfd);
    }

    void start()
    {
        char inbuffer[1024]; //将来读取到的数据，都放在这里
        char outbuffer[1024]; //将来要发送的数据
        while (true)
        { 
            struct sockaddr_in peer; //输出型参数
            socklen_t len = sizeof(peer); //输入输出型参数
            //demo2, recvfrom是udp特有的读取信息
            //回消息：后面两个是输出型参数
            ssize_t s = recvfrom(_sockfd, inbuffer, sizeof(inbuffer)-1, 0,\
                (struct sockaddr *)&peer, &len);

            if (s > 0)
            {
                inbuffer[s] = 0; //当作字符串
            }
            else if (s == -1)
            {
                logMessage(WARNING, "recvfrom: %s:%d", strerror(errno), _sockfd);
                continue;
            }
            
            //读取成功，除了读取到对方的数据，还要读取到对方的网络地址 ip:port
            std::string peerIP = inet_ntoa(peer.sin_addr); //对方的IP，将四字节IP转换成字符串方便使用
            uint32_t peerPort = ntohs(peer.sin_port); //对方的端口号
            
            checkOnlineUser(peerIP, peerPort, peer); //如果存在，什么都不做；如果不存在，就添加

            //打印出来客户端给服务器发送过来的消息
            logMessage(NOTICE, "[%s:%d]# %s", peerIP.c_str(), peerPort, inbuffer);

            ////接收到信息后将小写转换成大写后转发回client
            //for (int i=0; i<strlen(inbuffer); i++)
            //{
            //    if (isalpha(inbuffer[i]) && islower(inbuffer[i]))
            //    {
            //        outbuffer[i] = toupper(inbuffer[i]);
            //    }
            //    else
            //    {
            //        outbuffer[i] = toupper(inbuffer[i]);
            //    }
            //}
            messageRoute(peerIP, peerPort, inbuffer); //消息路由转发给所有人

            //demo1
            //logMessage(NOTICE, "Server providing service...");
            //sleep(1);
        }
    }

    void checkOnlineUser(std::string &ip, uint32_t port, struct sockaddr_in &peer)
    {
        std::string key = ip;
        key = ":";
        key += std::to_string(port);
        auto iter = users.find(key);
        if (iter == users.end())
        {//没找到
            users.insert({key, peer});
        }
        else
        {
            // do nothing
        }
            
    }

    void messageRoute(std::string ip, uint32_t port, std::string info)
    {
        std::string message = "[";
        message += ip;
        message += ":";
        message += std::to_string(port);
        message += "]";
        message += info;
        for (auto &user : users)
        {
            sendto(_sockfd, message.c_str(), message.size(), 0, (struct sockaddr *)&user.second, sizeof(user.second));
        }
    }
private:
    uint16_t _port; //服务器必须要有端口号信息
    std::string _ip;
    int _sockfd; //服务器的socket fd信息
    std::unordered_map<std::string , struct sockaddr_in> users; //记录用户信息

};




// ./udpServer port [ip]
int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3) {
        Usage(argv[0]);
        exit(3);
    }

    uint16_t port = atoi(argv[1]);

    std::string ip;
    if (argc == 3)
    {
        ip = argv[2];
    }
    UdpServer svr(port, ip);
    svr.init();
    svr.start();


    return 0;
}