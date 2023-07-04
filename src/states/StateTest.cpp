#include "../graphics.h"
#include "../audio.h"
#include "../input.h"
#include "score.h"

#include "StateTest.h"

StateTest::StateTest(SCore* _score, Core* _core) : State(_score, _core) {
	init();
}

StateTest::~StateTest() {}

void StateTest::init() {
	//g->reset();
}

void StateTest::update() {}

void StateTest::exitState(StateType targetState) {}