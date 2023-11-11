//
// Created by siwan yu on 11/11/2023.
//

#include "coin_drawing_area.h"
#include <cairomm/context.h>
CoinDrawingArea::CoinDrawingArea() {
    set_size_request(100, 100); // 设置绘图区域的推荐尺寸
}

void CoinDrawingArea::set_text(const std::string& text) {
    text_ = text; // 更新文本
    queue_draw(); // 请求重绘制
}

bool CoinDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    // 获取绘图区域的尺寸
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    // 计算圆形的半径
    const int radius = std::min(width, height) / 2 - 10; // 留出边界

    // 绘制圆形
    cr->set_source_rgb(0, 0, 0); // 设置绘制颜色为黑色
    cr->arc(width / 2.0, height / 2.0, radius, 0, 2 * M_PI); // 绘制圆形
    cr->fill_preserve(); // 填充圆形但保留路径
    cr->set_line_width(2.0); // 设置线宽
    cr->stroke(); // 绘制圆形边缘

    // 设置文本颜色为白色，以便与黑色圆形对比
    cr->set_source_rgb(1, 1, 1); // 白色

    // 创建布局并设置文本
    auto layout = create_pango_layout(text_);
    int text_width, text_height;
    layout->get_pixel_size(text_width, text_height);

    // 将文本居中绘制在圆形中
    cr->move_to((width - text_width) / 2, (height - text_height) / 2);
    layout->show_in_cairo_context(cr);

    return true; // 返回true表示on_draw()事件已处理
}