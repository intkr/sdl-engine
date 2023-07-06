#pragma once
#include <map>
#include <vector>
#include <string>

class Sprite;

class AnimationEvent {
public:
	AnimationEvent(int length, void (*func)(Sprite*, AnimationEvent*)) : maxFrames(length), currentFrame(0), f(func) {}
	~AnimationEvent() {}

	/// <summary>
	/// Animate the sprite by processing an animation event.
	/// </summary>
	/// <param name="s">: Sprite object.</param>
	/// <returns>true if the animation event has finished, false otherwise.</returns>
	bool animate(Sprite* s);

	/// <summary>
	/// Resets the animation event by resetting the current frame counter.
	/// </summary>
	void reset() { currentFrame = 1; }
	
	unsigned int getCurrentFrame() { return currentFrame; }
	unsigned int getMaxFrames() { return maxFrames; }

	/// <summary>
	/// Sets a new animation parameter.
	/// </summary>
	/// <param name="name">: Parameter name.</param>
	/// <param name="value">: Parameter value.</param>
	/// <returns>true if successful, false otherwise.</returns>
	bool setBool(std::string name, bool value);
	bool setChar(std::string name, char value);
	bool setFloat(std::string name, float value);

	/// <summary>
	/// Returns an animation parameter.<para/>
	/// If an invalid parameter is requested, a default value listed as below is returned.<para/>
	/// false (bool) / '\0' (char) / 0.0f (float)
	/// </summary>
	/// <param name="name">: Parameter name.</param>
	/// <returns>Parameter value if successful, or default value otherwise.</returns>
	bool getBool(std::string name);
	char getChar(std::string name);
	float getFloat(std::string name);

private:
	/// <summary>
	/// Animation function defined within the namespace 'Animations'.
	/// </summary>
	void (*f)(Sprite*, AnimationEvent*);

	/// <summary>
	/// Current animation frame counter.<para/>
	/// Value range is [1 ~ maxFrames].
	/// </summary>
	unsigned int currentFrame;

	/// <summary>
	/// Length of the animation in frames.<para/>
	/// Assumes game runs at 60 FPS.
	/// </summary>
	unsigned int maxFrames;

	/// <summary>
	/// List of parameters.
	/// </summary>
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

	/// <summary>
	/// Resets all AnimationEvents in the group to its initial state.
	/// </summary>
	void reset();

	/// <summary>
	/// Animates the sprite by processing all events in the group.
	/// </summary>
	/// <param name="s">: Sprite object.</param>
	/// <returns>true if all animation events have finished, false otherwise.</returns>
	bool animate(Sprite* s);

	/// <summary>
	/// Adds an animation event to the group.
	/// </summary>
	/// <param name="e">: Animation event object.</param>
	/// <returns>true if successful, false otherwise.</returns>
	bool addEvent(AnimationEvent* e);

	/// <summary>
	/// Enables the group, and resets all events in the group.
	/// </summary>
	void enableGroup();

	/// <summary>
	/// Disables the group.<para/>
	/// Its events are not affected.
	/// </summary>
	void disableGroup() { enabled = false; }

private:
	/// <summary>
	/// List of all animation events for the group.
	/// </summary>
	std::vector<AnimationEvent*> animationList;

	/// <summary>
	/// Index of the currently playing animation event in _animationList, if the group is sequential.<para/>
	/// -1 if the group is not sequential, indicating all events should be played simultaneously.
	/// </summary>
	unsigned int currentAnimation;

	/// <summary>
	/// If true, its animation events are processed.
	/// </summary>
	bool enabled;

	/// <summary>
	/// If true, all animation events restart when they are finished.
	/// </summary>
	bool looping;

	/// <summary>
	/// If true, the animation events in the group is processed one at a time.
	/// </summary>
	bool sequential;
};