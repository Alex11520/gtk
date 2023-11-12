#include "server.h"
#include <csignal>
#include <iostream>

FlipCoinServer server;
void signal_handler(int signal_num) {
    std::cout << "Signal " << signal_num << " received, terminating the server." << std::endl;
    server.stop();
    exit(signal_num);
}

int main() {

    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
    server.run();

    return 0;
}
