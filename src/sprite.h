#pragma once
#include <vector>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "animation.h"

enum AnimationType { _INTRO, _IDLE, _OUTRO, _END };
enum SpriteType { _BACKGROUND, _FOREGROUND, _POPUP };

#define AniVector std::vector<std::pair<std::string, Animation*>>

class Animation;

class Sprite {
public:
	Sprite(SDL_Texture* tex, SDL_Rect* src, SDL_FRect* dst, double a = 0);
	~Sprite();

	SDL_Texture* getTexture() { return _texture; }
	SDL_Rect* getSrcRect() { return srcRect; }
	SDL_FRect* getDstRect() { return dstRect; }
	SDL_FRect* getBaseRect() { return baseRect; }
	double getAngle() { return angle; }
	bool isVisible() { return visibility; }

	void setAngle(double a);

	// Forces the status to _OUTRO.
	// Use to remove certain sprites or trigger screen transitions.
	void triggerOutro() { status = _OUTRO; }

	// Updates sprite by processing through its animations.
	// Returns true if sprite is valid and needs to be rendered,
	// false if it finished its animations and needs to be deleted.
	bool updateSprite();

	// Adds animation to vector. Returns true if successful, false otherwise.
	//
	// name : Sprite object identifier.
	// a : Animation object. Must be dynamically allocated.
	bool addAnimation(std::string name, Animation* a, AnimationType type);

private:
	SDL_Texture* _texture;
	SDL_Rect* srcRect;
	SDL_FRect* baseRect;
	SDL_FRect* dstRect;

	double angle;
	bool visibility;

	// destroy animation when finished (unless idle looping)
	// change status when vector is empty
	AniVector introAnimations;
	AniVector idleAnimations;
	AniVector outroAnimations;
	AniVector* _animations[3];
	AnimationType status;
};



// This function checks the collision between a point and a rotated rectangle.
// 
// p : Point on screen.
// s : Sprite to check collision with.
bool checkCollision(SDL_FPoint& point, Sprite* sprite);

bool checkCollision(Sprite* s1, Sprite* s2);