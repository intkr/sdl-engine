#include "StateTest.h"

#include "../core.h"
#include "score.h"


StateTest::StateTest(SCore* _score, Core* _core) : State(_score, _core) {
	init();
}

StateTest::~StateTest() {}

void StateTest::init() {
	//g->reset();
}

void StateTest::update() {}

void StateTest::exitState(StateType targetState) {}