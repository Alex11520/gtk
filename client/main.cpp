#include <iostream>
#include "window.h"
#include <gtkmm/application.h> // for creating and running Gtkmm applications
#include <locale>


int main(int argc, char *argv[]) {

    std::cout << "Creating application." << std::endl;
    // Creating an instance of Gtk Application with a unique application ID
    auto app = Gtk::Application::create("org.gtkmm.examples.base");
    std::cout << "Creating window." << std::endl;
    // Creating an instance of the main window
    auto window = new FlipCoinWindow();

    std::cout << "Running application." << std::endl;
    // Running the Gtk application which shows the window
    int result = app->make_window_and_run<FlipCoinWindow>(argc, argv);
    // Cleanup by deleting the window instance
    delete window;
    std::cout << "Application finished." << std::endl;
    // Returning the exit code from the application run
    return result;

}
