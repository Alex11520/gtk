#include <iostream>
#include "window.h"
#include <gtkmm/application.h>
#include <locale>


int main(int argc, char *argv[]) {

    std::cout << "Creating application." << std::endl;
    auto app = Gtk::Application::create("org.gtkmm.examples.base");
    std::cout << "Creating window." << std::endl;
    auto window = new FlipCoinWindow();

    std::cout << "Running application." << std::endl;
    int result = app->make_window_and_run<FlipCoinWindow>(argc, argv);;
    delete window;  // 不要忘记释放内存
    std::cout << "Application finished." << std::endl;
    return result;

}
