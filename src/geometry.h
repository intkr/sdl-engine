#pragma once

#include <SDL.h>

// Geometry data used by sprites.
struct SpriteGeometry {
	SpriteGeometry() : texRect(nullptr), baseRect(nullptr), modRect(nullptr), hitbox(nullptr), angle(0.0) {}
	// Used to get the sprite texture from the spritesheet.
	SDL_Rect* texRect;
	// Used as the base hitbox for animations.
	SDL_FRect* baseRect;
	// Post-animation (i.e. "modded") hitbox.
	// This hitbox is positioned relative to the parent entity's center. 
	SDL_FRect* modRect;
	// Used for the final rendering of the sprite.
	// This hitbox contains absolute coordinates within the screen.
	SDL_FRect* hitbox;
	
	// Unit : degrees
	double angle;
}

// Geometry data used by entities.
struct EntityGeometry {
	EntityGeometry() : pos(), angle(0.0) {}
	EntityGeometry(SDL_FPoint _pos, double _angle = 0.0) : pos(_pos), angle(_angle) {}
	
	EntityGeometry EntityGeometry::operator+(const EntityGeometry& other) {
		SDL_FPoint newPos{ pos.x + other.pos.x, pos.y + other.pos.y };
		return EntityGeometry(newPos, angle + other.angle);
	}
	
	// The pos of an entity is absolute within the screen,
	// but the pos of a subentity is relative to its parent entity's pos.
	SDL_FPoint pos;
	double angle;
}