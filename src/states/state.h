#pragma once
#include <string>

#include <SDL.h>

#include "../input_event.h"

enum class StateCode {
	_STATE_TEST = 0, _STATE_TITLE = 1, _STATE_SELECT = 2, _STATE_PREP = 3,
	_GAME_PAIR = 101
};

// Base class for states in a Finite State Machine.
class State {
public:
	State() {}
	virtual ~State() {}

	// Critical common functions.
	// Make sure to override these for every existing state.

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void exit() = 0;

	// Event handling common functions.
	// If not required, these functions may not be overridden.

	virtual void handleKey(Key key, InputType type) {}
	virtual void handleMouseHover(MouseButton button, SDL_FPoint pos) {}
	virtual void handleMouseDown(MouseButton button, SDL_FPoint pos) {}
	virtual void handleMouseUp(MouseButton button, SDL_FPoint pos) {}
	virtual void handleClick(MouseButton button, SDL_FPoint pos) {}
};