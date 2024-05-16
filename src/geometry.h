#pragma once

#include <SDL.h>

// Geometry data used by sprites.
struct SpriteGeometry {
	SpriteGeometry() : texRect(nullptr), baseRect(nullptr), modRect(nullptr), hitbox(nullptr), angle(0.0) {}
	// Used to get the sprite texture from the spritesheet.
	SDL_Rect* texRect;
	// Used as the base hitbox for animations.
	SDL_FRect* baseRect;
	// Post-animation hitbox, position relative to entity.
	SDL_FRect* modRect;
	// Final, absolute-positioned hitbox.
	SDL_FRect* hitbox;
	
	// Unit is in degrees.
	double angle;
}

// Positional data used by entities.
// TODO: this name is ass, change
struct Orientation {
	Orientation() : position(), angle(0.0) {}
	Orientation(SDL_FPoint _pos, double _angle = 0.0) : position(_pos), angle(_angle) {}
	
	Orientation Orientation::operator+(const Orientation& other) {
		SDL_FPoint newPos{ position.x + other.position.x, position.y + other.position.y };
		return Orientation(newPos, angle + other.angle);
	}
	
	// The position of an entity is absolute,
	// but the position of a subentity is relative to its parent entity's position.
	SDL_FPoint position;
	double angle;
}