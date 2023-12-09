﻿#ifndef GLOBALS_H
#define GLOBALS_H

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define FD_DESC_SZ 64

#define COMM_OK (0)
#define COMM_ERROR (-1)
#define COMM_NOMESSAGE (-3)
#define COMM_TIMEOUT (-4)
#define COMM_SHUTDOWN (-5)
#define COMM_INPROGRESS (-6)
#define COMM_ERR_CONNECT (-7)
#define COMM_ERR_DNS (-8)
#define COMM_ERR_CLOSING (-9)

/* 调试相关 */
#define DEBUG_LEVEL 0
#define DEBUG_ONLY 8
#define debug(m, n) \
  if (m >= DEBUG_LEVEL && n <= DEBUG_ONLY) printf

#define safe_free(x) \
  if (x) {           \
    free(x);         \
    x = NULL;        \
  }

typedef void PF(int, void *);

/* 核心数据结构，用来托管 */
struct _fde {
  unsigned int type;
  u_short local_port;
  u_short remote_port;
  struct in_addr local_addr;

  char ipaddr[16]; /* dotted decimal address of peer */

  PF *read_handler;
  void *read_data;
  PF *write_handler;
  void *write_data;
  PF *timeout_handler;
  time_t timeout;
  void *timeout_data;
};

typedef struct _fde fde;

extern fde *fd_table;
extern int Biggest_FD;

/* 系统时间相关,设置成全局变量，供所有模块使用 */
extern struct timeval current_time;
extern double current_dtime;
extern time_t sys_curtime;

/* epoll 相关接口封装，仅框架内部使用，位于 comm_epoll.c 中 */
extern void do_epoll_init(int max_fd);
extern void do_epoll_shutdown();
extern void epollSetEvents(int fd, int need_read, int need_write);
extern int do_epoll_select(int msec);

/* 封装错误处理的接口 */
extern const char *xstrerror(void);
int ignoreErrno(int ierrno);

/* 框架外部接口，供使用者使用，位于 comm.c 中 */
void comm_init(int max_fd);
extern int comm_select(int msec);
extern inline void comm_call_handlers(int fd, int read_event, int write_event);
void commUpdateReadHandler(int fd, PF *handler, void *data);
void commUpdateWriteHandler(int fd, PF *handler, void *data);

#endif /* GLOBALS_H */
