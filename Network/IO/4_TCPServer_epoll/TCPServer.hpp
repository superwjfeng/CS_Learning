#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <cerrno>
#include <cassert>
#include "Sock.hpp"
#include "Log.hpp"
#include "Epoll.hpp"
#include "Protocol.hpp"
 
class TCPServer; //declaration
class Connection;

using func_t = std::function<void(Connection*)>; //函数形式是void (Connection*)
using callback_t = std::function<void (Connection*, std::string request)>;

//为了能正常工作，常规的sock必须要有自己独立的接收缓冲区
class Connection 
{
public:
    Connection(int sock = -1)
        :_sock(sock), _tsvr(nullptr)
    {}

    void SetCallBack(func_t recv_cb, func_t send_cb, func_t except_cb)
    {
        _recv_cb = recv_cb;
        _send_cb = send_cb;
        _except_cb = except_cb; 
    }

    ~Connection() {}
//这里为了方便起见，将属性设为私有就不用写get了。规范是要设置成private的
public:
    int _sock; //负责进行IO的文件描述符
    //3个回调方法，表示对_sock的读写方法
    func_t _recv_cb; //读回调
    func_t _send_cb; //写回调
    func_t _except_cb; //异常回调
    std::string _inbuffer; //暂时没有办法处理二级制流，文本是可以的
    std::string _outbuffer; 
    // 设置对TCPServer的回执指针
    TCPServer *_tsvr;
    uint64_t _lasttimestamp; //最近一次被访问的事件
};

// 网络服务器不可以和上层业务强耦合
class TCPServer
{
    const static int gport = 8080;
    const static int gnum = 128;
public:
    TCPServer(int port = 8080)
        :_port(port), _revs_num(gnum)
    {
        // 1. 创建listensock
        _listensock = Sock::Socket();
        Sock::Bind(_listensock, _port);
        Sock::Listen(_listensock);

        // 2. 创建多路转接对象
        _poll.CreateEpoll();
        
        // 3. 添加listensock到服务器中
        // 构造函数可以调用类方法，因为走到了函数体内以后对象已经通过初始化列表创建出来了
        // lisetn不关心send和except，所以为nullptr
        AddConnection(_listensock, std::bind(&TCPServer::Acceptr, this, std::placeholders::_1), nullptr, nullptr);

        // 4. 构建一个获取就绪事件的缓冲区
        _revs = new struct epoll_event[_revs_num];
    }

    //专门针对任意sock添加到TCPServer，设计一个接口
    void AddConnection(int sock, func_t recv_cb, func_t send_cb, func_t except_cb)
    {
        Sock::SetNonBlock(sock); //ET模式设置fd为非阻塞
        // 1. 除了_listensock，未来还存在大量的socket，每一个sock都必须被封装称为一个Connection
        // 当服务器中存在大量的Connection的时候，TCPServer就需要管理所有的Connection：先描述再组织
        // 构建conn对象，封装sock
        Connection *conn = new Connection(sock);
        conn->SetCallBack(recv_cb, send_cb, except_cb);
        conn->_tsvr = this;
        // 2. 添加sock[]到epoll中
        //任何多路转接的服务器，一般默认只会打开对读取事件的关心，写入事件会按需打开
        _poll.AddSockToEpoll(sock, EPOLLIN | EPOLLET); //设置成ET模式，默认是LT模式，不需要设置
    // 3. 还要将对应的Connection* 对象指针添加到Connection映射表中
        _connection.insert(std::make_pair(sock, conn));

    }

    void Acceptr(Connection *conn)
    {
        logMessage(DEBUG, "Acceptr been called");
        // 一定是listensock已经就绪了，此次读取不会被阻塞
        // 要循环accept，因为有可能是来了一批的socket
        while (true)
        {
            std::string clientIP;
            uint16_t clientPort;
            int accept_errno = 0;
            //此时的sock是常规的IO sock
            int sock = Sock::Accept(conn->_sock, &clientIP, &clientPort, &accept_errno);
            //获取失败
            if (sock < 0)
            {
                if (accept_errno == EAGAIN || accept_errno == EWOULDBLOCK) break;
                else if (accept_errno == EINTR) continue; //概率非常低
                else //accept失败
                {
                    logMessage(WARNING, "accept error, %d : %s", accept_errno, strerror(accept_errno));
                    break;
                }
            }
            if (sock >= 0)
            {
                //获取成功，将新的socket托管给TCPServer
                AddConnection(sock, std::bind(&TCPServer::Recver, this, std::placeholders::_1),\
                                    std::bind(&TCPServer::Sender, this, std::placeholders::_1),\
                                    std::bind(&TCPServer::Excepter, this, std::placeholders::_1));
                logMessage(DEBUG, "accept client %s:%d success, add to epoll && TCPServer success, sock: %d",\
                        clientIP.c_str(), clientPort, sock);

            }
        }
    }

