#include "util.hpp"

static void Usage(std::string proc)
{
    std::cerr << "Usage\n\t" << proc << " serverIP serverPort" << std::endl;
    std::cerr << "Example:\n\t" << proc << " 8080 127.0.0.1\n" << std::endl;
}

volatile bool quit = false; //退出标记位

// ./clientTCP serverIP serverPort
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        exit(USAGE_ERR);
    }
    std::string serverIP = argv[1];
    uint16_t serverPort = atoi(argv[2]);
    //1. 创建socket SOCK_STREAM
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        std::cout << "socket: " << strerror(errno) << std::endl;
        exit(SOCKET_ERR);
    }

    //2. 需要bind，但不需要自己显式bind
    //3. 不需要listen，因为没人连client
    //4. 不需要accept

    //5. 需要connet，向服务器发起连接请求
    //5.1 先填充需要连接的远端主机的基本信息
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server)); //清零
    server.sin_family = AF_INET;
    server.sin_port = htons(serverPort);
    inet_aton(serverIP.c_str(), &(server.sin_addr));
    
    //5.2 发起请求，connet会自动进行bind
    if (connect(sock, (const struct sockaddr *)&server, sizeof(server)) != 0)
    {
        std::cerr << "connect: " << strerror(errno) << std::endl; 
    }

    std::cout << "info: connect success: " << sock << std::endl;
    
    std::string message;
    while (!quit)
    {
        message.clear();
        std::cout << "请输入你的信息>>>";
        std::getline(std::cin, message);
        if (strcasecmp(message.c_str(), "quit") == 0)
        {
            quit == true;
        }

        ssize_t s = write(sock, message.c_str(), message.size());
        if (s > 0)
        {
            message.resize(1024);
            ssize_t s = read(sock, (char *)(message.c_str()), 1024);
            if (s > 0)
            {
                message[s] = 0;
            }
            std::cout << "Server echos>>> " << message << std::endl;
        }
        else if (s <= 0)
        {
            break;
        }
    }

    close(sock);
    return 0;
}