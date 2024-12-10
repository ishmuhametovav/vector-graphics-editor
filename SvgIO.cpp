#include<string>
#include<forward_list>
#include<vector>
#include<sstream>
#include<fstream>
#include"tinyxml2.h"
#include"coordinate_system.h"
#include"Rectangle.h"
#include"Ellipse.h"
#include"Line.h"
#include"Pencil.h"
#include"SvgIO.h"



TColor svg_io::rgb_to_tcolor(const std::string& color_str) const
{
	if (color_str.size() != 7 || color_str[0] != '#')
		return clBlack;
	int r = std::stoi(color_str.substr(1, 2), nullptr, 16);
	int g = std::stoi(color_str.substr(3, 2), nullptr, 16);
	int b = std::stoi(color_str.substr(5, 2), nullptr, 16);

	return (TColor)((b << 16) | (g << 8) | r);
}

void svg_io::load_rectangle(XMLElement* element)
{
	if (!element) return;
	if (std::string(element->Value()) == "rect")
	{
        int p_x = element->IntAttribute("x");
        int p_y = element->IntAttribute("y");
        int p_width = element->IntAttribute("width");
        int p_height = element->IntAttribute("height");
        int stroke_width = element->IntAttribute("stroke-width", 1);

        double x1 = coord_system->to_coordx(p_x), y1 = coord_system->to_coordy(p_y),
               x2 = coord_system->to_coordx(p_x + p_width), y2 = coord_system->to_coordy(p_y + p_height);

        std::string stroke_color = element->Attribute("stroke") ? element->Attribute("stroke") : "#000000";
        std::string fill_color = element->Attribute("fill") ? element->Attribute("fill") : "#FFFFFF";

        TColor pen_color = rgb_to_tcolor(stroke_color);
        TColor brush_color = rgb_to_tcolor(fill_color);

        shapes->push_front(new rectangle(x1, y1, x2, y2, stroke_width, pen_color, brush_color));
    }

	for (XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement())
		load_rectangle(child);
}

void svg_io::load_ellipse(XMLElement* element)
{
	if (!element) return;
	if (std::string(element->Value()) == "ellipse")
	{
		int p_cx = element->IntAttribute("cx");
		int p_cy = element->IntAttribute("cy");
		int p_rx = element->IntAttribute("rx");
		int p_ry = element->IntAttribute("ry");
		int stroke_width = element->IntAttribute("stroke-width", 1);

		double cx = coord_system->to_coordx(p_cx), cy = coord_system->to_coordy(p_cy),
		rx = coord_system->to_coordx(p_rx), ry = coord_system->to_coordy(p_ry);

		std::string stroke_color = element->Attribute("stroke") ? element->Attribute("stroke") : "#000000";
		std::string fill_color = element->Attribute("fill") ? element->Attribute("fill") : "#FFFFFF";

		TColor pen_color = rgb_to_tcolor(stroke_color);
		TColor brush_color = rgb_to_tcolor(fill_color);

		shapes->push_front(new ellipse(cx, cy, rx, ry, stroke_width, pen_color, brush_color));
	}
	for (XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement())
		load_ellipse(child);
}

void svg_io::load_line(XMLElement* element)
{
	if (!element) return;
	if (std::string(element->Value()) == "line")
	{
		int p_x1 = element->IntAttribute("x1");
		int p_y1 = element->IntAttribute("y1");
		int p_x2 = element->IntAttribute("x2");
		int p_y2 = element->IntAttribute("y2");
		int stroke_width = element->IntAttribute("stroke-width", 1);

		double x1 = coord_system->to_coordx(p_x1), y1 = coord_system->to_coordy(p_y1),
		x2 = coord_system->to_coordx(p_x2), y2 = coord_system->to_coordy(p_y2);

		std::string stroke_color = element->Attribute("stroke") ? element->Attribute("stroke") : "#000000";

		TColor pen_color = rgb_to_tcolor(stroke_color);

		shapes->push_front(new line(x1, y1, x2, y2, stroke_width, pen_color));
	}
	for (XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement())
		load_line(child);
}

void svg_io::load_polyline(XMLElement* element)
{
	if (!element) return;
	if (std::string(element->Value()) == "polyline")
    {
        const char* points_attr = element->Attribute("points");
        if (!points_attr) return; // Если атрибут отсутствует, выходим

        std::istringstream points_stream(points_attr);
        std::vector<std::pair<double, double>> points;

        std::string point;
		while (std::getline(points_stream, point, ' '))
		{
            size_t comma_pos = point.find(',');
            if (comma_pos != std::string::npos)
            {
                double x = coord_system->to_coordx(std::stod(point.substr(0, comma_pos)));
                double y = coord_system->to_coordy(std::stod(point.substr(comma_pos + 1)));
                points.emplace_back(x, y);
            }
		}
		if (points.size() < 2) return;

        int stroke_width = element->IntAttribute("stroke-width", 1);
        std::string stroke_color = element->Attribute("stroke") ? element->Attribute("stroke") : "#000000";

        TColor pen_color = rgb_to_tcolor(stroke_color);

		pencil* new_pencil = new pencil(points[0].first, points[0].second, points[1].first, points[1].second, stroke_width, pen_color);

		for (size_t i = 2; i < points.size(); ++i) new_pencil->update_on_drag(points[i].first, points[i].second);
        shapes->push_front(new_pencil);
	}
	for (XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement())
		load_polyline(child);
}


void svg_io::save_to_file(const std::string& filename, int& original_width, int& original_height) const
{
	double scale = coord_system->get_scale();
	coord_system->set_scale(1.0);

	std::string result = std::string("<?xml version=\"1.0\"?>\n") +
		std::string("<svg width=\"") + std::to_string(original_width) + std::string("\" height=\"") + std::to_string(original_height) +
		std::string("\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:svg=\"http://www.w3.org/2000/svg\">\n");

	for(auto i : *shapes)
		result += ("  " + i->to_svg(coord_system) + "\n");

	result += "</svg>\n";

	std::ofstream ofs(filename);
	if(!ofs.is_open())
		throw std::invalid_argument("incorect file name!");

	ofs << result;
	ofs.close();

	coord_system->set_scale(scale);
}

void svg_io::load_from_file(const std::string& filename, int& original_width, int& original_height)
{
	tinyxml2::XMLDocument doc;

	if (doc.LoadFile(filename.c_str()) != XML_SUCCESS)
		throw std::invalid_argument("no such file");

	XMLElement* svg = doc.FirstChildElement("svg");

	if (!svg) throw std::invalid_argument("<svg> is not found.");

	const char* width_attr = svg->Attribute("width");
	const char* height_attr = svg->Attribute("height");
	original_width = std::stod(width_attr);
	original_height = std::stod(height_attr);

	load_rectangle(svg);
	load_ellipse(svg);
	load_line(svg);
	load_polyline(svg);
}
