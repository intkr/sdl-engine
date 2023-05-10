#pragma once
#include "state.h"

class StateTest : public State {
public:
	StateTest(Graphics* _g, Input* _i, Audio* _a);
	~StateTest();
	void init() override;
	Command update() override;
};