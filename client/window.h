#ifndef FLIPCOIN_WINDOW_H
#define FLIPCOIN_WINDOW_H

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>

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
    Gtk::Box m_box;
};

#endif // FLIPCOIN_WINDOW_H
