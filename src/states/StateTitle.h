#pragma once
#include "state.h"

class StateTitle : public State {
public:
	StateTitle(Graphics* _g, Input* _i, Audio* _a);
	~StateTitle();
	void init() override;
	Command update() override;

private:

};