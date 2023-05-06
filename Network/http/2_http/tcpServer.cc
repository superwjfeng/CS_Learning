#include "server.hpp"

static void Usage(std::string proc)
{
    cerr << "Usage:\n\t" << proc << " port" << endl;
    cerr << "Example:\n\t" << proc << " 8080\n" << endl;
}

// ./tcpServer local_port local_ip
// local_ip 为空的时候会自己填充
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        Usage(argv[0]);
        exit(0);
    }

    uint16_t port = atoi(argv[1]);

    ServerTcp svr(port);
    svr.init();
    svr.loop();
    return 0;
}
