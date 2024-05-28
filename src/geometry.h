#pragma once

#include <SDL.h>

// Geometric data used by sprites.
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

// Geometric data used by entities.
struct EntityGeometry {
	EntityGeometry() : position(), angle(0.0) {}
	EntityGeometry(SDL_FPoint _pos, double _angle = 0.0) : position(_pos), angle(_angle) {}
	
	EntityGeometry EntityGeometry::operator+(const EntityGeometry& other) {
		SDL_FPoint newPos{ position.x + other.position.x, position.y + other.position.y };
		return EntityGeometry(newPos, angle + other.angle);
	}
	
	// The position of an entity is absolute within the screen,
	// but the position of a subentity is relative to its parent entity's position.
	SDL_FPoint position;
	double angle;
}