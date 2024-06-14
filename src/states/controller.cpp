#include "score.h"

#include "../graphics.h"
#include "../input.h"
#include "../core.h"

StateController::StateController() {
	StateCode startingState = _STATE_TITLE;
	loadState(startingState);
}

StateController::~StateController() {}

void StateController::changeState(StateCode code) {
	if (state != nullptr) delete state;
	loadState(code);
}

void StateController::loadState(StateCode code) {
	// Looks like horrible and archaic implementation, but this should be fixed as I implement states with Lua
	switch (code) {
	case _STATE_TITLE:
		state = new StateTitle(this);
		break;

	case _STATE_SELECT:
		state = new StateSelect(this);
		break;

	case _STATE_PREP:
		state = new StatePrep(this);
		break;
	
	//////
	case _GAME_PAIR:
		state = new GamePair(this);
		break;
	case _STATE_TEST:
		state = new StateTest(this);
		break;
	default:
		// shouldn't happen unless I forgot to write a case for a state
		break;
	}
}

void StateController::update() {
	state->update();
}

void StateController::handleKey(KeyInput& input) {
	state->handleKey(id, active);
}

void StateController::handleMouse(MouseInput& input) {
	switch (input.type) {
		// write after ik what those events do
		//case _SOMETHING:
		//	state->handleWhatever(input.button, input.pos);
	}
}