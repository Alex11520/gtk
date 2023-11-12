#ifndef FLIPCOIN_WINDOW_H
#define FLIPCOIN_WINDOW_H

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/centerbox.h>

// Declaration of the FlipCoinWindow class which inherits from Gtk::Window
class FlipCoinWindow : public Gtk::Window {
public:
    // Constructor declaration
    FlipCoinWindow();
    // Virtual destructor declaration
    virtual ~FlipCoinWindow();

protected:
    // Signal handler function for button click events
    void on_button_clicked();

    // Widget member variables
    Gtk::Button m_button; // Button for flipping the coin
    Gtk::Label m_label; // Label to display flip results
    Gtk::CenterBox m_center_box; // CenterBox to center the label on the window
    Gtk::Box m_outer_box; // Outer Box to contain all widgets and manage the layout

    // Function to initialize CSS for styling the widgets
    void init_css();

};

#endif // FLIPCOIN_WINDOW_H