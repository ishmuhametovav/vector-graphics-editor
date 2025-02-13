#include<vector>
#include<utility>
#include"coordinate_system.h"
#include"Pencil.h"
#include<algorithm>

pencil::pencil(double x1, double y1, double x2, double y2, int width, TColor pen_color) :
	points{ {x1, y1}, {x2, y2} }, shape(width, pen_color, clNone) {}

void pencil::draw(TCanvas* canvas, const coordinate_system* coord_system)
{
	apply_properties(canvas);

	for (unsigned int i = 1; i < points.size(); ++i)
	{
		int p_x1 = coord_system->to_pixelx(points[i - 1].first);
		int p_y1 = coord_system->to_pixely(points[i - 1].second);
		int p_x2 = coord_system->to_pixelx(points[i].first);
		int p_y2 = coord_system->to_pixely(points[i].second);

		canvas->MoveTo(p_x1, p_y1);
		canvas->LineTo(p_x2, p_y2);
	}
}

void pencil::translate(const double dx, const double dy)
{
	for(auto& [u, v] : points)
	{
		u += dx; v += dy;
	}
}

void pencil::scale(const double x, const double y)
{
	double min_x = points[0].first, max_x = points[0].first;
    double min_y = points[0].second, max_y = points[0].second;

    for (const auto& point : points)
    {
        if (point.first < min_x) min_x = point.first;
        if (point.first > max_x) max_x = point.first;
        if (point.second < min_y) min_y = point.second;
        if (point.second > max_y) max_y = point.second;
    }

	double width = max_x - min_x;
    double height = max_y - min_y;

	double new_width = x - min_x;
    double new_height = y - min_y;

	double scale_x = (new_width == 0.0) ? 1.0 : new_width / width;
	double scale_y = (new_height == 0.0) ? 1.0 : new_height / height;

    for (auto& point : points)
	{
		point.first = min_x + (point.first - min_x) * scale_x;
		point.second = min_y + (point.second - min_y) * scale_y;
	}

}

void pencil::update_on_drag(const double x, const double y)
{
	points.push_back({x, y});
}

void pencil::draw_selection_box(TCanvas* canvas, const coordinate_system* coord_system)
{
	canvas->Pen->Width = 1;
	canvas->Pen->Style = psDash;
	canvas->Pen->Color = clBlack;
	canvas->Brush->Style = bsClear;

	double x1 = points[0].first, x2 = points[0].first;
	double y1 = points[0].second, y2 = points[0].second;

	for (const auto& point : points)
	{
		if (point.first < x1) x1 = point.first;
		if (point.first > x2) x2 = point.first;
		if (point.second < y1) y1 = point.second;
		if (point.second > y2) y2 = point.second;
	}

	int p_x1, p_y1, p_x2, p_y2;
	p_x1 = coord_system->to_pixelx(x1);
	p_y1 = coord_system->to_pixely(y1);
	p_x2 = coord_system->to_pixelx(x2);
	p_y2 = coord_system->to_pixely(y2);

	int min_x = std::min(p_x1, p_x2);
	int max_x = std::max(p_x1, p_x2);
	int min_y = std::min(p_y1, p_y2);
	int max_y = std::max(p_y1, p_y2);

	canvas->Rectangle(min_x - 4 - width, min_y - 4 - width, max_x + 4 + width, max_y + 4 + width);
}

bool pencil::is_clicked(const double x, const double y) const
{
	double min_x = points[0].first, max_x = points[0].first;
	double min_y = points[0].second, max_y = points[0].second;

	for (const auto& point : points)
	{
		if (point.first < min_x) min_x = point.first;
		if (point.first > max_x) max_x = point.first;
		if (point.second < min_y) min_y = point.second;
		if (point.second > max_y) max_y = point.second;
	}

	return (x >= min_x && x <= max_x && y >= min_y && y <= max_y);
}

bool pencil::is_border_clicked(const double x, const double y) const
{
	double max_x = points[0].first, max_y = points[0].second;

	for (const auto& point : points)
	{
		if (point.first > max_x) max_x = point.first;
		if (point.second > max_y) max_y = point.second;
	}

	return (x >= max_x && x <= max_x + width + 4 && y >= max_y && y <= max_y + width + 4);
}

std::string pencil::to_svg(const coordinate_system* coord_system) const
{
	std::string result;
	auto colors = color_to_string();

	result = "<polyline points=\"";

	for(auto [x, y] : points)
	{
		int p_x = coord_system->to_pixelx(x);
		int p_y = coord_system->to_pixely(y);
		result += (std::to_string(p_x) + ',' +std::to_string(p_y) + ' ');
	}

	result[result.length()-1] = '\"';

	result += " stroke-width=\"" + std::to_string(width) + "\" stroke=\""
		+ colors.first + "\" fill=\"" + "none" + "\"/>";

	return result;
}
