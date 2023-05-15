#pragma once
#include "StateTitle.h"
#include "StateTest.h"

#include "GamePair.h"


class StateManager {
public:
	StateManager(int n, Graphics* _g, Input* _i, Audio* _a);
	~StateManager();
	void update();
private:
	void setState();
	State* s;
	Graphics* g;
	Input* i;
	Audio* a;

	Command _command;
	int currentState;
};