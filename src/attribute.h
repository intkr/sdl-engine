#pragma once
// TODO: think more about this later

// Attributes used by all objects.
struct Attribute {
	Attribute(std::string _name, bool _active = true) : name(_name), active(_active) {}
	
	std::string name;
	bool active;
};

struct TextAttribute {
	std::string color;
	std::string font; // TODO: there is not a name for the default font yet
};