#include<string>
#include"coordinate_system.h"
#include"Text.h"

text::text(double x, double y, std::string text, int width, TColor pen_color) : x(x), y(y), text(text), shape(width, pen_color, clNone) {}

void text::draw(TCanvas* canvas, const coordinate_system* coord_system)
{

}

void text::translate(const double dx, const double dy)
{
    x += dx;
    y += dy;
}

void text::scale(const double x, const double y)
{

}

void text::update_on_drag(const double x, const double y)
{

}

void text::draw_selection_box(TCanvas* canvas, const coordinate_system* coord_system)
{

}

bool text::is_clicked(const double x, const double y) const
{

}

bool text::is_border_clicked(const double x, const double y) const
{

}

std::string text::to_svg(const coordinate_system* coord_system) const
{
    return nullptr;
}
