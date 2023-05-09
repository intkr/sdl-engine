#pragma once
#include "state.h"

class TestState : public State {
public:
	TestState(Graphics* _g, Input* _i, Audio* _a);
	~TestState();
	void init() override;
	int update() override;
};