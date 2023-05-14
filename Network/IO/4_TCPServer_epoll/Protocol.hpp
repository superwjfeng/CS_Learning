#pragma once 

#include <iostream>
#include <cstring>
#include <string>
#include <vector>

// 1. 报文和报文之间采用特殊字符来解决粘包问题
// 2. 获取一个一个独立完整的报文，需要序列和反序列化 -- 自定义
// e.x. 100+19X100+10X100+10

#define SEP "X"
#define SEP_LEN strlen(SEP)

//class Request {};
//class Response {};

// 要切分传入的缓冲区
// 1. buffer会被窃走，也同时要从buffer中移除
// 2. 可能会存在多个报文，多个报文依次放入out
// buffer：输入输出型参数
// out：输出型参数
void SpliteMessage(std::string &buffer, std::vector<std::string> *out)
{
    while (true)
    {
        auto pos = buffer.find(SEP);
        if (std::string::npos == pos) break; // 没有分隔符，不完整不做处理
        std::string message = buffer.substr(0, pos); //前闭后开
        buffer.erase(0, pos + SEP_LEN);
        out->push_back(message);
    }

}
