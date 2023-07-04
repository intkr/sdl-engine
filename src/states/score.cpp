#include "score.h"
#include "../graphics.h"
#include "../input.h"

SCore::SCore(Core* _core) : core(_core), currentState(_STATE_TITLE) {
	changeState(currentState);
}

SCore::~SCore() {}

void SCore::changeState(StateType state) {
	if (s != nullptr) delete s;

	switch (state) {
	case _STATE_TITLE:
		std::cout << "Screen transitioned to title menu.\n";
		s = new StateTitle(this, core);
		break;
	case _GAME_PAIR:
		std::cout << "Screen transitioned to game \"Pair\".\n";
		s = new GamePair(this, core);
		break;
	case _STATE_TEST:
		std::cout << "Screen transitioned to test menu.\n";
		s = new StateTest(this, core);
		break;
	default:
		// shouldn't happen
		break;
	}
}

void SCore::update() {
	s->update();
	
	// TODO: fix
	//while (!cmdQueue.empty()) {
	//	cmd = cmdQueue.front();
	//
	//	switch (cmd.type) {
	//	case _CMD_STATE:
	//		if (s->isStateRunning()) s->exitState(cmd);
	//		else changeState((StateType)cmd.value);
	//		return;
	//	case _CMD_TRANSITION:
	//		cmdQueue.push(Command{ _CMD_STATE, cmd.value });
	//	default:
	//		break;
	//	}
	//
	//	cmdQueue.pop();
	//}
}

bool SCore::isStateRunning() {
	return true;
}

void SCore::handleKey(SDL_Scancode id, bool active) {
	s->handleKey(id, active);
}

void SCore::handleHover(std::string objName) {
	s->handleHover(objName);
}

void SCore::handleClick(std::string objName, bool active) {
	s->handleClick(objName, active);
}

void SCore::handleRelease(std::string objName) {
	s->handleRelease(objName);
}

int SCore::checkKeybinds(SDL_Scancode key) {
	return core->checkKeybinds(key);
}