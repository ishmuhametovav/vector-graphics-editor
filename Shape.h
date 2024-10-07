#ifndef SHAPE_H
#define SHAPE_H

class shape
{
public:
	virtual void draw(TCanvas* canvas, const coordinate_system* coord_system) = 0;
	virtual void translate(const double dx, const double dy) = 0;
	virtual void scale(const double x, const double y) = 0;
	virtual void update_on_drag(const double x, const double y) = 0;
};

#endif
