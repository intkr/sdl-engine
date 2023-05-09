#include "stateManager.h"
#include "../graphics.h"

StateManager::StateManager(int n, Graphics* _g, Input* _i, Audio* _a) : g(_g), i(_i), a(_a), currentState(n) {
	setState();
}

StateManager::~StateManager() {}

void StateManager::setState() {
	delete s;

	switch (currentState) {
	case _STATE_TITLE:
		std::cout << "Screen transitioned to title menu.\n";
		s = new TitleMenuState(g, i, a);
		break;
	case _STATE_TEST:
		std::cout << "Screen transitioned to test menu.\n";
		s = new TestState(g, i, a);
		break;
	default:
		// shouldn't happen
		break;
	}
}

void StateManager::update() {
	int r = s->update();

	if (currentState > 0 && r > 0) {
		currentState = 0 - r;
		g->triggerOutro();
	}
	if (currentState < 0) {
		if (s->isStateRunning()) {
			currentState = 0 - currentState;
			setState();
		}
	}
}