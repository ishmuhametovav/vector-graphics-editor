#ifndef COORDINATE_SYSTEM_H
#define COORDINATE_SYSTEM_H

class coordinate_system
{
	double x_min, y_min, x_max, y_max;
	double scale;
public:
	coordinate_system(double x_min = 0, double y_min = 0, double x_max = 1000, double y_max = 1000, double scale = 1.0);

	int to_pixelx(const double x) const;
	int to_pixely(const double y) const;

	double to_coordx(const int pixel_x) const;
	double to_coordy(const int pixel_y) const;
};

#endif
