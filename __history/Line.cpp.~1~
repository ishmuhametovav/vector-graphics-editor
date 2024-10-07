#include"coordinate_system.h"
#include"Line.h"

line::line(double x1, double y1, double x2, double y2) : x1(x1), y1(y1), x2(x2), y2(y2)
{

}

void line::draw(TCanvas* canvas, const coordinate_system* coord_system)
{
	double p_x1 = coord_system->to_pixelx(x1);
	double p_y1 = coord_system->to_pixely(y1);
	double p_x2 = coord_system->to_pixelx(x2);
	double p_y2 = coord_system->to_pixely(y2);
	canvas->MoveTo(p_x1, p_y1);
	canvas->LineTo(p_x2, p_y2);
}

void line::translate(const double dx, const double dy)
{
	x1 += dx; y1 += dy;
	x2 += dx; y2 += dy;
}

void line::scale(const double x, const double y)
{
	x2 = x; y2 = y;
}
