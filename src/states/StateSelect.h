#pragma once

#include "state.h"

class StateSelect : public State {
public:
	StateSelect(SCore* _score, Core* _core);
	~StateSelect();

	void init() override;
	void update() override;
	void exitState(StateType targetState) override;

	void handleClick(std::string name, bool active) override;

private:
	int selectedGame;
};