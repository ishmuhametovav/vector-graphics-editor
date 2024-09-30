#include"coordinate_system.h"
#include"Rectangle.h"


rectangle::rectangle(double x1, double y1, double x2, double y2) : x1(x1), y1(y1), x2(x2), y2(y2)
{

}
void rectangle::draw(TCanvas* canvas, const coordinate_system* coord_system)
{
	int p_x1, p_y1, p_x2, p_y2;
	p_x1 = coord_system->to_pixelx(x1);
	p_y1 = coord_system->to_pixely(y1);
	p_x2 = coord_system->to_pixelx(x2);
	p_y2 = coord_system->to_pixely(y2);
	canvas->Rectangle(p_x1, p_y1, p_x2, p_y2);
}
void rectangle::translate(const double dx, const double dy)
{
	x1+=dx; x2+=dx;
	y1+=dy; y2+=dy;
}

void rectangle::scale(const double value)
{

}
