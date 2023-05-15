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
		s = new StateTitle(g, i, a);
		break;
	case _GAME_PAIR:
		std::cout << "Screen transitioned to game \"Double\".\n";
		s = new GamePair(g, i, a);
		break;
	case _STATE_TEST:
		std::cout << "Screen transitioned to test menu.\n";
		s = new StateTest(g, i, a);
		break;
	default:
		// shouldn't happen
		break;
	}
}

void StateManager::update() {
	// Return value is ignored under certain situations
	Command returnCmd = s->update();

	switch (_command.getType()) {
	case _CMD_STATE:
		// _command shouldn't change
		break;
	default:
		_command = returnCmd;
	}

	// 
	switch (_command.getType()) {
	case _CMD_STATE:

		break;

	case _CMD_NONE:
	default:
		break;
	}

	// fix when Command is implemented
	if (currentState > 0 && 0) {
		currentState = 0;
		//g->triggerOutro();
	}
	if (currentState < 0) {
		if (s->isStateRunning()) {
			currentState = 0 - currentState;
			setState();
		}
	}
}