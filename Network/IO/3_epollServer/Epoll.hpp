#pragma once
#include <iostream>
#include <sys/epoll.h>

//封装epoll
class Epoll
{
public:
    static const int gsize = 256; //随便选一个大于0的值

public:
    static int CreateEpoll() //单例
    {
        int epfd = epoll_create(gsize);
        if (epfd > 0) return epfd;
        exit(5);
    }

    static bool CtlEpoll(int epfd, int oper, int sock, uint32_t events)
    {
        struct epoll_event ev;
        ev.events = events;
        ev.data.fd = sock;
        int n = epoll_ctl(epfd, oper, sock, &ev);
        return n == 0;
    }

    static int WiatEpoll(int epfd, struct epoll_event revs[], int num, int timeout)
    {
        // 细节1：若底层就绪的sock非常多，revs装不下怎么办？不影响，若一次拿不完就下回再拿
        // 细节2：关于epoll_wait的返回值问题：有n个fd上的事件就绪，就返回m，epoll返回的时候
        //       会将所有就绪的event按照顺序放到revs数组中，因此只要顺序读前n个数组元素就行了
        return epoll_wait(epfd, revs, num, timeout);
    }
};