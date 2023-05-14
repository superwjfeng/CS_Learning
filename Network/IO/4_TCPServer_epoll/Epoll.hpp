#pragma once
#include <iostream>
#include <sys/epoll.h>


//可以采用下面继承的方案，实现多种多路转接方案
/*
//虚基类
class Poll
{};

class Epoll : public Poll {};
class Select : public Poll {};
*/

class Epoll
{
    const static int gnum = 128;
    const static int gtimeout = 5000;
public:
    Epoll(int timeout = gtimeout) :_timeout(timeout)
    {}
    
    void CreateEpoll()
    {
        _epfd = epoll_create(gnum);
        if (_epfd < 0) exit(5);
    }

    bool DelEpoll(int sock)
    [
        int n = epoll_ctl(_epfd, EPOLL_CTL_DEL, sock, nullptr);
        return n == 0;
    ]

    bool CtrlEpoll(int sock, uint32_t events)
    {
        events |= EPOLLET;
        struct epoll_event ev;
        ev.events = events;
        ev.data.fd = sock;
        int n = epoll_ctl(_epfd, EPOLL_CTL_MOD, sock, &ev);
        return n == 0;

    }

    // 封装epoll_ctl 注册sock的功能
    bool AddSockToEpoll(int sock, uint32_t events)
    {
        struct epoll_event ev;
        ev.events = events;
        ev.data.fd = sock;
        int n = epoll_ctl(_epfd, EPOLL_CTL_ADD, sock, &ev);
        return n == 0;
    }

    //封装epoll_wait
    int WaitEpoll(struct epoll_event revs[], int num)
    {
        return epoll_wait(_epfd, revs, num, _timeout);   
    }

    ~Epoll()
    {}
private:
    int _epfd;
    int _timeout;
};