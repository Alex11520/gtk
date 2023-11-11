#include "server.h"
#include <locale>
#include <csignal>
#include <iostream>

FlipCoinServer server;
void signal_handler(int signal_num) {
    std::cout << "Signal " << signal_num << " received, terminating the server." << std::endl;
    server.stop(); // 调用服务器的停止方法
    exit(signal_num);
}

int main() {
    // 设置C++全局locale为C locale
    std::locale::global(std::locale("C"));
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
    server.run();

    return 0;
}
