#pragma once

#include <string>

#include "SDL.h"

#include "clock.h"
#include "exception.h"
#include "transform.h"

// Base class for all in-game objects.
class GameObject {
public:
	GameObject(std::string _name, SDL_FPoint initialPos) : name(_name), transform(initialPos) {}
	~GameObject();
	
    // TODO: check if this works between derived classes
	bool operator==(const GameObject& other) const {
        return name == other.name;
    }
	
	virtual void update(ms delta) {}

protected:
	std::string name;
	bool active;
	
	Transform transform;
};