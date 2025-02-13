#ifndef SHAPE_H
#define SHAPE_H

#include<string>
#include<utility>
#include<cmath>

class shape
{
protected:
	int width;
	TColor pen_color, brush_color;

	std::pair<std::string, std::string> color_to_string() const;
	void apply_properties(TCanvas* canvas) const;
public:
	shape(int width, TColor pen_color, TColor brush_color) :
		width(width), pen_color(pen_color), brush_color(brush_color){}

	inline void set_width(const int width) { this->width = width; }
	inline void set_pen_color(const TColor pen_color) { this->pen_color = pen_color; }
	inline void set_brush_color(const TColor brush_color) { this->brush_color = brush_color; }
	virtual bool is_clicked(const double x, const double y) const = 0;
	virtual bool is_border_clicked(const double x, const double y) const = 0;
	virtual void draw(TCanvas* canvas, const coordinate_system* coord_system) = 0;
	virtual void translate(const double dx, const double dy) = 0;
	virtual void scale(const double x, const double y) = 0;
	virtual void update_on_drag(const double x, const double y) = 0;
	virtual void draw_selection_box(TCanvas* canvas, const coordinate_system* coord_system) = 0;
	virtual std::string to_svg(const coordinate_system* coord_system) const = 0;
};

#endif
