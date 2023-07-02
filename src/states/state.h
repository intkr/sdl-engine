#pragma once
#include <string>

#include <SDL.h>

#include "../status.h"
#include "../animation_functions.h"

class SCore;

enum StateType {
	_STATE_TEST = 999, _STATE_TITLE = 1,
	_GAME_PAIR = 101
};

// Base class for game states
class State {
public:
	State(SCore* _core) : core(_core), interactable(true) {}
	virtual ~State() {}

	virtual void init() = 0;
	
	// Returns 0 if the screen state shouldn't change;
	// otherwise returns screen state key value
	virtual void update() = 0;

	// Deallocates sprites and textures.
	// In most cases (if not all), _CMD_STATE or _CMD_TRANSITION is assumed.
	virtual void exitState(StateType targetState) = 0;

	// Handles a specific portion of user input, and returns a Command object.
	// Command type is _CMD_NONE if nothing of value should be returned.
	// In such cases, the return value should be ignored.

	virtual void handleKey(SDL_Scancode key, bool active) {}
	virtual void handleHover(std::string name) {}
	virtual void handleClick(std::string name, bool active) {}
	virtual void handleRelease(std::string name) {}

	void toggleInteractivity(bool status) { interactable = status; }
	bool isInteractable() { return interactable; }
protected:
	SCore* core;

private:
	bool interactable;
};