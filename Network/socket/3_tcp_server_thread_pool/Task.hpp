#pragma once

#include <pthread.h>

#include <functional>
#include <iostream>
#include <string>

#include "Log.hpp"

class Task {
 public:
  // 回调函数包装器
  // 和 using 等价
  // typedef std::function<void (int, std::string, uint16_t)> callBack_t;
  using callBack_t = std::function<void(int, std::string, uint16_t)>;

 private:
  int _sock;         // 给用户提供IO服务的sock
  uint16_t _port;    // client port
  std::string _ip;   // client ip
  callBack_t _func;  // 回调方法
 public:
  Task() : _sock(-1), _port(-1) {}
  Task(int sock, std::string ip, uint16_t port, callBack_t func)
      : _sock(sock), _ip(ip), _port(port), _func(func) {}
  void operator()()  // 让Task对象成为一个仿函数 Task()
  {
    logMessage(DEBUG, "线程ID[%p] 处理 %s:%d 的请求 开始啦...", pthread_self(),
               _ip.c_str(), _port);
    _func(_sock, _ip, _port);
    logMessage(DEBUG, "线程ID[%p] 处理 %s:%d 的请求 结束啦...", pthread_self(),
               _ip.c_str(), _port);
  }
  ~Task() {}
};