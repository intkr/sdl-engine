#pragma once
#include <queue>

#include "../core.h"

#include "StateTitle.h"
#include "StateTest.h"

#include "GamePair.h"

// State Core
class SCore {
public:
	SCore(Core* _c);
	~SCore();

	void update();
	void changeState(StateType state);

	// TODO: implement when needed
	bool isStateRunning();

	// cringe (and hopefully temporary) functions below

	void handleKey(SDL_Scancode id, bool active);
	void handleHover(std::string objName);
	void handleClick(std::string objName, bool active);
	void handleRelease(std::string objName);

	int checkKeybinds(SDL_Scancode key);

private:
	State* s;

	StateType currentState;

	Core* core;
};