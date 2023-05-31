#pragma once
#include <map>
#include <vector>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "animation.h"
#include "command.h"

// _BACKGROUND, _FOREGROUND, _POPUP
enum SpriteType { _BACKGROUND, _FOREGROUND, _POPUP };

#define AniContainer std::map<std::string, AnimationGroup*>

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
	// false if its animations have all finished playing.
	bool updateSprite();

	void setStatus(TimelineType type) { status = type; }
	TimelineType getStatus() { return status; }

	void setTexture(SDL_Texture* texture) { _texture = texture; }
	// Adds animation group to _animations. Returns true if successful, false otherwise.
	//
	// name : Animation group object identifier.
	// a : Animation group object.
	bool addAnimationGroup(std::string name, TimelineType type, AnimationGroup* g);

	// Adds animation event to an animation group.
	// 
	// groupName : Animation group object identifier.
	bool addAnimationEvent(std::string groupName, AnimationEvent* e);

	bool toggleAnimationGroup(std::string groupName, TimelineType type, bool enable);

private:
	SDL_Texture* _texture;
	SDL_Rect* srcRect;
	SDL_FRect* baseRect;
	SDL_FRect* dstRect;

	double angle;
	bool visibility;

	// destroy animation when finished (unless idle looping)
	// change status when vector is empty
	AniContainer introAnimations;
	AniContainer idleAnimations;
	AniContainer outroAnimations;
	AniContainer* _animations[3];
	TimelineType status;
};



// This function checks the collision between a point and a rotated rectangle.
// 
// p : Point on screen.
// s : Sprite to check collision with.
bool checkCollision(SDL_FPoint point, Sprite* sprite);

bool checkCollision(Sprite* s1, Sprite* s2);