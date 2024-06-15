#include "controller.h"

StateController* StateController::getStateController() {
	if (_controller == nullptr) {
		_controller = new StateController();
	}
	return _controller;
}

void StateController::deleteStateController() {
	delete _controller;
}

StateController::StateController() : currentState(_STATE_TITLE) {
	initStateTypes();
	changeState(currentState);
}

StateController::~StateController() {}

void StateController::initStateTypes() {
	stateTypes[_STATE_TEST] = &createState<StateTest>;
	stateTypes[_STATE_TITLE] = &createState<StateTitle>;
	stateTypes[_STATE_SELECT] = &createState<StateSelect>;
	stateTypes[_STATE_PREP] = &createState<StatePrep>;
	stateTypes[_GAME_PAIR] = &createState<StatePair>;
}

void StateController::changeState(StateCode code) {
	if (state != nullptr) delete state;
	loadState(code);
}

void StateController::loadState(StateCode code) {
	try {
		state = stateTypes[stateTypes.at(state)]();
	}
	catch (std::out_of_range& e) {
		// This state has not been added properly to the map when initializing,
		// so load the testing state as a failsafe.
		state = createState<StateTest>();
	}
}

void StateController::update() {
	state->updateData();
	state->updateAssets();
}

void StateController::handleInput(KeyInput i) {
	state->handleKey(i);
}

void StateController::handleInput(MouseInput i) {
	state->handleMouse(i);
}

void StateController::render(Renderer* r) {
	state->render(r);
}