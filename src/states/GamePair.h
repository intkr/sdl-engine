#pragma once
#include "state.h"

class GamePair : public State {
public:
	GamePair(Graphics* _g, Input* _i, Audio* _a);
	~GamePair();
	void init() override;
	Command update() override;
};