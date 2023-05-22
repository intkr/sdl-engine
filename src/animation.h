#pragma once
#include <map>
#include <vector>
#include <string>

class Sprite;

class AnimationEvent {
public:
	AnimationEvent(int length, void (*func)(Sprite*, AnimationEvent*)) : maxFrames(length), currentFrame(0), f(func) {}
	~AnimationEvent() {}

	// Processes the sprite's animation.
	// If an animation cycle has finished, reset the current frame timer and return true.
	// Otherwise, return false.
	bool animate(Sprite* s);

	void reset() { currentFrame = 0; }
	
	unsigned int getCurrentFrame() { return currentFrame; }
	unsigned int getMaxFrames() { return maxFrames; }

	bool setBool(std::string name, bool value) {
		if (paramBool.count(name) > 0) return false;
		paramBool[name] = value;
		return true;
	}
	bool setFloat(std::string name, float value) {
		if (paramFloat.count(name) > 0) return false;
		paramFloat[name] = value;
		return true;
	}
	bool setChar(std::string name, char value) {
		if (paramChar.count(name) > 0) return false;
		paramChar[name] = value;
		return true;
	}

	bool getBool(std::string name) { return paramBool[name]; }
	float getFloat(std::string name) { return paramFloat[name]; }
	char getChar(std::string name) { return paramChar[name]; }

private:
	void (*f)(Sprite*, AnimationEvent*);

	// Value range is [0 ~ maxFrames).
	// Value is changed after animation is processed.
	unsigned int currentFrame;

	// Length is set assuming game runs at 60 FPS.
	unsigned int maxFrames;

	std::map<std::string, float> paramFloat;
	std::map<std::string, char> paramChar;
	std::map<std::string, bool> paramBool;
};

class AnimationGroup {
public:
	AnimationGroup() : looping(false), sequential(false), enabled(true), currentAnimation(-1) {}
	AnimationGroup(bool _looping, bool _sequential, bool _enabled)
		: looping(_looping), sequential(_sequential), enabled(_enabled), currentAnimation((int)!_sequential) {}
	~AnimationGroup();

	// Resets all AnimationEvents to its initial state.
	void reset();

	// Processes the sprite's animation group.
	// If all animation has finished playing, return true.
	// Otherwise, return false.
	bool animate(Sprite* s);

	bool addEvent(AnimationEvent* e);

	void update();

	void enableGroup() { enabled = true; }
	void disableGroup() { enabled = false; }

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

	bool enabled;
	bool looping;
	bool sequential;
};