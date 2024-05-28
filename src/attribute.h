#pragma once

// Attributes used by entities and sprites.
struct ObjectAttribute {
	ObjectAttribute(std::string _name) : name(_name), visibility(true), activeness(true) {}
	
	std::string name;
	bool visibility;
	bool activeness;
};

// TODO: implement this when i get back home
struct SpriteAttribute {
	/* only add attributes that may differ from sprite to sprite, even within the same entity.

	Some examples I can think of rn:
		- collidable
			true for sprites that should have collision,
			false for sprites that shouldn't have collision (for purely visual stuff such as particle effects)
		- renderable
			true for sprites with textures,
			false for sprites without textures (for triggers or whatever those kind of stuff)
	*/
};

struct TextAttribute {
	std::string color;
	std::string font; // TODO: there is not a name for the default font yet
};