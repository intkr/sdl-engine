#pragma once
#include <queue>

#include "StateTitle.h"
#include "StateTest.h"

#include "GamePair.h"


class StateManager {
public:
	StateManager(StateType _s, Graphics* _g, Input* _i, Audio* _a);
	~StateManager();
	void update();

private:
	void pollInput();

	void pushCommand(Command& cmd);

	void setState(StateType state);

	// Returns false if the first item in queue currently has a certain type.
	//	(ex. _CMD_STATE - game is under state transition)
	// Otherwise, returns true.
	bool cmdEnabled;

	State* s;
	Graphics* g;
	Input* i;
	Audio* a;

	// Used to poll all inputs for each frame.
	std::queue<Command> cmdQueue;

	StateType currentState;
};