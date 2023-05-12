#pragma once
#include <vector>

class Sprite;

class AnimationEvent {
public:
	AnimationEvent(int length, void (*func)(Sprite*, AnimationEvent*)) : animationLength(length), currentFrame(0), f(func) {}

	// Processes the sprite's animation.
	// If an animation cycle has finished, reset the current frame timer and return true.
	// Otherwise, return false.
	bool animate(Sprite* s);
	
	unsigned int getCurrentFrame() { return currentFrame; }
	unsigned int getAnimationLength() { return animationLength; }

	std::vector<double>* getParameter() { return &parameters; }

private:
	void (*f)(Sprite*, AnimationEvent*);

	// Value range is [0 ~ animationLength).
	// Value is changed after animation is processed.
	unsigned int currentFrame;

	// Length is set assuming game runs at 60 FPS.
	unsigned int animationLength;

	std::vector<double> parameters;
};

class AnimationGroup {
public:
	AnimationGroup() : looping(false), sequential(false), currentAnimation(-1) {}
	AnimationGroup(bool _looping, bool _sequential) : looping(_looping), sequential(_sequential), currentAnimation((int)!_sequential) {}

	void reset();

	// Processes the sprite's animation group.
	// If all animation has finished playing, return true.
	// Otherwise, return false.
	bool animate(Sprite* s);

	bool addEvent(AnimationEvent* e);

	void update();

private:
	// Vector containing all animation objects within the group.
	std::vector<AnimationEvent*> animationList;

	// Index of the currently playing animation in _animationList.
	// 
	// Any non-negative value indicates that this animation group is sequential,
	// so every AnimatinoEvent should be processed one-by-one.
	//
	// Negative values (ideally -1) indicates that this animation group is non-sequential,
	// so every AnimationEvent should all be processed at once.
	unsigned int currentAnimation;

	bool looping;
	bool sequential;
};