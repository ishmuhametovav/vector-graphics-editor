#include"coordinate_system.h"
#include"Rectangle.h"
#include<algorithm>

rectangle::rectangle(double x1, double y1, double x2, double y2, int width, TColor pen_color, TColor brush_color) :
	x1(x1), y1(y1), x2(x2), y2(y2), shape(width, pen_color, brush_color)
{

}
void rectangle::draw(TCanvas* canvas, const coordinate_system* coord_system)
{
	int p_x1, p_y1, p_x2, p_y2;
	p_x1 = coord_system->to_pixelx(x1);
	p_y1 = coord_system->to_pixely(y1);
	p_x2 = coord_system->to_pixelx(x2);
	p_y2 = coord_system->to_pixely(y2);

	apply_properties(canvas);
	canvas->Rectangle(p_x1, p_y1, p_x2, p_y2);
}
void rectangle::translate(const double dx, const double dy)
{
	x1+=dx; x2+=dx;
	y1+=dy; y2+=dy;
}

void rectangle::scale(const double x, const double y)
{
	double x_center = (x1 + x2)/2;
	double y_center = (y1 + y2)/2;

	double deltax = std::abs(x_center - x), deltay = std::abs(y_center - y);

	x1 = x_center - deltax;
	y1 = y_center - deltay;

	x2 = x_center + deltax;
	y2 = y_center + deltay;
}

void rectangle::update_on_drag(const double x, const double y)
{
	x2 = x; y2 = y;
}

void rectangle::draw_selection_box(TCanvas* canvas, const coordinate_system* coord_system)
{
	canvas->Pen->Width = 1;
	canvas->Pen->Style = psDash;
	canvas->Pen->Color = clBlack;
	canvas->Brush->Style = bsClear;

	int p_x1, p_y1, p_x2, p_y2;
	p_x1 = coord_system->to_pixelx(x1);
	p_y1 = coord_system->to_pixely(y1);
	p_x2 = coord_system->to_pixelx(x2);
	p_y2 = coord_system->to_pixely(y2);

	int min_x = std::min(p_x1, p_x2);
	int max_x = std::max(p_x1, p_x2);
	int min_y = std::min(p_y1, p_y2);
	int max_y = std::max(p_y1, p_y2);

	canvas->Rectangle(min_x - 4 - width, min_y - 4 - width, max_x + 4 + width, max_y + 4 + width);
}

bool rectangle::is_clicked(const double x, const double y) const
{
	double min_x = std::min(x1, x2);
	double max_x = std::max(x1, x2);
	double min_y = std::min(y1, y2);
	double max_y = std::max(y1, y2);

	return (x >= min_x && x <= max_x && y >= min_y && y <= max_y);
}

bool rectangle::is_border_clicked(const double x, const double y) const
{
	double max_x = std::max(x1, x2);
	double max_y = std::max(y1, y2);

	return (x >= max_x && x <= max_x + width + 4 && y >= max_y && y <= max_y + width + 4);
}

std::string rectangle::to_svg(const coordinate_system* coord_system) const
{
	std::string result;
	auto colors = color_to_string();

	int min_x = std::min(coord_system->to_pixelx(x1), coord_system->to_pixelx(x2));
	int min_y = std::min(coord_system->to_pixely(y1), coord_system->to_pixely(y2));
	int rect_width = std::abs(coord_system->to_pixelx(x1) - coord_system->to_pixelx(x2));
	int rect_height = std::abs(coord_system->to_pixely(y1) - coord_system->to_pixely(y2));

	result = "<rect x=\"" + std::to_string(min_x) + "\" y=\"" + std::to_string(min_y) + "\" width=\"" + std::to_string(rect_width)
		+ "\" height=\"" + std::to_string(rect_height) + "\" stroke-width=\"" + std::to_string(width) + "\" stroke=\""
		+ colors.first + "\" fill=\"" + colors.second + "\"/>";

	return result;
}
