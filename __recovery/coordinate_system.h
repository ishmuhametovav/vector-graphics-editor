class coordinate_system
{
	double x_min, y_min, x_max, y_max;
	double scale;
public:
	coordinate_system(double x_min = 0, double y_min = 0, double x_max = 1000, double y_max = 1000, double scale = 1.0);

	int to_pixelx(const double x, const int screen_width) const;
	int to_pixely(const double y, const int screen_height) const;

	double to_coordx(const int pixel_x, const int screen_width) const;
	double to_coordy(const int pixel_y, const int screen_height) const;
};
