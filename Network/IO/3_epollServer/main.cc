#include "EpollServer.hpp"
#include <memory>

using namespace std;
using namespace wjfeng;

void change(std::string request)
{
    //完成业务逻辑
    std::cout << "change: " << request << std::endl;
}

int main() {
    unique_ptr<EpollServer> epoll_server(new EpollServer(change));
    epoll_server->Start();

    return 0;
}