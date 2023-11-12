#include "window.h"
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <gtkmm/cssprovider.h>
#include <gtkmm/aspectframe.h>

// Definition of the FlipCoinWindow constructor
FlipCoinWindow::FlipCoinWindow() : m_button("Flip"), m_label("?"), m_center_box(), m_outer_box(Gtk::Orientation::VERTICAL)  {
    // Set up the initial window properties
    set_title("Flip Coin Game"); // Setting the title of the window
    m_label.set_text("?"); // Setting the default text of the label
    m_label.set_size_request(100, 100); // Requesting a size for the label


    //create css
    init_css();

    //create a aspect frame
    Gtk::AspectFrame aspect_frame(1.0, false); // Creating an AspectFrame to maintain the label's aspect ratio
    aspect_frame.set_child(m_label); // Adding the label to the aspect frame
    aspect_frame.set_halign(Gtk::Align::CENTER); // Aligning the frame horizontally
    aspect_frame.set_valign(Gtk::Align::CENTER); // Aligning the frame vertically

    // put AspectFrame inside CenterBox and in the center
    m_center_box.set_center_widget(aspect_frame);

    // Outer Box setup
    m_outer_box.set_expand(true); // Allowing the box to expand to fill space
    m_outer_box.append(m_center_box); // Adding the CenterBox to the outer box
    m_button.set_margin_top(10); // Setting a top margin for the button
    m_outer_box.append(m_button); // Adding the button to the outer box
    m_button.set_halign(Gtk::Align::CENTER); // Center-aligning the button within the outer box

    // Set up the window's child widget
    set_child(m_outer_box); // Setting the outer box as the child of the window

    // Connect the button's click event to the signal handler
    m_button.signal_clicked().connect(sigc::mem_fun(*this, &FlipCoinWindow::on_button_clicked));


}

FlipCoinWindow::~FlipCoinWindow() {}

// FlipCoinWindow member function definition for handling button click event
void FlipCoinWindow::on_button_clicked() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "\n Socket creation error \n";
        return;
    }

    // Setting up the server address structure
    serv_addr.sin_family = AF_INET; // Internet Protocol family
    serv_addr.sin_port = htons(8080); // Convert to network byte order

    // Convert the IP address to binary form and check for errors
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        std::cout << "\nInvalid address/ Address not supported \n";
        return;
    }

    // Attempt to connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "\nConnection Failed \n";
        return;
    }

    // Send flip request to server
    send(sock, "flip", strlen("flip"), 0);
    // Read server response into the buffer
    valread = read(sock, buffer, 1024);
    // Convert buffer data to a std::string object
    std::string result(buffer, valread);
    // Update GUI label to display the result
    m_label.set_text(result);

    // Close the socket connection
    ::close(sock);
}

// FlipCoinWindow member function definition for initializing CSS styling
void FlipCoinWindow::init_css() {
    // Create a new CSS style provider
    auto css_provider = Gtk::CssProvider::create();
    // CSS style data for coin label
    const char* css_data =".coin-label { border-radius: 9999px; background-color: gold; padding: 5px; min-width: 50px; min-height: 50px; }";
    // Load CSS data into the provider
    css_provider->load_from_data(css_data);

    // Apply the CSS styles to the coin label
    m_label.get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    m_label.get_style_context()->add_class("coin-label");
}
