#include "TCPServer.hpp"
#include <memory>

void NetCal(Connection *conn, std::string &request)
{
    logMessage(DEBUG, "NetCal been called, get request: %s", request.c_str());
    // 1. 反序列化
    Request req;
    // 2. 业务处理
    Response resp = calculator(req);
    // 3. 构建应答、序列化
    std::String sendstr = resp.Serialize();
    sendstr = Encode(sendstr);
    // 4. 交给服务器，让服务器发送
    conn->_outbuffer += sendstr;
    // 5. 想办法让底层的TCPServer发送
    //  a. 需要有完整的发送逻辑
    //  b. 触发发送的动作，一旦开始EPOLLOUT，epoll会自动立马触发一次发送事件就绪，若后续保持发送的开启，epoll会一直发送
    conn->_tsvr->EnableReadWrite(conn, true, true);
}

int main() {
    std::unique_ptr<TCPServer> svr(new TCPServer);
    svr->Dispatcher(); // 派发
    return 0;
}
