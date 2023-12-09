#pragma once
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>
#include <iostream>

void daemonize() {
  int fd = 0;
  // 1. 忽略SIGPIPE
  signal(SIGPIPE, SIG_IGN);
  // 2. 更改进程的工作目录
  // chdir();

  // 3. 让自己不要成为进程组组长
  if (fork() > 0) exit(1);
  // 4. 设置自己是一个独立的会话
  setsid();
  // 5. 重定向0，1，2fd
  if ((fd = open("/dev/null", O_RDWR)) != -1)  // fd一般就是3
  {
    dup2(fd, STDIN_FILENO);  // STDIN_FILENO 宏就是对0 fd的封装
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
    // 6. 关闭掉不需要的fd
    if (fd > STDERR_FILENO) close(fd);
  }
}