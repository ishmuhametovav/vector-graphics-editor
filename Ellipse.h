#ifndef ELLIPSE_H
#define ELLIPSE_H

#include"Shape.h"

class ellipse : public shape
{
	double x_center, y_center, x_radius, y_radius;
public:
	ellipse(double x_center, double y_center, double x_radius, double y_radius, int width, TColor pen_color, TColor brush_color);
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