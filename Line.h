#ifndef LINE_H
#define LINE_H

#include"Shape.h"

class line : public shape
{
	double x1, y1, x2, y2;
public:
	line(double x1, double y1, double x2, double y2);
	void draw(TCanvas* canvas, const coordinate_system* coord_system) override;
	void translate(const double dx, const double dy) override;
	void scale(const double x, const double y) override;
    void update_on_drag(const double x, const double y) override;
};

#endif