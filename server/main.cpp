#include "server.h"
#include <csignal>
#include <iostream>

// Declaration of the FlipCoinServer object
FlipCoinServer server;

// Signal handling function that terminates the server on receiving specific signals
void signal_handler(int signal_num) {
    // Output message indicating which signal was received
    std::cout << "Signal " << signal_num << " received, terminating the server." << std::endl;
    // Call the stop function of the server to perform termination tasks
    server.stop();
    // Exit the program with the signal number as the status
    exit(signal_num);
}

// Main function entry point of the program
int main() {

    // Registering signal_handler to handle SIGTERM (termination signal)
    signal(SIGTERM, signal_handler);
    // Registering signal_handler to handle SIGINT (interrupt from keyboard)
    signal(SIGINT, signal_handler);
    // Run the server to start listening for requests
    server.run();

    // Return 0 to indicate normal exit
    return 0;
}
