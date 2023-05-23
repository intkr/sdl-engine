#pragma once
#include "state.h"

class StateTitle : public State {
public:
	StateTitle(Graphics* _g, Input* _i, Audio* _a);
	~StateTitle();
	void init() override;
	Command update() override;
	void exitState(Command& cmd) override;
	bool isStateRunning() override;

private:
	Command handleClick(std::string name, bool active);

	void freeAll();
	void freeSpecifics(); // rename to something better

	bool test = true;
};