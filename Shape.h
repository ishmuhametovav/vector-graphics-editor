#ifndef SHAPE_H
#define SHAPE_H

class shape
{
public:
	virtual void draw() = 0;
	virtual void translate(const double dx, const double dy) = 0;
	virtual void scale(const double value) = 0;
};

#endif
