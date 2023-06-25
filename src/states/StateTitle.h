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

	Command handleClick(std::string name, bool active) override;
	Command handleKey(SDL_Scancode key, bool active) override;

private:

	void freeAll();
	void freeSpecifics(); // rename to something better

	bool test = true;
};