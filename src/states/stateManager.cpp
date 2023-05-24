#include "stateManager.h"
#include "../graphics.h"
#include "../input.h"

StateManager::StateManager(StateType _s, Graphics* _g, Input* _i, Audio* _a) : g(_g), i(_i), a(_a), currentState(_s) {
	setState(_s);
}

StateManager::~StateManager() {}

void StateManager::setState(StateType state) {
	delete s;
	std::queue<Command>().swap(cmdQueue);

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
	pollInput();
	s->update();
	if (cmdQueue.empty()) return;
	Command& cmd = cmdQueue.front();
	
	while (!cmdQueue.empty()) {
		cmd = cmdQueue.front();

		switch (cmd.type) {
		case _CMD_STATE:
			if (s->isStateRunning()) s->exitState(cmd);
			else setState((StateType)cmd.value);
			return;
		case _CMD_TRANSITION:
			cmdQueue.push(Command{ _CMD_STATE, cmd.value });
		default:
			break;
		}

		cmdQueue.pop();
	}
}

void StateManager::pollInput() {
	Command cmd;
	SDL_Scancode id;
	std::string objName;
	bool active;

	for (auto& key : *i->getPressedKeys()) {
		id = key.first, active = key.second;
		cmd = s->handleKey(id, active);
		pushCommand(cmd);
	}

	for (auto& obj : *i->getHoveredObject()) {
		cmd = s->handleHover(obj);
		pushCommand(cmd);
	}

	for (auto& obj : *i->getClickedObject()) {
		objName = obj.first, active = obj.second;
		cmd = s->handleClick(objName, active);
		pushCommand(cmd);
	}

	for (auto& obj : *i->getReleasedObject()) {
		cmd = s->handleRelease(obj);
		pushCommand(cmd);
	}
}

void StateManager::pushCommand(Command& cmd) {
	if (cmd.type == _CMD_NONE) return;
	if (!cmdEnabled) {
		cmdQueue.push(cmd);
	}
}