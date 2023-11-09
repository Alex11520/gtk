#include <iostream>
#include "window.h"
#include <gtkmm/application.h>
#include <locale>


int main(int argc, char *argv[]) {
    // 设置C++全局locale为C locale
    std::locale::global(std::locale("en_US.UTF-8"));
//
//    auto app = Gtk::Application::create("org.gtkmm.examples.base");
////    FlipCoinWindow window;
//
//    // Shows the window and returns when it is closed.
//    return app->make_window_and_run<FlipCoinWindow>(argc, argv);
    std::cout << "Creating application." << std::endl;
    auto app = Gtk::Application::create("org.gtkmm.examples.base");
    std::cout << "Creating window." << std::endl;
    auto window = new FlipCoinWindow();  // 修改此处来动态分配窗口

    // 显示窗口并返回当它被关闭
    std::cout << "Running application." << std::endl;
    int result = app->make_window_and_run<FlipCoinWindow>(argc, argv);;
    delete window;  // 不要忘记释放内存
    std::cout << "Application finished." << std::endl;
    return result;

}
