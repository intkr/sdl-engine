#pragma once

struct ObjectAttribute {
	Attribute(std::string _name) : name(_name), visibility(true), activeness(true) {}
	
	std::string name;
	bool visibility;
	bool activeness;
};

struct TextAttribute {
	std::string color;
	std::string font; // TODO: there is not a name for the default font yet
}