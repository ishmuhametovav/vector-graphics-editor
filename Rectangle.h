#ifndef RECTANGLE_H
#define RECTANGLE_H

#include"Shape.h"

class rectangle : public shape
{
	double x1,y1,x2,y2;
public:
	rectangle(double x1, double y1, double x2, double y2);
	void draw() override;
	void translate(const double dx, const double dy) override;
	void scale(const double value) override;
};

#endif