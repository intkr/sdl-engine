#include "../graphics.h"
#include "../audio.h"
#include "../input.h"

#include "StateTest.h"

extern float rm;

StateTest::StateTest(Graphics* _g, Input* _i, Audio* _a) : State(_g, _i, _a) {
	init();
}

StateTest::~StateTest() {}

void StateTest::init() {
	g->reset();
}

Command StateTest::update() {
	auto pressedKeys = i->getPressedKeys();
	if (pressedKeys->size() > 0) {
		return Command();
	}

	auto clickedObject = i->getClickedObject();
	if (clickedObject->size() > 0) {
		return Command();
	}

	return Command();
}

void StateTest::free(Command& cmd) {
}

bool StateTest::isStateRunning() {
	return true;
}