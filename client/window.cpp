#include "window.h"
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

FlipCoinWindow::FlipCoinWindow()
        : m_button("Flip"), m_box(Gtk::Orientation::VERTICAL), m_coin_area() { // 初始化box, button

    set_title("Flip Coin Game");

    // 设置box的边距
    m_box.set_margin(10); // 替代set_border_width的功能
    m_box.append(m_button); // 将button添加到box
    //m_box.append(m_label);
    m_box.append(m_coin_area); // 将m_coin_area添加到m_box中
    set_child(m_box); // 将box设置为window的子widget

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
    //m_label.set_text(result);  // 更新标签显示结果
    m_coin_area.set_text(result); // 更新硬币面值显示


    ::close(sock);  // 关闭socket连接
}
