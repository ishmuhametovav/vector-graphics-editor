#ifndef SVG_IO_H
#define SVG_IO_H

using namespace tinyxml2;

class svg_io
{
	coordinate_system* coord_system;
	std::forward_list<shape*>* shapes;

	TColor rgb_to_tcolor(const std::string& color_str) const;
	void load_rectangle(XMLElement* svg);
	void load_ellipse(XMLElement* svg);
	void load_line(XMLElement* svg);
	void load_polyline(XMLElement* svg);
public:
	svg_io(coordinate_system* coord_system, std::forward_list<shape*>* shapes) : coord_system(coord_system), shapes(shapes){}
	void save_to_file(const std::string& filename, int& original_width, int& original_height) const;
	void load_from_file(const std::string& filename, int& original_width, int& original_height);
};

#endif
