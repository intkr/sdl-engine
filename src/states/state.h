#pragma once
#include <string>

#include <SDL.h>

#include "../status.h"
#include "../animation_functions.h"

class SCore;
class Core;

enum StateType {
	_STATE_TEST = 999, _STATE_TITLE = 1, _STATE_SELECT = 2,
	_GAME_PAIR = 101
};

// Base class for game states
class State {
public:
	State(SCore* _score, Core* _core) : sCore(_score), core(_core),
										interactable(true) {}
	virtual ~State() {}

	/// <summary>
	/// Initializes the state.
	/// </summary>
	virtual void init() = 0;
	
	/// <summary>
	/// Updates the state.
	/// </summary>
	virtual void update() = 0;

	/// <summary>
	/// Exits the state.<para/>
	/// Sprites, textures, and sounds should be deallocated here.
	/// </summary>
	/// <param name="targetState"></param>
	virtual void exitState(StateType targetState) = 0;

	virtual void handleKey(SDL_Scancode key, bool active) {}
	virtual void handleHover(std::string name) {}
	virtual void handleClick(std::string name, bool active) {}
	virtual void handleRelease(std::string name) {}

	void toggleInteractivity(bool status) { interactable = status; }
	bool isInteractable() { return interactable; }
protected:
	SCore* sCore;
	Core* core;

private:
	/// <summary>
	/// If true, user can interact with the game.
	/// </summary>
	bool interactable;
};