//
// Created by siwan yu on 11/11/2023.
//

#ifndef FLIPCOIN_COIN_DRAWING_AREA_H
#define FLIPCOIN_COIN_DRAWING_AREA_H

#include <gtkmm/drawingarea.h>
#include <gtkmm.h>
#include <string>

class CoinDrawingArea : public Gtk::DrawingArea {
public:
    CoinDrawingArea();
    void set_text(const std::string& text); // 设置要显示的文本

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

private:
    std::string text_; // 内部存储文本
};


#endif //FLIPCOIN_COIN_DRAWING_AREA_H