    void Recver(Connection *conn)
    {
        const int num = 1024;
        bool err = false;
        logMessage(DEBUG, "Recver event happens, Recver() been called.");
        // v1: 直接面向字节流，先进行常规读取
        while (true)
        {
            char buffer[num];
            ssize_t n = recv(conn->_sock, buffer, sizeof(buffer)-1, 0); 
            if (n < 0)
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK) break; //没处错，读完了
                else if (errno == EINTR) continue;
                else 
                {
                    logMessage(ERROR, "recv error, %d : %s", errno, strerror(errno));
                    conn->_except_cb(conn); //交给异常回调处理
                    err = true;
                    break;
                }
            }
            else if (n == 0)
            {
                logMessage(DEBUG, "client[%d] quit, server close", errno, strerror(errno));
                conn->_except_cb(conn);
                err = true;
                break;
            }
            else // 读取成功
            {
                buffer[n] = 0;
                conn->_inbuffer += buffer;
            }
        } // end while 
        logMessage(DEBUG, "conn->_inffer[sock: %d]: %s", conn->_sock, conn->_inbuffer.c_str());
        if (!err)
        {
            std::vector<std::string> messages;
            // 自定义协议解决粘包问题
            SpliteMessage(conn->_inbuffer, &messages);
            // 能保证走到这里是一个完整报文
            for (auto &msg:messages) _cb(conn, msg); 
            // 可以将message封装称为task，然后push到任务队列，任务处理交给后端线程
        }
    }

    void EnableReadWrite(bool readable, bool writeable)
    {
        uint32_t events = ((readable ? EPOLLIN : 0) | (writeable ? EPOLLOUT : 0));
        _poll.CtrlEpoll(conn->_sock, events);
        assert(res); //更改成if
    }

    void Excepter(Connection *conn)
    {
        if(!IsConnectionExists(conn->_sock)) return;
        // 1. 从epoll中移除
        bool res = _poll.DelFromEpoll(conn->_sock);
        assert(res); //要判断
        // 2. 从我们的unorder_map中移除
        _connections.erase(conn->_sock);
        // 3. close(sock);
        close(conn->_sock);
        // 4. delete conn;
        delete conn;

        logMessage(DEBUG, "Excepter 回收完毕，所有的异常情况");
    }

    bool IsConnectionExists(int sock)
    {
        auto iter = _connection.find(sock);
        if(iter == _connection.end()) return false;
        else return true;
    }

    // 最开始的时候，conn是没有被触发的
    void Sender(Connection *conn)
    {
        while (true)
        {
            size_t n = send(conn->_sock, conn->_outbuffer.c_str(), conn->_outbuffer.size(), 0);
            if (n > 0)
            {
                conn->_outbuffer.erase(0, n);
                if (conn->_outbuffer.empty()) break;
            }
            else
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK) break;
                else if (errno == EINTR) continue; //中断
                else 
                {
                    logMessage(ERROR, "send error, %d : %s", errno, strerror(errno));
                    conn->_except_cb(conn);
                    err = true;
                    break;
                }
            }
        }

        // 不确定有没有发送完，但是可以保证没有出错，则一定是要么发送完，要不发送条件不满足，下次再发
        if (conn->_outbuffer.empty()) EnableReadWrite(conn, true, false);
        else EnableReadWrite(conn, true, true);
    }

    void LoopOnce()
    {
        int n = _poll.WaitEpoll(_revs, _revs_num); //从内核的epoll中捞取数据到Server自己的epoll中
        for (int i = 0; i < n; i++) 
        {
            int sock = _revs[i].data.fd;
            uint32_t revents = _revs[i].events;

            //统一异常处理： 讲所有的异常全部交给read或者write统一处理
            if (revents & EPOLLERR) revents |= (EPOLLIN | EPOLLOUT);
            if (revents & EPOLLHUP) revents |= (EPOLLIN | EPOLLOUT);

            if (revents &EPOLLIN) //EPOLLIN为真，执行读方法 _recv_cb
            {
                if (IsConnectionExists(sock) && _connection[sock]->_recv_cb != nullptr)
                    _connection[sock]->_recv_cb(_connection[sock]);
            }
            if (revents & EPOLLOUT) //EPOLLOUT为真，执行写方法 _send_cb
            {
                if (IsConnectionExists(sock) && _connection[sock]->_send_cb !=nullptr)
                    _connection[sock]->_send_cb(_connection[sock]);
            }
        }
    }

    void ConnectAliveCheck()
    {
        // 遍历所有的_connections，通过检测最近conn的活动时间，如果长时间没有动
        // 进入到链接超时的逻辑
        //for(auto &iter : _connections)
        //{
        //    uint64_t currtime = time();
        //    deadtime = currtime - iter->_lasttimestamp;
        //    if(deadtime > XXXX) //差错处理逻辑
        //}
    }
    
    //根据就绪的事件来派发特定事件
    void Dispatcher(callback_t cb)
    {
        _cb = cb;
        while (true)
        {
            LoopOnce();
        }
    }

    ~TCPServer()
    {
        if (_listensock > 0) close(_listensock);
        if (_revs) delete []_revs;
    }
private:
    int _listensock;
    int _port;
    Epoll _poll; //给Server自带一个epoll结构体方便使用
    //可以用智能指针降低工作量，这里用原生指针是为了展示
    std::unordered_map<int, Connection *> _connection; //保存所有的Connection对象的映射，key是sockfd
    struct epoll_event *_revs; //ready events
    int _revs_num;
    callback_t _cb; // 下面是上层业务处理
};
