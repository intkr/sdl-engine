#pragma once
#include <map>
#include <vector>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "status.h"
#include "animation.h"

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

	bool isVisible() { return visibility; }

	void setAngle(double a);
	double getAngle() { return angle; }

	void setStatus(StatusType _status) { status = _status; }
	StatusType getStatus() { return status; }

	/// <summary>
	/// Resets the values of dstRect to baseRect.
	/// </summary>
	void resetDstRect();

	/// <summary>
	/// Sets the sprite's status to _OUTRO.
	/// </summary>
	void triggerOutro() { status = _OUTRO; }

	/// <summary>
	/// Updates the sprite by processing through all of its animations.
	/// </summary>
	/// <returns>true if sprite needs to be rendered, false otherwise.</returns>
	bool update();

	/// <summary>
	/// Sets the sprite's texture.
	/// </summary>
	/// <param name="texture">: Texture to be used.</param>
	void setTexture(SDL_Texture* texture) { _texture = texture; }

	/// <summary>
	/// Adds an animation group to the sprite.
	/// </summary>
	/// <param name="name">: Animation group name.</param>
	/// <param name="type">: Animation status type - _INTRO, _IDLE, _OUTRO. </param>
	/// <param name="g">: Animation group object.</param>
	/// <returns>true if successful, false otherwise.</returns>
	bool addAnimationGroup(std::string name, StatusType type, AnimationGroup* g);

	/// <summary>
	/// Adds an animation event to an animation group.
	/// </summary>
	/// <param name="groupName">: Animation group name.</param>
	/// <param name="e">: Animation event object.</param>
	/// <returns>true if successful, false otherwise.</returns>
	bool addAnimationEvent(std::string groupName, AnimationEvent* e);

	/// <summary>
	/// Enables or disables an animation group.
	/// </summary>
	/// <param name="groupName">: Animation group name.</param>
	/// <param name="type">: Animation status type - _INTRO, _IDLE, _OUTRO. </param>
	/// <param name="enable">: Enables the group if true, disables if false.</param>
	/// <returns>true if successful, false otherwise.</returns>
	bool toggleAnimationGroup(std::string groupName, StatusType type, bool enable);

private:
	/// <summary>
	/// Texture used for the sprite.
	/// </summary>
	SDL_Texture* _texture;

	/// <summary>
	/// Rectangle used on the texture.
	/// </summary>
	SDL_Rect* srcRect;

	/// <summary>
	/// Rectangle used to draw on the screen, pre-animation.
	/// May not equal to the sprite's hitbox - use dstRect instead.
	/// </summary>
	SDL_FRect* baseRect;

	/// <summary>
	/// Rectangle used to draw on the screen, post-animation.
	/// Equal to sprite's hitbox.
	/// </summary>
	SDL_FRect* dstRect;

	/// <summary>
	/// Sprite's rotation angle, in degrees.
	/// </summary>
	double angle;

	/// <summary>
	/// Sprite's visibility.
	/// Visible if true, invisible if false.
	/// </summary>
	bool visibility;

	// destroy animation when finished (unless idle looping)
	// change status when vector is empty

	/// <summary>
	/// List of the sprite's AnimationGroups.
	/// </summary>
	AniContainer introAnimations;
	AniContainer idleAnimations;
	AniContainer outroAnimations;

	/// <summary>
	/// Array of three AnimationGroup lists.
	/// </summary>
	AniContainer* _animations[3];

	/// <summary>
	/// Sprite status.
	/// </summary>
	StatusType status;
};

/// <summary>
/// Checks if the sprite's hitbox overlaps with a single point.
/// </summary>
/// <param name="point">: Specific point, with float coordinate values.</param>
/// <param name="sprite">: Sprite object.</param>
/// <returns>true if they overlap, false otherwise.</returns>
bool checkCollision(SDL_FPoint point, Sprite* sprite);

/// <summary>
/// Checks if two sprites overlap.
/// TODO: Unfinished - make this when needed.
/// </summary>
/// <param name="s1">: Sprite object.</param>
/// <param name="s2">: Sprite object.</param>
/// <returns>true if they overlap, false otherwise.</returns>
bool checkCollision(Sprite* s1, Sprite* s2);