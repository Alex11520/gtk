#ifndef FLIPCOIN_WINDOW_H
#define FLIPCOIN_WINDOW_H

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include "coin_drawing_area.h"


class FlipCoinWindow : public Gtk::Window {
public:
    FlipCoinWindow();
    virtual ~FlipCoinWindow();

protected:
    // method that deals with request
    void on_button_clicked();

    // members
    Gtk::Button m_button;
    //Gtk::Label m_label;
    CoinDrawingArea m_coin_area; // 使用CoinDrawingArea替代Gtk::Label
    Gtk::Box m_box;
};

#endif // FLIPCOIN_WINDOW_H
