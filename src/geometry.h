#pragma once

#include "SDL.h"

struct Position {
	Position Position::operator+(const Position& other) {
		SDL_FPoint newPos{ position.x + other.position.x, position.y + other.position.y };
		return Position{newPos, angle_deg + other.angle_deg};
	}

	SDL_FPoint point;
	double angle_deg;
};

// Contains pre-calculation geometric data.
struct SourceGeometry {
	// Used to get the sprite texture from the spritesheet.
	SDL_Rect textureBox;

	// Contains the values before any animation is applied.
	// Positioned relative to the entity's center.
	SDL_FRect baseBox;
	// Post-animation (i.e. "modded") box.
	// Positioned relative to the entity's center.
	SDL_FRect modBox;

	double angle_deg;
};

// Contains post-calculation geometric data.
struct FinalGeometry {
	// Used for the final rendering of the sprite.
	// Positioned absolute within the screen.
	SDL_FRect renderBox;
	// Used for collision handling.
	// Positioned absolute within the screen.
	SDL_FRect hitbox;

	double angle_deg;
};