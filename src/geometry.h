#pragma once

template <typename T>
struct Point<T> {
	T x;
	T y;
};

template <typename T>
struct Rect<T> {
	T x;
	T y;
	T w;
	T h;
};

struct Position {
	Position Position::operator+(const Position& other) {
		Point<float> newPos{ position.x + other.position.x, position.y + other.position.y };
		return Position{newPos, angle_deg + other.angle_deg};
	}

	Point<float> point;
	double angle_deg;
};

// Contains pre-calculation geometric data.
struct SourceGeometry {
	// Used to get the sprite texture from the spritesheet.
	Rect<int> textureBox;

	// Contains the values before any animation is applied.
	// Positioned relative to the entity's center.
	Rect<float> baseBox;
	// Post-animation (i.e. "modded") box.
	// Positioned relative to the entity's center.
	Rect<float> modBox;

	double angle_deg;
};

// Contains post-calculation geometric data.
struct FinalGeometry {
	// Used for the final rendering of the sprite.
	// Positioned absolute within the screen.
	Rect<float> renderBox;
	// Used for collision handling.
	// Positioned absolute within the screen.
	Rect<float> hitbox;

	double angle_deg;
};