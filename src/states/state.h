#pragma once
#include <string>

#include <SDL.h>

#include "../command.h"
#include "../animation_functions.h"

class Input;
class Audio;
class Graphics;

enum StateType {
	_STATE_TEST = 999, _STATE_TITLE = 1,
	_GAME_PAIR = 101
};

// Base class for game states
class State {
public:
	State(Graphics* _g, Input* _i, Audio* _a) : g(_g), i(_i), a(_a), interactable(true) {}
	virtual ~State() {}

	virtual void init() = 0;
	
	// Returns 0 if the screen state shouldn't change;
	// otherwise returns screen state key value
	virtual Command update();

	// Deallocates sprites and textures.
	// In most cases (if not all), _CMD_STATE or _CMD_TRANSITION is assumed.
	virtual void exitState(Command& cmd) = 0;

	// Checks for sprite and audio data.
	// If there are no sprites available and no sound is playing,
	// assume the game is going to transition into a new state and return false.
	// Otherwise, return true.
	virtual bool isStateRunning() = 0;

	// Handles a specific portion of user input, and returns a Command object.
	// Command type is _CMD_NONE if nothing of value should be returned.
	// In such cases, the return value should be ignored.

	virtual Command handleKey(SDL_Scancode key, bool active);
	virtual Command handleHover(std::string name);
	virtual Command handleClick(std::string name, bool active);
	virtual Command handleRelease(std::string name);

	void toggleInteractivity(bool status) { interactable = status; }
	bool isInteractable() { return interactable; }
protected:
	Graphics* g;
	Input* i;
	Audio* a;

private:
	bool interactable;
};