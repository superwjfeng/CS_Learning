#pragma once

#include <cstdio>
#include <assert.h>
#include <cstdarg>
#include <time.h>
#include <cstring>
#include <cerrno>
#include <stdlib.h>

//日志等级
#define DEBUG    0
#define NOTICE   1
#define WARNING  2
#define FATAL    3

const char *log_level[] = {"DEBUG", "NOTICE", "WARNING", "FATAL"};

void logMessage(int level, const char *format, ...) {
    assert(level >= DEBUG);
    assert(level <= FATAL);

    char *name = getenv("USER");

    char logInfo[1024];

    va_list ap; //char* ap
    va_start(ap, format);
    
    vsnprintf(logInfo, sizeof(logInfo)-1, format, ap); //对格式化内容流写入到logInfo中

    
    va_end(ap); //ap = NULL

    FILE *out = (level == FATAL) ? stderr:stdout;
    
    //输出日志等级+时间+使用者+消息内容
    fprintf(out, "%s | %u | %s | %s\n", \
        log_level[level], \
        (unsigned int)time(nullptr), \
        name == nullptr ? "unknow":name, \
        logInfo);
}