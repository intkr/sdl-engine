#pragma once
#include "state.h"

class StateTest : public State {
public:
	StateTest(SCore* _score, Core* _core);
	~StateTest();
	void init() override;
	void update() override;
	void exitState(StateType targetState) override;
};