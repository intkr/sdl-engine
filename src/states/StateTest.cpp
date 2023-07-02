#include "../graphics.h"
#include "../audio.h"
#include "../input.h"
#include "score.h"

#include "StateTest.h"

StateTest::StateTest(SCore* _core) : State(_core) {
	init();
}

StateTest::~StateTest() {}

void StateTest::init() {
	Graphics* g = core->getGraphics();
	g->reset();
}

void StateTest::update() {}

void StateTest::exitState(StateType targetState) {}