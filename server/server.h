#ifndef FLIPCOIN_SERVER_H
#define FLIPCOIN_SERVER_H

#include <string>
#include <netinet/in.h>
#include <vector>



// FlipCoinServer class definition
class FlipCoinServer {
public:
    FlipCoinServer();  // Constructor
    ~FlipCoinServer(); // Destructor

    void run();  // Starts the server to listen for requests
    void stop(); // Stops the server and releases resources

private:
    int server_fd; // File descriptor for the server socket
    struct sockaddr_in address; // Structure for storing server IP and port details
    int addrlen; // Length of the address data structure
    bool is_running; // Flag to keep track of server's running status

    std::string flip_coin(); // Private method to simulate flipping a coin
};


#endif // FLIPCOIN_SERVER_H
