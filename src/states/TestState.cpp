#include "../graphics.h"
#include "../audio.h"
#include "../input.h"

#include "TestState.h"

extern double rm;

TestState::TestState(Graphics* _g, Input* _i, Audio* _a) : State(_g, _i, _a) {
	init();
}

TestState::~TestState() {}

void TestState::init() {
	g->reset();
}

int TestState::update() {
	auto pressedKeys = i->getPressedKeys();
	if (pressedKeys->size() > 0) {
		return 0;
	}

	auto clickedObject = i->getClickedObject();
	if (clickedObject->size() > 0) {
		return 0;
	}

	return 0;
}