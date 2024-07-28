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