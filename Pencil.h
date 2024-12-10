#ifndef PENCIL_H
#define PENCIL_H

#include"Shape.h"

class pencil : public shape
{
	std::vector<std::pair<double, double>> points;
public:
	pencil(double x1, double y1, double x2, double y2, int width, TColor pen_color);

    inline void set_brush_color(const TColor brush_color) = delete;
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
