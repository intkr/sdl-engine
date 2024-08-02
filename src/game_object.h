#pragma once

#include "geometry.h"
#include "exception.h"

// Base class for all ingame objects.
class GameObject {
public:
	GameObject(std::string _name, Point<float> point) : name(_name), position(point) {}
	~GameObject();
	
    // TODO: check if this works with derived classes (equal / different types)
	bool operator==(const GameObject& other) const {
        return name == other.name;
    }
	
	void update() = 0;
	void render() = 0;

protected:
	std::string name;
	Position position;
};