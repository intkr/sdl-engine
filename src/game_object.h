#pragma once

#include "attribute.h"
#include "geometry.h"
#include "exception.h"

// Base class for all ingame objects.
class GameObject {
public:
	GameObject(std::string name, Point<float> point) : attribute(name), position(point) {}
	~GameObject();
	
    // TODO: check if this works with derived classes (equal / different types)
	bool operator==(const GameObject& other) const {
        return attribute.name == other.attribute.name;
    }
	
	void update() = 0;
	void render() = 0;

private:
	Attribute attribute;
	Position position;
};