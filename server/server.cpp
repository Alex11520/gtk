#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <random>

// Constructor for FlipCoinServer with initializer list
FlipCoinServer::FlipCoinServer() : server_fd(0), addrlen(sizeof(address)), is_running(false) {
    // Create a socket and check if it fails
    //socket(int domain, int type, int protocol)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed"); // Print error message
        exit(EXIT_FAILURE); // Exit if socket creation fails
    }

    // Define the server address structure
    address.sin_family = AF_INET; // Set the address family to AF_INET (IPv4)
    address.sin_addr.s_addr = INADDR_ANY; // Allow any IP to connect
    address.sin_port = htons(8080); // Convert the port number to network byte order

    // Bind the socket to the address and port number
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed"); // Print error message
        exit(EXIT_FAILURE); // Exit if bind fails
    }

    // Set the socket to listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen"); // Print error message
        exit(EXIT_FAILURE); // Exit if listen fails
    }
}

// Destructor for FlipCoinServer
FlipCoinServer::~FlipCoinServer() {
    // Close the server file descriptor if the server is running
    if (is_running) {
        close(server_fd);
    }
}

// Function to run the server and accept incoming connections
void FlipCoinServer::run() {
    is_running = true; // Set server running status to true
    int new_socket; // Declare a new socket file descriptor for incoming connections
    long valread; // Variable to store the number of bytes read from the client

    // Server main loop
    while (is_running) {
        std::cout << "Server started. Waiting for connections..." << std::endl;
        // Accept a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            // Check if server is still running before printing an error message
            if(is_running) {
                perror("accept");
                continue; // Continue to the next iteration
            } else {
                std::cout << "Server is shutting down." << std::endl;
                break; // Break the loop if server is stopping
            }
        }

        // Clear the buffer and read data from the socket
        char buffer[1024] = {0};
        valread = read(new_socket, buffer, 1024); // Read data from socket
        std::string coin_result = flip_coin(); // Flip the coin and get the result
        send(new_socket, coin_result.c_str(), coin_result.length(), 0); // Send the result back to the client
        std::cout << "Coin flipped: " << coin_result << std::endl;
        close(new_socket); // Close the connection
    }

    // Close the server socket after exiting the loop
    close(server_fd);
}

// Function to simulate a coin flip
std::string FlipCoinServer::flip_coin() {
    // Use random number generator to simulate coin flip
    std::random_device rd; // Non-deterministic random number generator
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> dis(0, 1); // Distribution on a range [0, 1]
    return dis(gen) == 0 ? "head" : "tail"; // Return "head" or "tail"
}

// Function to stop the server
void FlipCoinServer::stop() {
    is_running = false; // Set running status to false
    close(server_fd); // Close the server file descriptor
}
