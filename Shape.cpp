#include"coordinate_system.h"
#include"Shape.h"
#include<sstream>
#include<iomanip>

void shape::apply_properties(TCanvas* canvas) const
{
    canvas->Brush->Color = brush_color;
	canvas->Pen->Style = psSolid;
	canvas->Brush->Style = bsSolid;
	canvas->Pen->Color = pen_color;
	canvas->Pen->Width = width;
}

std::pair<std::string, std::string> shape::color_to_string() const
{
    std::pair<std::string, std::string> result;

	auto color_to_hex = [](int color) -> std::string
	{
		std::ostringstream sstream;
		int b = (color & 0x00FF0000) >> 16;
		int g = (color & 0x0000FF00) >> 8;
		int r = color & 0x000000FF;
		sstream << "#" << std::setw(2) << std::setfill('0') << std::hex << r
				<< std::setw(2) << std::setfill('0') << g
				<< std::setw(2) << std::setfill('0') << b;
		return sstream.str();
    };

    result.first = color_to_hex(pen_color);
    result.second = color_to_hex(brush_color);

    return result;
}
