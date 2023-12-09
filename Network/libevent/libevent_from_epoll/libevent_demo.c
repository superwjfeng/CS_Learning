#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <event.h>
#include <event2/event.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct _ConnectStat ConnectStat;

#define BUFLEN 1024

struct _ConnectStat {
  struct event *ev;
  int fd;
  char send_buf[BUFLEN];
  // PF *handler;  //不同页面的处理函数
};

// echo 服务实现相关代码
ConnectStat *stat_init(int fd);
void accept_connection(int fd, short events, void *arg);
void do_welcome_handler(int fd, short events, void *arg);
void do_echo_handler(int fd, short events, void *arg);
void do_echo_response(int fd, short events, void *arg);

struct event_base *ev_base;

void usage(const char *argv) { printf("%s:[ip][port]\n", argv); }

void set_nonblock(int fd) {
  int fl = fcntl(fd, F_GETFL);
  fcntl(fd, F_SETFL, fl | O_NONBLOCK);
}

int startup(char *_ip, int _port)  // 创建一个套接字，绑定，检测服务器
{
  // sock
  // 1.创建套接字
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("sock");
    exit(2);
  }

  int opt = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  // 2.填充本地 sockaddr_in 结构体（设置本地的IP地址和端口）
  struct sockaddr_in local;
  local.sin_port = htons(_port);
  local.sin_family = AF_INET;
  local.sin_addr.s_addr = inet_addr(_ip);

  // 3.bind() 绑定
  if (bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0) {
    perror("bind");
    exit(3);
  }
  // 4.listen() 监听 检测服务器
  if (listen(sock, 5) < 0) {
    perror("listen");
    exit(4);
  }

  return sock;  // 这样的套接字返回
}

ConnectStat *stat_init(int fd) {
  ConnectStat *temp = NULL;
  temp = (ConnectStat *)malloc(sizeof(ConnectStat));

  if (!temp) {
    fprintf(stderr, "malloc failed. reason: %m\n");
    return NULL;
  }

  memset(temp, '\0', sizeof(ConnectStat));
  temp->fd = fd;
  // temp->status = 0;
}

void do_welcome_handler(int fd, short events, void *arg) {
  const char *WELCOME = "Welcome.\n";
  int wlen = strlen(WELCOME);
  int n;
  ConnectStat *stat = (ConnectStat *)(arg);

  if ((n = write(fd, "Welcome.\n", wlen)) != wlen) {
    if (n <= 0) {
      fprintf(stderr, "write failed[len:%d], reason: %s\n", n, strerror(errno));
    } else
      fprintf(stderr, "send %d bytes only ,need to send %d bytes.\n", n, wlen);

  } else {
    // 为了支持修改事件的属性，ConnectStat需要维护event信息
    event_set(stat->ev, fd, EV_READ, do_echo_handler, (void *)stat);
    stat->ev->ev_base = ev_base;  // 必须重置event_base，因为会被清零
    event_add(stat->ev, NULL);
  }
}

void do_echo_handler(int fd, short events, void *arg) {
  ConnectStat *stat = (ConnectStat *)(arg);
  char *p = NULL;

  assert(stat != NULL);

  p = stat->send_buf;
  *p++ = '-';
  *p++ = '>';
  ssize_t _s =
      read(fd, p, BUFLEN - (p - stat->send_buf) - 1);  // 2字节"->" +字符结束符.
  if (_s > 0) {
    *(p + _s) = '\0';
    printf("receive from client: %s\n", p);
    //_s--;
    // while( _s>=0 && ( stat->send_buf[_s]=='\r' || stat->send_buf[_s]=='\n' )
    // ) stat->send_buf[_s]='\0';

    if (!strncasecmp(p, "quit", 4)) {  // 退出
      event_free(stat->ev);            // 自动解除监听事件，释放event
      close(fd);
      free(stat);
      return;
    }
    event_set(stat->ev, fd, EV_WRITE, do_echo_response, (void *)stat);
    stat->ev->ev_base = ev_base;  // 必须重置事件集合
    event_add(stat->ev, NULL);
  } else if (_s == 0)  // client:close
  {
    fprintf(stderr, "Remote connection[fd: %d] has been closed\n", fd);
    event_free(stat->ev);
    close(fd);
    free(stat);
  } else  // err occurred. 出错在处理暂时忽略
  {
    fprintf(stderr, "read failed[fd: %d], reason:%s [%ld]\n", fd,
            strerror(errno), _s);
  }
}

void do_echo_response(int fd, short events, void *arg) {
  ConnectStat *stat = (ConnectStat *)(arg);
  int len = strlen(stat->send_buf);
  int _s = write(fd, stat->send_buf, len);

  if (_s > 0) {
    event_set(stat->ev, fd, EV_READ, do_echo_handler, (void *)stat);
    stat->ev->ev_base = ev_base;  // 必须重置事件集合
    event_add(stat->ev, NULL);
  } else if (_s == 0) {
    fprintf(stderr, "Remote connection[fd: %d] has been closed\n", fd);
    event_free(stat->ev);
    close(fd);
    free(stat);
  } else {
    fprintf(stderr, "read failed[fd: %d], reason:%s [%d]\n", fd,
            strerror(errno), _s);
  }
}

void accept_connection(int fd, short events, void *arg) {
  struct sockaddr_in peer;
  socklen_t len = sizeof(peer);

  int new_fd = accept(fd, (struct sockaddr *)&peer, &len);

  if (new_fd > 0) {
    ConnectStat *stat = stat_init(new_fd);
    set_nonblock(new_fd);

    printf("new client: %s:%d\n", inet_ntoa(peer.sin_addr),
           ntohs(peer.sin_port));
    struct event *ev =
        event_new(ev_base, new_fd, EV_WRITE, do_welcome_handler, (void *)stat);
    stat->ev = ev;
    event_add(ev, NULL);
  }
}

int main(int argc, char **argv) {
  if (argc != 3)  // 检测参数个数是否正确
  {
    usage(argv[0]);
    exit(1);
  }

  int listen_sock = startup(
      argv[1], atoi(argv[2]));  // 创建一个绑定了本地 ip 和端口号的套接字描述符

  ev_base = event_base_new();

  ConnectStat *stat = stat_init(listen_sock);

  // 创建事件，event_new 会指定对应的sock到全局event_base
  struct event *ev_listen = event_new(
      ev_base, listen_sock, EV_READ | EV_PERSIST, accept_connection, NULL);
  event_add(ev_listen, NULL);

  event_base_dispatch(ev_base);
  return 0;
}
