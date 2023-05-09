#pragma once
#include "TitleMenu.h"
#include "TestState.h"

enum StateName { _STATE_TEST = 999, _STATE_TITLE = 1,  };

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

	int currentState;
};