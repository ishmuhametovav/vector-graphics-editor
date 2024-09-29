#include"coordinate_system.h"
#include"Ellipse.h"

ellipse::ellipse(double x_center, double y_center, double x_radius, double y_radius) : x_center(x_center),
	 y_center(y_center), x_radius(x_radius), y_radius(y_radius)
{

}
void ellipse::draw(TCanvas* canvas, const coordinate_system* coord_system)
{
	int p_x_center = coord_system->to_pixelx(x_center);
	int p_y_center = coord_system->to_pixely(y_center);
	int p_x_radius = static_cast<int>(x_radius * coord_system->get_scale());
	int p_y_radius = static_cast<int>(y_radius * coord_system->get_scale());
	canvas->Ellipse(p_x_center - p_x_radius, p_y_center - p_y_radius,
		 p_x_center + p_x_radius, p_y_center + p_y_radius);
}

void ellipse::translate(const double dx, const double dy)
{
	x_center+=dx;
	y_center+=dy;
}

void ellipse::scale(const double value){}
