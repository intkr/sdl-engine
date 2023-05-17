#include "stateManager.h"
#include "../graphics.h"

StateManager::StateManager(StateType _s, Graphics* _g, Input* _i, Audio* _a) : g(_g), i(_i), a(_a), currentState(_s) {
	setState(_s);
}

StateManager::~StateManager() {}

void StateManager::setState(StateType state) {
	delete s;

	switch (state) {
	case _STATE_TITLE:
		std::cout << "Screen transitioned to title menu.\n";
		s = new StateTitle(g, i, a);
		break;
	case _GAME_PAIR:
		std::cout << "Screen transitioned to game \"Pair\".\n";
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

	if (isCmdUpdatable()) {
		_command = returnCmd;

		switch (_command.getType()) {
		case _CMD_TRANSITION:
			
			// idk how to implement this rn
			//break;

		case _CMD_STATE:
			s->free(_command);
			setState((StateType)_command.getValue());
			break;

		case _CMD_NONE:
		default:
			break;
		}
	}

	// fix when Command is implemented
	//if (currentState > 0 && 0) {
	//	currentState = 0;
	//	//g->triggerOutro();
	//}
	//if (currentState < 0) {
	//	if (s->isStateRunning()) {
	//		currentState = 0 - currentState;
	//		setState();
	//	}
	//}
}

bool StateManager::isCmdUpdatable() {
	switch (_command.getType()) {
	case _CMD_STATE:
	case _CMD_TRANSITION:
		return false;
		break;
	default:
		return true;
	}
}