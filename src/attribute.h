#pragma once

// Attributes used by all objects.
struct Attribute {
	Attribute(std::string _name) : name(_name), active(true) {}
	
	std::string name;
	bool active;
};

// TODO: work on this later idk
struct TextAttribute {
	std::string color;
	std::string font; // TODO: there is not a name for the default font yet
};