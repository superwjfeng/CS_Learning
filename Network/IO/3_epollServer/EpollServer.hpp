#ifndef __EPOLL_SERVER_HPP__
#define __EPOLL_SERVER_HPP__

#include <iostream>
#include <string>
#include <cassert>
#include <functional>
#include "Log.hpp"
#include "Sock.hpp"
#include "Epoll.hpp"

namespace wjfeng
{
    const static int default_port = 8080;
    const static int gnum = 64;
    
    //只处理读取，refactor会处理输入
    class EpollServer
    {
        using func_t = std::function<void(std::string)>;
    public:
        //static const int default_port = 8080; //静态变量在构造的时候要存在，所以不能这么写
        EpollServer(func_t HandlerRequest, const int &port = default_port)
            :_port(port), _revs_num(gnum), _HandlerRequest(HandlerRequest)
        {
            //0、申请对应的空间
            _revs = new struct epoll_event[_revs_num];
            //1、创建listensock
            _listensock = Sock::Socket();
            Sock::Bind(_listensock, _port);
            Sock::Listen(_listensock);
            //2、创建epoll模型
            _epfd = Epoll::CreateEpoll();
            logMessage(DEBUG, "init success, listensock: %d, epfd: %d", _listensock, _epfd);
            //3、将listensock先添加到epoll中，让epoll帮我们管理起来
            if (!Epoll::CtlEpoll(_epfd, EPOLL_CTL_ADD, _listensock, EPOLLIN)) exit(6);
            logMessage(DEBUG, "add listensock to epoll success.");
        }
        
        void Accepter(int listensock)
        {
            std::string clientip;
            uint16_t clientport;
            int sock = Sock::Accept(listensock, &clientip, &clientport);
            if (sock < 0)
            {
                logMessage(WARNING, "accept error");
                return;
            }
            //不能直接read，要交给epoll等
            if (!Epoll::CtlEpoll(_epfd, EPOLL_CTL_ADD, sock, EPOLLIN)) return;
            logMessage(DEBUG, "add new sock: %d to epoll success");
        }

        void Recver(int sock)
        {
            // 1. 读取数据
            char buffer[1024];
            ssize_t n = recv(sock, buffer, sizeof(buffer)-1, 0);
            if (n > 0)
            {
                //假设这里就是读到的完整报文
                buffer[n] = 0;
                _HandlerRequest(buffer); //跳转到main中处理相关的逻辑
            }
            else if (n == 0)
            {
                //一定要现在epoll中去掉sock，然后再close文件
                bool res = Epoll::CtlEpoll(_epfd, EPOLL_CTL_DEL, sock, 0);
                assert(res);
                (void)res;
                close(sock);
                logMessage(NORMAL, "client %d quit, me too...", sock);
            }
            else
            {
                //一定要现在epoll中去掉sock，然后再close文件
                bool res = Epoll::CtlEpoll(_epfd, EPOLL_CTL_DEL, sock, 0);
                assert(res);
                (void)res;
                close(sock);
                logMessage(NORMAL, "client recv %d error, close error sock", sock);
            }
            // 2. 处理数据
        }

        void HandlerEvents(int n) 
        {
            assert(n > 0);
            for (int i = 0; i < n; i++) //因为epoll_wait返回的是前n个就绪的fd，所以秩序要遍历n个就行了
            {
                uint32_t revents = _revs[i].events;
                int sock = _revs[i].data.fd;
                if (revents & EPOLLIN)
                {
                    // 1. listensock就绪
                    if (sock == _listensock) Accepter(sock);
                    else Recver(sock); // 2. 一般sock就绪 - read
                }
            }
        }

        void LoopOnce(int timeout)
        {
            int n = Epoll::WiatEpoll(_epfd, _revs, _revs_num, timeout);
            // if (n == _revs_num) //扩容
            switch (n)
            {
            case 0:
                logMessage(DEBUG, "timeout...");
                break;
            case -1:
                logMessage(WARNING, "epoll wait error: %s", strerror(errno));
                break;
            default:
                //等待成功
                logMessage(DEBUG, "get a event");
                HandlerEvents(n);
                break;
            }
        }

        void Start()
        {
            int timeout = 1000; //ms 0是非阻塞，-1是阻塞
            while (true) {
                LoopOnce(timeout);
            }
        }
        ~EpollServer()
        {
            if (_listensock >= 0) close(_listensock);
            if (_epfd >= 0) close(_epfd);
            if (_revs) delete []_revs;
        }
        

    private:
        int _listensock;
        int _epfd;
        uint16_t _port;
        struct epoll_event *_revs; //结构体数组
        int _revs_num;
        func_t _HandlerRequest;
    };
} // namespace wjfeng



#endif