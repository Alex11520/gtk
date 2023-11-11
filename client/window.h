#ifndef FLIPCOIN_WINDOW_H
#define FLIPCOIN_WINDOW_H

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/centerbox.h>

class FlipCoinWindow : public Gtk::Window {
public:
    FlipCoinWindow();
    virtual ~FlipCoinWindow();

protected:
    // 信号处理函数
    void on_button_clicked();

    // 控件成员
    Gtk::Button m_button;
    Gtk::Label m_label;
    Gtk::CenterBox m_center_box; // 用于居中标签的CenterBox
    Gtk::Box m_outer_box; // 包含所有控件的Box，负责整体布局


    // 添加的CSS初始化函数
    void init_css();

};

#endif // FLIPCOIN_WINDOW_H