#pragma once
#include "state.h"

class TitleMenuState : public State {
public:
	TitleMenuState(Graphics* _g, Input* _i, Audio* _a);
	~TitleMenuState();
	void init() override;
	int update() override;
};