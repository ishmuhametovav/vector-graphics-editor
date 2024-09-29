#ifndef ELLIPSE_H
#define ELLIPSE_H

#include"Shape.h"

class ellipse : public shape
{
	double x_center, y_center, x_radius, y_radius;
public:
	ellipse(double x_center, double y_center, double x_radius, double y_radius);
	void draw(TCanvas* canvas, const coordinate_system* coord_system) override;
	void translate(const double dx, const double dy) override;
	void scale(const double value) override;
};

#endif