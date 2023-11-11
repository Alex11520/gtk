#ifndef FLIPCOIN_SERVER_H
#define FLIPCOIN_SERVER_H

#include <string>
#include <netinet/in.h>

class FlipCoinServer {
public:
    FlipCoinServer();
    ~FlipCoinServer();

    void run();
    void stop();

private:
    int server_fd; // 服务器的文件描述符
    struct sockaddr_in address;
    int addrlen;
    bool is_running;

    std::string flip_coin(); // 模拟翻转硬币
};

#endif // FLIPCOIN_SERVER_H
