#ifndef TEXT_H
#define TEXT_H

#include"Shape.h"

class text : public shape
{
	double x, y;
    std::string text;
public:
	text(double x, double y, std::string text, int width, TColor pen_color);
	void draw(TCanvas* canvas, const coordinate_system* coord_system) override;
	void translate(const double dx, const double dy) override;
	void scale(const double x, const double y) override;
	void update_on_drag(const double x, const double y) override;
	void draw_selection_box(TCanvas* canvas, const coordinate_system* coord_system) override;
	bool is_clicked(const double x, const double y) const override;
	bool is_border_clicked(const double x, const double y) const override;
	std::string to_svg(const coordinate_system* coord_system) const override;
};

#endif
