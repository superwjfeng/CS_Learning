#include <iostream>
#include <cstring>
#include <ctime>
#include <cassert>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>

#include <sys/time.h>

bool SetNonBlock(int fd)
{
    int fl = fcntl(fd, F_GETFL); // 在底层获取当前fd对应的文件读写标志位
    if (fl < 0)
        return false;
    fcntl(fd, F_SETFL, fl | O_NONBLOCK); // 设置非阻塞
    return true;
}

int main()
{
    while (true)
    {
        std::cout << "time: " << (unsigned long)time(nullptr) << std::endl;
        struct timeval currtime = {0, 0};
        int n = gettimeofday(&currtime, nullptr);
        assert(n == 0);
        (void)n;
        std::cout << "gettimeofday: " << currtime.tv_sec << "." << currtime.tv_usec << std::endl;
        sleep(1);
    }

    // // 0
    // SetNonBlock(0); //只要设置一次，后续就都是非阻塞了

    // char buffer[1024];
    // while (true)
    // {
    //     sleep(1);
    //     errno = 0;
    //     // 非阻塞的时候，我们是以出错的形式返回，告知上层数据没有就绪：
    //     // a. 我们如何甄别是真的出错了
    //     // b. 还是仅仅是数据没有就绪呢？
    //     // 数据就绪了的话，我们就正常读取就行
    //     ssize_t s = read(0, buffer, sizeof(buffer) - 1); //出错，不仅仅是错误返回值，errno变量也会被设置，表明出错原因
    //     if (s > 0)
    //     {
    //         buffer[s-1] = 0;
    //         std::cout << "echo# " << buffer << " errno[---]: " << errno << " errstring: " << strerror(errno) << std::endl;
    //     }
    //     else
    //     {
    //         // 如果失败的errno值是11，就代表其实没错，只不过是底层数据没就绪
    //         //std::cout << "read \"error\" " << " errno: " << errno << " errstring: " << strerror(errno) << std::endl;

    //         if(errno == EWOULDBLOCK || errno == EAGAIN)
    //         {
    //             std::cout << "当前0号fd数据没有就绪, 请下一次再来试试吧" << std::endl;
    //             continue;
    //         }
    //         else if(errno == EINTR)
    //         {
    //             std::cout << "当前IO可能被信号中断，在试一试吧" << std::endl;
    //             continue;
    //         }
    //         else
    //         {
    //             //进行差错处理
    //         }
    //     }
    // }
    return 0;
}