#pragma once

#include <cstdio>
#include <assert.h>
#include <cstdarg>
#include <time.h>
#include <cstring>
#include <cerrno>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

//日志等级
#define DEBUG    0
#define NOTICE   1
#define WARNING  2
#define FATAL    3

const char *log_level[] = {"DEBUG", "NOTICE", "WARNING", "FATAL"};

#define LOGFILE "tcpServer.log"

class Log
{
public:
    Log(): _logFd(-1)
    {}
    void enable()
    {
        umask(0);
        _logFd = open(LOGFILE, O_WRONLY | O_CREAT | O_APPEND, 0666);
        assert(_logFd);
        dup2(_logFd, 1);
        dup2(_logFd, 2);
    }
    ~Log()
    {
        if (_logFd != -1)
        {
            fsync(_logFd);
            close(_logFd);
        }
    }
private:
    int _logFd;
};


void logMessage(int level, const char *format, ...) {
    assert(level >= DEBUG);
    assert(level <= FATAL);

    char *name = getenv("USER");

    char logInfo[1024];

    va_list ap; //char* ap
    va_start(ap, format);
    
    vsnprintf(logInfo, sizeof(logInfo)-1, format, ap); //对格式化内容流写入到logInfo中
    
    va_end(ap); //ap = NULL

    //umask(0);
    //int fd = open(LOGFILE, O_WRONLY | O_CREAT | O_APPEND, 0666);
    //assert(fd >= 0);
    
    //if (logFd != -1)
    //{
    //    dup2(logFd, 1);
    //    dup2(logFd, 2);
    //}

    //输出日志等级+时间+使用者+消息内容
    FILE *out = (level == FATAL) ? stderr : stdout;
    fprintf(out, "%s | %u | %s | %s\n", \
        log_level[level], \
        (unsigned int)time(nullptr), \
        name == nullptr ? "unknow":name, \
        logInfo);

    fflush(out); //将C缓冲区中的数据刷新到OS
    fsync(fileno(out)); //将OS中的数据落盘

    //close(fd);
}