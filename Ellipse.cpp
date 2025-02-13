
#include"coordinate_system.h"
#include"Ellipse.h"
#include<algorithm>

ellipse::ellipse(double x_center, double y_center, double x_radius, double y_radius, int width, TColor pen_color, TColor brush_color) :
	x_center(x_center), y_center(y_center), x_radius(x_radius), y_radius(y_radius), shape(width, pen_color, brush_color)
{

}
void ellipse::draw(TCanvas* canvas, const coordinate_system* coord_system)
{
	int p_x_center = coord_system->to_pixelx(x_center);
	int p_y_center = coord_system->to_pixely(y_center);
	int p_x_radius = static_cast<int>(x_radius * coord_system->get_scale());
	int p_y_radius = static_cast<int>(y_radius * coord_system->get_scale());
    apply_properties(canvas);
	canvas->Ellipse(p_x_center - p_x_radius, p_y_center - p_y_radius,
		 p_x_center + p_x_radius, p_y_center + p_y_radius);
}

void ellipse::translate(const double dx, const double dy)
{
	x_center+=dx;
	y_center+=dy;
}

void ellipse::scale(const double x, const double y)
{
	x_radius = std::abs(x_center - x);
	y_radius = std::abs(y_center - y);
}

void ellipse::update_on_drag(const double x, const double y)
{
	scale(x, y);
}

void ellipse::draw_selection_box(TCanvas* canvas, const coordinate_system* coord_system)
{
	canvas->Pen->Width = 1;
	canvas->Pen->Style = psDash;
	canvas->Pen->Color = clBlack;
	canvas->Brush->Style = bsClear;

	int p_x1, p_y1, p_x2, p_y2;
	p_x1 = coord_system->to_pixelx(x_center - x_radius);
	p_y1 = coord_system->to_pixely(y_center - y_radius);
	p_x2 = coord_system->to_pixelx(x_center + x_radius);
	p_y2 = coord_system->to_pixely(y_center + y_radius);

	int min_x = std::min(p_x1, p_x2);
	int max_x = std::max(p_x1, p_x2);
	int min_y = std::min(p_y1, p_y2);
	int max_y = std::max(p_y1, p_y2);

	canvas->Rectangle(min_x - 4 - width, min_y - 4 - width, max_x + 4 + width, max_y + 4 + width);
}

bool ellipse::is_clicked(const double x, const double y) const
{
	double x1 = x_center - x_radius;
	double y1 = y_center - y_radius;
	double x2 = x_center + x_radius;
	double y2 = y_center + y_radius;
	double min_x = std::min(x1, x2);
	double max_x = std::max(x1, x2);
	double min_y = std::min(y1, y2);
	double max_y = std::max(y1, y2);

	return (x >= min_x && x <= max_x && y >= min_y && y <= max_y);
	return false;
}

bool ellipse::is_border_clicked(const double x, const double y) const
{
	double x1 = x_center - x_radius;
	double y1 = y_center - y_radius;
	double x2 = x_center + x_radius;
	double y2 = y_center + y_radius;
	double max_x = std::max(x1, x2);
	double max_y = std::max(y1, y2);

	return (x >= max_x && x <= max_x + width + 4 && y >= max_y && y <= max_y + width + 4);
}

std::string ellipse::to_svg(const coordinate_system* coord_system) const
{
	std::string result;
	auto colors = color_to_string();

	int p_center_x = coord_system->to_pixelx(x_center);
	int p_center_y = coord_system->to_pixelx(y_center);
	int p_radius_x = coord_system->to_pixelx(x_radius);
	int p_radius_y = coord_system->to_pixelx(y_radius);

	result = "<ellipse cx=\"" + std::to_string(p_center_x) + "\" cy=\"" + std::to_string(p_center_y) + "\" rx=\"" + std::to_string(p_radius_x)
		+ "\" ry=\"" + std::to_string(p_radius_y) + "\" stroke-width=\"" + std::to_string(width) + "\" stroke=\""
		+ colors.first + "\" fill=\"" + colors.second + "\"/>";

	return result;
}
