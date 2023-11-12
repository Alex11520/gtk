#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <random>

FlipCoinServer::FlipCoinServer() : server_fd(0), addrlen(sizeof(address)), is_running(false) {
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

FlipCoinServer::~FlipCoinServer() {
    if (is_running) {
        close(server_fd);
    }
}

void FlipCoinServer::run() {
    is_running = true;
    int new_socket;
    long valread;



    while (is_running) {
        std::cout << "Server started. Waiting for connections..." << std::endl;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {

            if(is_running) {
                perror("accept");
                continue;
            } else {
                std::cout << "Server is shutting down." << std::endl;
                break;
            }
        }

        char buffer[1024] = {0};
        valread = read(new_socket, buffer, 1024);
        std::string coin_result = flip_coin();
        send(new_socket, coin_result.c_str(), coin_result.length(), 0);
        std::cout << "Coin flipped: " << coin_result << std::endl;
        close(new_socket);
    }

    close(server_fd);
}

std::string FlipCoinServer::flip_coin() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    return dis(gen) == 0 ? "head" : "tail";
}

void FlipCoinServer::stop() {
    is_running = false;
    close(server_fd);
}
