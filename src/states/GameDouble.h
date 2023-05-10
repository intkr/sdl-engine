#pragma once
#include "state.h"

class GameDouble : public State {
public:
	GameDouble(Graphics* _g, Input* _i, Audio* _a);
	~GameDouble();
	void init() override;
	Command update() override;
};