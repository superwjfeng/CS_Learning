#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cassert>

struct sockaddr_in server; //初始化

static void Usage(const std::string name)
{
    std::cout << "Usage:\n\t" << name << " server_ip server_port" << std::endl; 
}

//这个线程负责收消息
void *receiveAndPrint(void *args)
{
    while (true)
    {
        int sockfd = *(int *)args;
        char buffer[1024];

        struct sockaddr_in temp;
        socklen_t len = sizeof(temp);
        ssize_t s = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&temp, &len);
        if (s > 0)
        {
            buffer[s] = 0;
            std::cout << "server echo# " << buffer << std::endl;
        }
    }
}

// udpClient 
// 若一个客户端要连接server必须知道server对应的ip和port
int main(int argc, char *argv[]) {

    if (argc != 3)
    {
        Usage(argv[0]);
        exit(-1);
    }

    //1. 根据命令行，设置要访问的服务器IP
    std::string server_ip = argv[1];
    uint16_t server_port = atoi(argv[2]);

    //2. 创建客户端
    //2.1 创建socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sockfd > 0);

    //2.2 client不需要bind，不需要指的是用户自己不需要自己bind端口信息，因为OS会自动绑定
    //也推荐这么做，但如果用户非得自己绑定，也可以，但很不推荐
    //原因是因为一般在一台host上要获取一台server服务的clients会有很多，若指定了clients的某个port进行bind
    //此时若该port已经和其他client绑定了，那么这个client就不能正常启动和获取服务
    //因此推荐让OS随机生成、自动分配port和绑定。举个例子，去公司上班，我们需要知道公司的地址，但反过来公司不需要员工的地址

    //2.3 填充server对应信息
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);
    server.sin_addr.s_addr = inet_addr(server_ip.c_str());


    pthread_t t;
    pthread_create(&t, nullptr, receiveAndPrint, (void *)&sockfd);
    //3. 通讯过程
    std::string buffer;
    while (true)
    {
        std::cout << "Please enter# ";
        std::getline(std::cin, buffer);
        
        //主线程发送消息给server
        //首次调用sendto函数的时候，client会自动bind自己的ip和port
        //sendto前面4个参数表示发送者和发送内容，最后两个参数表示接收者相关信息
        sendto(sockfd, buffer.c_str(), buffer.size(), 0,\
            (const struct sockaddr *)&server, sizeof(server));
    }
    return 0;
}