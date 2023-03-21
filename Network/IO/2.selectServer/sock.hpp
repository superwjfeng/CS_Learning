#pragma once 

#include <iostream>
#include <fstream>
#include <signal.h>
#include <sys/types.h>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#define CRLF "\r\n"
#define SPACE " "
#define SPACE_LEN strlen(SPACE)
#define HOME_PAGE "index.html"
#define ROOT_PATH "wwwroot"

using namespace std;

class Sock
{
public:
    static const int gbacklog = 20;
    //1. 创建套接字
    static int Socket()
    {
        int listenSock = socket(PF_INET, SOCK_STREAM, 0);
        if (listenSock < 0)
        {
            exit(1);
        }
        int opt = 1;
        setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
        return listenSock;
    }

    //2. bind
    static void Bind(int socket, uint16_t port)
    {
        //2.1 填充服务器信息
        struct sockaddr_in local; //用户栈上
        memset(&local, 0, sizeof(local)); //清空
        local.sin_family = PF_INET; //和AF_INET是一样的
        local.sin_port = htons(port);
        local.sin_addr.s_addr = INADDR_ANY;
        //2.2 本地socket信息，写入_sock对应的内核区域
        if (bind(socket, (const struct sockaddr*)&local, sizeof(local)) == -1)
        {
            exit(2);
        }
    }

    static void Listen(int socket)
    {
        //3. 监听socket，tcp是面向连接的。所谓面向的意思就是在做任何事情之前先干什么
        //比如面向对象就是先要创建对象
        if (listen(socket, gbacklog)<0)
        {
            exit(3);
        }
    }
    static int Accept(int socket, std::string *clientIp, uint16_t *clientPort)
    {     
        struct sockaddr_in peer; //连接者信息
        socklen_t len = sizeof(peer);
        //5. 获取连接，accept的返回值是一个新的套接字文件描述符
        int serviceSock = accept(socket, (struct sockaddr *)&peer, &len);
        
        if (serviceSock < 0)
        {//获取连接失败
            return -1;
        }
        if (clientPort) *clientPort = ntohs(peer.sin_port);
        if (clientIp) *clientIp = inet_ntoa(peer.sin_addr);
        return serviceSock;
    }
public:

};