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

std::string getPath(std::string http_request)
{
    std::size_t pos = http_request.find(CRLF);
    if(pos == std::string::npos) return "";
    std::string request_line = http_request.substr(0, pos);
    //GET /a/b/c http/1.1
    std::size_t first = request_line.find(SPACE);
    if(pos == std::string::npos) return "";
    std::size_t second = request_line.rfind(SPACE);
    if(pos == std::string::npos) return "";

    std::string path = request_line.substr(first+SPACE_LEN, second - (first+SPACE_LEN));
    if(path.size() == 1 && path[0] == '/') path += HOME_PAGE;
    return path;
}

std::string readFile(const std::string &resource)
{
    std::ifstream in(resource, std::ifstream::binary);
    if(!in.is_open()) return "404";
    std::string content;
    std::string line;
    while(std::getline(in, line)) content += line;
    in.close();
    return content;
}


void handlerHttpRequest(int sock)
{
    char buffer[10240];
    ssize_t s = read(sock, buffer, sizeof(buffer));
    if (s > 0) cout << buffer;
    
    //1. 文件在那里？在请求的请求行中，第二个字段就是你要访问的文件
    //path = "/a/b/index.html";
    //resource = "./wwwroot"; //web根目录
    //resource += path; //./wwwroot/a/b/index./html
    std::string path = getPath(buffer);
    //2. 如何读取？
    std::string resource = ROOT_PATH;
    resource += path;
    std::cout << resource << std::endl;

    std::string html = readFile(resource);
    std::size_t pos = resource.rfind(".");
    std::string suffix = resource.substr(pos);
    cout << suffix << endl;
    //开始响应
    //std::string html = "<html><h1>hello world</h1></html>\r\n";
    std::string response;
    response = "HTTP/1.0 200 OK\r\n";
    if (suffix == ".jpg") 
    {
        response += "Content-Type: image/jpeg\r\n";
    }
    else
    {
        response += "Content-Type: text/html\r\n";
    }
    response += ("Content-Length: " + std::to_string(html.size()) + "\r\n");
    response += "\r\n"; //空行
    response += html;
    send(sock, response.c_str(), response.size(), 0);
}

class ServerTcp
{
public:
    ServerTcp(uint16_t port, const std::string &ip = "")
        :_port(port), _ip(ip), _listenSock(-1)
        //_logFd(isLog ? (open(LOGFILE, O_WRONLY | O_CREAT | O_APPEND, 0666)) : -1)
    {
        _quit = false;
    }
    ~ServerTcp()
    {
        if (_listenSock >= 0) close(_listenSock);
        //if (_logFd >= 0) close(_logFd);
    }
public:
    void init()
    {
        //1. 创建套接字
        _listenSock = socket(PF_INET, SOCK_STREAM, 0); //默认是流式服务
        if (_listenSock < 0)
        {
            exit(1);
        }
        int opt = 1;
        setsockopt(_listenSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        setsockopt(_listenSock, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
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
            exit(2);
        }
        
        //3. 监听socket，tcp是面向连接的。所谓面向的意思就是在做任何事情之前先干什么
        //比如面向对象就是先要创建对象
        if (listen(_listenSock, 5)<0)
        {
            exit(3);
        }

        //允许别人来连接了
    }

    void loop()
    {
        signal(SIGCHLD, SIG_IGN); //only Linux
        //SIG_IGN 忽略，子进程在终止时会自动清理掉,不会产生僵尸进程，也不会通知父进程
        while (!_quit)
        {
            struct sockaddr_in peer; //连接者信息
            socklen_t len = sizeof(peer);
            //5. 获取连接，accept的返回值是一个新的套接字文件描述符
            int serviceSock = accept(_listenSock, (struct sockaddr *)&peer, &len);
            
            if (_quit)
            {
                break;
            }

            if (serviceSock < 0)
            {//获取连接失败
                cerr << "accept error ..." << endl;
                continue; //继续获取
            }

            //多进程
            pid_t id = fork();
            assert(id != -1);
            if (id == 0)
            {
                close(_listenSock); //建议关掉
                if (fork()>0) exit(0);
                //子进程
                //ransService(serviceSock, peerIP, peerPort);
                handlerHttpRequest(serviceSock);
                exit(0);
            }
            //父进程
            close(serviceSock); //这一步是一定要做的
            wait(nullptr);
        }
    }

    bool quitServer()
    {
        _quit = true;
    }
private:
    int _listenSock; //套接字
    uint16_t _port; //端口号
    std::string _ip;
    bool _quit;//安全退出
};