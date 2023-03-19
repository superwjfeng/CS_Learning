#pragma once
#include <iostream>
#include <string>
#include <assert.h>
#include <jsoncpp/json/json.h>
#include "util.hpp"

//应用层协议定制
//网络版本的计算器

#define CRLF      "\r\n"
//千万不要用sizeof(CRLF) == 3，因为sizeof包含了\0
#define CRLF_LEN  strlen(CRLF) 
#define SPACE     " " //分隔符
#define SPACE_LEN strlen(SPACE)
#define OPS       "+-*/%"
//#define MY_SELF    1

//decode，整个序列化之后的字符串去掉报头
//1. 必须具有完整的长度
//2. 必须具有和len相符合的有效载荷
//满足上面两个条件才返回有效载荷和len，否则就是不停地检测
std::string decode(std::string &in, uint32_t* len)
{
    assert(len);
    //1. 确认是否是一个包含len的有效字符串
    *len = 0;
    std::size_t pos = in.find(CRLF);
    if (pos == std::string::npos)
        return "";
    //2. 提取长度
    std::string inLen = in.substr(0, pos); //头上的报文长度字符串
    int intLen = atoi(inLen.c_str()); //转换成int
    //3. 确认有效载荷是符合要求的
    int surplus = in.size() - 2 * CRLF_LEN - pos;
    if (surplus < intLen) return ""; //报文不完整
    //4. 确认报文是完整的
    std::string package = in.substr(pos+CRLF_LEN, intLen);
    *len = intLen;
    //5. 将当前报文完整的从in中全部移除掉
    int removeLen = inLen.size() + package.size() + 2*CRLF_LEN;
    in.erase(0, removeLen);
    //6. 正常返回
    return package;
}

//encode，整个序列化之后的字符串添加报头
//采用 "strLen\r\nXXXXXXXXXX\r\n" 的方案而不是 strLen定长字节数字+"XXXXXXX"的方案，提高可读性
//为什么要发送strLen，直接读\r\n不行吗？因为一段话可能是有好几个\r\n分段组成的，因此不能用它做标志（这种情况称为二进制不安全）
//但我们可以保证strLen里是不含\r\n的，可以把第一个\r\n作为strLen结束的标志
std::string encode(const std::string &in, uint32_t len)
{
    // "_exitCode _result"
    // "len\r\n""_exitCode _result\r\n"
    std::string encodein = std::to_string(len);
    encodein += CRLF;
    encodein += in;
    encodein += CRLF;
    return encodein;
}

//定制的请求 _x _op _y
class Request
{
public:
    Request()
    {}
    ~Request()
    {}
    //序列化：结构化的数据转成字符串
    //认为结构化字段中的内容已经被填充了
    void serialize(std::string *out) 
    {
#ifdef MY_SELF
//自定义序列化
        std::string xstr = std::to_string(_x);
        std::string ystr = std::to_string(_y);
        //若用to_string进行转换的话，to_string需要一个int值，会转成ascii码
        //std::string opstr = std::to_string(_op);
        
        *out = xstr;
        *out += SPACE;
        *out += _op; //直接+= char
        *out += SPACE;
        *out += ystr;
#else
        //json
        // 1. Value对象是一个万能对象
        // 2. json是基于KV的
        // 3. json有两套操作方法
        // 4. 序列化的时候，会将所有的数据内容转换成字符串

        // 填充
        Json::Value root;
        root["x"] = _x;
        root["y"] = _y;
        root["op"] = _op;

        // 序列化
        Json::FastWriter fw;
        *out = fw.write(root);        
#endif
    }

    bool deserialize(std::string &in) //反序列化：字符串转换成结构化数据
    {
        //100 + 200
#ifdef MY_SELF
//自定义序列化
        std::size_t spaceOne = in.find(SPACE);
        if (std::string::npos == spaceOne) return false; //不存在空格
        std::size_t spaceTwo = in.rfind(SPACE);
        if (std::string::npos == spaceTwo) return false;

        std::string dataOne = in.substr(0, spaceOne);
        std::string dataTwo = in.substr(spaceTwo + SPACE_LEN);
        std::string oper = in.substr(spaceOne+SPACE_LEN, spaceTwo-(spaceOne+SPACE_LEN));
        if (oper.size() != 1) return false;
        
        //转成内部成员
        _x = atoi(dataOne.c_str());
        _y = atoi(dataTwo.c_str());
        _op = oper[0];
        return true;
#else
//json
        Json::Value root;
        Json::Reader rd;
        rd.parse(in, root);
        _x = root["x"].asInt();
        _y = root["y"].asInt();
        _op = root["op"].asInt();
        return true;

#endif

    }

    void debug()
    {
        std::cout << "###########################" << std::endl;
        std::cout << "_x: " << _x << std::endl;
        std::cout << "_op: " << _op << std::endl;
        std::cout << "_y: " << _y << std::endl;
        std::cout << "###########################" << std::endl;
    }

public:
    //需要计算的数据
    int _x;
    int _y;
    //需要进行的操作
    char _op; // + - * / %
};

//定制的响应
class Response
{
public:
    Response()
    {}
    ~Response()
    {}
    // 序列化：不仅仅是在网络中应用，本地也是可以直接使用的
    // 特别在落盘的时候序列化会比较好，因为长期存储的数据可能在之后会被升级过的软件打开
    void serialize(std::string *out) //序列化：结构化的数据转成字符串
    {
#ifdef MY_SELF
        // "exitCode_ result_"
        std::string ec = std::to_string(_exitCode);
        std::string res = std::to_string(_result);
        *out = ec;
        *out += SPACE;
        *out += res;
#else
//json
        Json::Value root;
        root["exitCode"] = _exitCode;
        root["result"] = _result;
        Json::FastWriter fw;
        *out = fw.write(root);
#endif  
    }

    bool deserialize(const std::string &in) //反序列化：字符串转换成结构化数据
    {
#ifdef MY_SELF
        // "exitCode_ result_"
        std::size_t pos = in.find(SPACE);
        if (std::string::npos == pos) return false;
        std::string codestr = in.substr(0, pos);
        std::string reststr = in.substr(pos + SPACE_LEN);
        // 将反序列化的结果写入到内部成员中，形成结构化数据
        _exitCode = atoi(codestr.c_str());
        _result = atoi(reststr.c_str());
        return true;
#else
//json
        Json::Value root;
        Json::Reader rd;
        rd.parse(in, root);
        _exitCode = root["exitCode"].asInt();
        _result = root["result"].asInt();
#endif  
    }

    void debug()
    {
        std::cout << "###########################" << std::endl;
        std::cout << "_exitCode: " << _exitCode << std::endl;
        std::cout << "_result: " << _result << std::endl;
        std::cout << "###########################" << std::endl;
    }

public:
    //退出状态，0表示运算结果合法，非0表示运算结果是非法的，!0是几就表示是什么原因错误了
    int _exitCode; 
    int _result; //运算结果
};

//将用户输入的内容转换为需要的req格式
bool makeRequest(const std::string &str, Request *req)
{
    // format: 1+1
    char strtmp[BUFFER_SIZE];
    snprintf(strtmp, sizeof(strtmp), "%s", str.c_str());
    char *left = strtok(strtmp, OPS);
    if (!left) return false;
    char *right = strtok(nullptr, OPS);
    if (!right) return false;
    char mid = str[strlen(left)];

    req->_x = atoi(left);
    req->_y = atoi(right);
    req->_op = mid;
    return true;
}