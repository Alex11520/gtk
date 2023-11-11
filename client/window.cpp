#include "window.h"
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <gtkmm/cssprovider.h>
#include <gtkmm/aspectframe.h>

FlipCoinWindow::FlipCoinWindow() : m_button("Flip"), m_label("?"), m_center_box(), m_outer_box(Gtk::Orientation::VERTICAL)  {
    // game name
    set_title("Flip Coin Game");
    // label default text
    m_label.set_text("?");
    // label size
    m_label.set_size_request(100, 100);

    //create css
    init_css();

    //create a aspect frame
    Gtk::AspectFrame aspect_frame( 1.0, false);
    aspect_frame.set_child(m_label);
    aspect_frame.set_halign(Gtk::Align::CENTER); //horizontal
    aspect_frame.set_valign(Gtk::Align::CENTER); //vertical

    // put AspectFrame inside CenterBox and in the center
    m_center_box.set_center_widget(aspect_frame);

    // put CenterBox inside outer Box
    m_outer_box.set_expand(true);
    m_outer_box.append(m_center_box);
    m_button.set_margin_top(10);
    m_outer_box.append(m_button);
    m_button.set_halign(Gtk::Align::CENTER);

    // 设置整个窗口的子项为外部盒子
    set_child(m_outer_box);

    // 组织布局
    m_button.signal_clicked().connect(sigc::mem_fun(*this, &FlipCoinWindow::on_button_clicked));


}

FlipCoinWindow::~FlipCoinWindow() {}

void FlipCoinWindow::on_button_clicked() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "\n Socket creation error \n";
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        std::cout << "\nInvalid address/ Address not supported \n";
        return;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "\nConnection Failed \n";
        return;
    }

    send(sock, "flip", strlen("flip"), 0);  // 发送翻转请求
    valread = read(sock, buffer, 1024);  // 读取服务端的响应
    std::string result(buffer, valread);  // 将响应转换为std::string
    m_label.set_text(result);  // 更新标签显示结果

    ::close(sock);  // 关闭socket连接
}
void FlipCoinWindow::init_css() {
    auto css_provider = Gtk::CssProvider::create();
    const char* css_data =".coin-label {   border-radius: 9999px;    background-color: gold;   padding: 5px;   min-width: 50px;    min-height: 50px; }";
    css_provider->load_from_data(css_data);


    // 为标签添加样式
    m_label.get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    m_label.get_style_context()->add_class("coin-label");
}