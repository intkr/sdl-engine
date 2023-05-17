#pragma once
#include "StateTitle.h"
#include "StateTest.h"

#include "GamePair.h"


class StateManager {
public:
	StateManager(StateType _s, Graphics* _g, Input* _i, Audio* _a);
	~StateManager();
	void update();
private:
	void setState(StateType state);

	// Returns false if _command currently has a certain type.
	//	(ex. _CMD_STATE - game is under state transition)
	// Otherwise, returns true.
	bool isCmdUpdatable();

	State* s;
	Graphics* g;
	Input* i;
	Audio* a;

	Command _command;
	StateType currentState;
};