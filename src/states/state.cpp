#include "state.h"
#include "../graphics.h"
#include "../audio.h"

State::State(Graphics* _g, Input* _i, Audio* _a) : g(_g), i(_i), a(_a) {}

State::~State() {}

bool State::isStateRunning() {
	return g->hasSprites() || a->hasSounds();
}

Command State::handleKey(SDL_Scancode key, bool active) { return Command(); }
Command State::handleHover(std::string name) { return Command(); }
Command State::handleClick(std::string name, bool active) { return Command(); }
Command State::handleRelease(std::string name) { return Command(); }