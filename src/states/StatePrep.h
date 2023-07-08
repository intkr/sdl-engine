#pragma once

#include "state.h"

class StatePrep : public State {
public:
	StatePrep(SCore* _score, Core* _core);
	~StatePrep() {}

	void init() override;
	void update() override;
	void exitState(StateType targetState) override;

	void handleClick(std::string name, bool active) override;

private:
	int selectedGame;
};