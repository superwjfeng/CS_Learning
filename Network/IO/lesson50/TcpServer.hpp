#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <unordered_map>
#include "Sock.hpp"
#include "Log.hpp"
#include "Epoll.hpp"

class TcpServer;
class Connection;

using func_t = std::function<void(Connection *)>;

// 我们为了能够正常工作，常规的sock必须是要有自己独立的接收缓冲区&&发送缓冲区
class Connection
{
public:
    Connection(int sock = -1) : _sock(sock), _tsvr(nullptr)
    {
    }
    void SetCallBack(func_t recv_cb, func_t send_cb, func_t except_cb)
    {
        _recv_cb = recv_cb;
        _send_cb = send_cb;
        _except_cb = except_cb;
    }
    ~Connection()
    {
    }

public:
    // 负责进行IO的文件描述符
    int _sock;
    // 三个回调方法，表征的就是对_sock进行特定读写对应的方法
    func_t _recv_cb;
    func_t _send_cb;
    func_t _except_cb;
    // 接收缓冲区&&发送缓冲区
    std::string _inbuffer; // 暂时没有办法处理二进制流，文本是可以的
    std::string _outbuffer;
    // 设置对TcpServer的回值指针
    TcpServer *_tsvr;
};

// class user
// {};

class TcpServer
{
    const static int gport = 8080;
    const static int gnum = 128;

public:
    TcpServer(int port = gport) : _port(port), _revs_num(gnum)
    {
        // 1. 创建listensock
        _listensock = Sock::Socket();
        Sock::Bind(_listensock, _port);
        Sock::Listen(_listensock);

        // 2. 创建多路转接对象
        _poll.CreateEpoll();

        // 3. 添加listensock到服务器中
        AddConnection(_listensock, std::bind(&TcpServer::Accepter, this, std::placeholders::_1), nullptr, nullptr);

        // 4. 构建一个获取就绪事件的缓冲区
        _revs = new struct epoll_event[_revs_num];
    }
    // 专门针对任意sock进行添加TcpServer
    void AddConnection(int sock, func_t recv_cb, func_t send_cb, func_t except_cb)
    {
        Sock::SetNonBlock(sock);
        // 除了_listensock,未来我们会存在大量的socket，每一个sock都必须被封装成为一个Connection
        //    当服务器中存在大量的Connection的时候，TcpServer就需要将所有的Connection要进行管理：先描述，在组织
        // 1. 构建conn对象，封装sock
        Connection *conn = new Connection(sock);
        conn->SetCallBack(recv_cb, send_cb, except_cb);
        conn->_tsvr = this;
        // 2. 添加sock到epoll中
        _poll.AddSockToEpoll(sock, EPOLLIN | EPOLLET); // 任何多路转接的服务器，一般默认只会打开对读取事件的关心，写入事件会按需进行打开！
        // 3. 还要将对应的Connection*对象指针添加到Connections映射表中！
        _connections.insert(std::make_pair(sock, conn));
    }

    void Accepter(Connection *conn)
    {
        // logMessage(DEBUG, "Accepter been called");
        // 一定是listensock已经就绪了，此次读取会阻塞吗？不会
        // v1 -> v2 : 你怎么保证，底层只有一个连接就绪呢？
        while (true)
        {
            std::string clientip;
            uint16_t clientport;
            int accept_errno = 0;
            // sock一定是常规的IO sock
            int sock = Sock::Accept(conn->_sock, &clientip, &clientport, &accept_errno);
            if (sock < 0)
            {
                if (accept_errno == EAGAIN || accept_errno == EWOULDBLOCK)
                    break;
                else if (accept_errno == EINTR)
                    continue; // 概率非常低
                else
                {
                    // accept失败
                    logMessage(WARNING, "accept error, %d : %s", accept_errno, strerror(accept_errno));
                    break;
                }
            }
            // 将sock托管给TcpServer
            if (sock >= 0)
            {
                AddConnection(sock, std::bind(&TcpServer::Recver, this, std::placeholders::_1),
                              std::bind(&TcpServer::Sender, this, std::placeholders::_1),
                              std::bind(&TcpServer::Excepter, this, std::placeholders::_1));
                logMessage(DEBUG, "accept client %s:%d success, add to epoll&&TcpServer success", clientip.c_str(), clientport);
            }
        }
    }

    void Recver(Connection *conn)
    {
        logMessage(DEBUG, "Recver event exists, Recver() been called");
    }

    void Sender(Connection *conn)
    {
    }

    void Excepter(Connection *conn)
    {
    }

    void LoopOnce()
    {
        int n = _poll.WaitEpoll(_revs, _revs_num);
        for (int i = 0; i < n; i++)
        {
            int sock = _revs[i].data.fd;
            uint32_t revents = _revs[i].events;
            if (revents & EPOLLIN)
            {
                if (IsConnectionExists(sock) && _connections[sock]->_recv_cb != nullptr)
                    _connections[sock]->_recv_cb(_connections[sock]);
            }
            if (revents & EPOLLOUT)
            {
                if (IsConnectionExists(sock) && _connections[sock]->_send_cb != nullptr)
                    _connections[sock]->_send_cb(_connections[sock]);
            }
        }
    }
    // 根据就绪的事件，进行特定事件的派发
    void Dispather()
    {
        while (true)
        {
            LoopOnce();
        }
    }
    ~TcpServer()
    {
        if (_listensock >= 0)
            close(_listensock);
        if (_revs)
            delete[] _revs;
    }

    bool IsConnectionExists(int sock)
    {
        auto iter = _connections.find(sock);
        if (iter == _connections.end())
            return false;
        else
            return true;
    }

private:
    int _listensock;
    int _port;
    Epoll _poll;
    // sock : connection
    std::unordered_map<int, Connection *> _connections;
    struct epoll_event *_revs;
    int _revs_num;
};
